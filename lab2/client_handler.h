#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <stdint.h>

typedef struct {
    uint32_t socket;
    char** theArray;
} handle_client_params_t;

// This functions allows you to set up state before handling
// any clients
void set_up_client_handler(int array_length);

// This function expects a handle_client_params_t to be passed
// in as the parameters to the function
void* handle_client(void* handle_client_parms);

#endif