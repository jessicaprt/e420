#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "client_handler.h"
#include "common.h"
#include "rw_lock.h"

rwlock_t rw_lock;

void set_up_client_handler(int array_length) {
    rwlock_init(&rw_lock);
}

void* handle_client(void* handle_client_params) {
    handle_client_params_t* params = (handle_client_params_t*) handle_client_params;

    int request_type = receive_int(params->socket);
    int request_index = receive_int(params->socket);

    if (request_type == READ_REQUEST_TYPE) {
        rwlock_rlock(&rw_lock);
        read_and_send_line(params->theArray, params->socket, request_index);
        rwlock_unlock(&rw_lock);
    } else if (request_type == WRITE_REQUEST_TYPE) {
        rwlock_wlock(&rw_lock);
        mark_line_as_modified(params->theArray, request_index);
        rwlock_unlock(&rw_lock);

        rwlock_rlock(&rw_lock);
        read_and_send_line(params->theArray, params->socket, request_index);
        rwlock_unlock(&rw_lock);
    }

    close(params->socket);

    return NULL;
}