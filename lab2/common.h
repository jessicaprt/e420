#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

extern const int READ_REQUEST_TYPE;
extern const int WRITE_REQUEST_TYPE;

// socket utils
void send_int(uint32_t socket, uint32_t request_type);
uint32_t receive_int(uint32_t socket);

void send_chars(uint32_t socket, char* chars, int len);
int receive_chars(uint32_t socket, char *out, int out_size, int stream_size);

// general utils
int get_total_digits_of(int number);

// the array utils
void read_and_send_line(char** theArray, uint32_t socket, int index);
void mark_line_as_modified(char** theArray, int index);

// memory_latency_recording
void record_memory_latency(double end_time, double start_time);
double get_total_memory_latency();

#endif