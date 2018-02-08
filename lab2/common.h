#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

extern const int READ_REQUEST_TYPE;
extern const int WRITE_REQUEST_TYPE;

void send_int(uint32_t socket, uint32_t request_type);
uint32_t receive_int(uint32_t socket);

void send_chars(uint32_t socket, char* chars, int len);
int receive_chars(uint32_t socket, char *out, int out_size, int stream_size);

int get_total_digits_of(int number);

#endif