#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client_handler.h"
#include "common.h"
#include "rw_lock.h"

rwlock_t* rw_locks;

int LENGTH_OF_MODIFIED_LINE_WITHOUT_INDEX = 45;

void set_up_client_handler(int array_length) {
    rw_locks = malloc(array_length * sizeof(rwlock_t));
    for (int i = 0; i < array_length; i++) {
        rwlock_init(&rw_locks[i]);
    }
}

void* handle_client(void* handle_client_params) {
    handle_client_params_t* params = (handle_client_params_t*) handle_client_params;

    int request_type = receive_int(params->socket);
    int request_index = receive_int(params->socket);

    rwlock_t array_mutex = rw_locks[request_index];

    if (request_type == READ_REQUEST_TYPE) {
        rwlock_rlock(&array_mutex);
        char * arrayLine = params->theArray[request_index];
        rwlock_unlock(&array_mutex);

        int arrayLength = strlen(arrayLine);
        send_chars(params->socket, arrayLine, arrayLength);
    } else if (request_type == WRITE_REQUEST_TYPE) {
        rwlock_wlock(&array_mutex);
        int newLength = LENGTH_OF_MODIFIED_LINE_WITHOUT_INDEX + get_total_digits_of(request_index);
        params->theArray[request_index] = realloc(params->theArray[request_index], newLength * sizeof(char));
        snprintf(params->theArray[request_index], newLength, "String %d has been modified by a write request", request_index);
        rwlock_unlock(&array_mutex);

        rwlock_rlock(&array_mutex);
        char * arrayLine = params->theArray[request_index];
        rwlock_unlock(&array_mutex);

        int arrayLength = strlen(arrayLine);
        send_chars(params->socket, arrayLine, arrayLength);
    }

    return NULL;
}