#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "client_handler.h"
#include "common.h"

pthread_mutex_t array_mutex;

void set_up_client_handler(int array_length) {
    pthread_mutex_init(&array_mutex, NULL);
}

void* handle_client(void* handle_client_params) {
    handle_client_params_t* params = (handle_client_params_t*) handle_client_params;

    int request_type = receive_int(params->socket);
    int request_index = receive_int(params->socket);

    if (request_type == READ_REQUEST_TYPE) {
        pthread_mutex_lock(&array_mutex);
        read_and_send_line(params->theArray, params->socket, request_index);
        pthread_mutex_unlock(&array_mutex);
    } else if (request_type == WRITE_REQUEST_TYPE) {
        pthread_mutex_lock(&array_mutex);
        mark_line_as_modified(params->theArray, request_index);
        read_and_send_line(params->theArray, params->socket, request_index);
        pthread_mutex_unlock(&array_mutex);
    }

    close(params->socket);

    return NULL;
}