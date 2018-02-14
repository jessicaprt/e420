#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include "common.h"
#include "timer.h"

#define min(a, b) ( (a) < (b) ? (a) : (b) )

const int READ_REQUEST_TYPE = 0;
const int WRITE_REQUEST_TYPE = 1;
const int LENGTH_OF_MODIFIED_LINE_WITHOUT_INDEX = 45;

double memory_latency = 0;
int initialized = 0;
pthread_mutex_t memory_latency_mutex;

void send_int(uint32_t socket, uint32_t request_type) {
    uint32_t out_request_type = htons(request_type);
    write(socket, &out_request_type, sizeof(uint32_t));
}

uint32_t receive_int(uint32_t socket) {
    uint32_t in_request_type;
    read(socket, &in_request_type, sizeof(uint32_t));
    in_request_type = ntohs(in_request_type);

    return in_request_type;
}

void send_chars(uint32_t socket, char* chars, int len) {
     write(socket, chars, len);
}

int receive_chars(uint32_t socket, char *out, int out_size, int stream_size) {
    int bytes_read = read(socket, out, stream_size);
    out[min(out_size - 1, stream_size)] = '\0';

    return bytes_read;
}

int get_total_digits_of(int number) {
	if (number == 0) {
		return 1;
	}
	return floor(log10(abs(number))) + 1;
}

void read_and_send_line(char** theArray, uint32_t socket, int index) {
    double end_time, start_time;

    GET_TIME(start_time);
    int arrayLength = strlen(theArray[index]) + 1; // + 1 for the null terminator
    send_int(socket, arrayLength); // send size of line
    send_chars(socket, theArray[index], arrayLength); // send line itself

    GET_TIME(end_time);
    record_memory_latency(start_time, end_time);
}

void mark_line_as_modified(char** theArray, int index) {
    int newLength = LENGTH_OF_MODIFIED_LINE_WITHOUT_INDEX + get_total_digits_of(index);

    double end_time, start_time;

    GET_TIME(start_time);
    theArray[index] = realloc(theArray[index], newLength * sizeof(char));
    snprintf(theArray[index], newLength, "String %d has been modified by a write request", index);
    GET_TIME(end_time);

    record_memory_latency(start_time, end_time);
}

void record_memory_latency(double start_time, double end_time) {
    if (initialized == 0) {
        pthread_mutex_init(&memory_latency_mutex, NULL);
        initialized = 1;
    }

    pthread_mutex_lock(&memory_latency_mutex);
    memory_latency += (end_time - start_time);
    pthread_mutex_unlock(&memory_latency_mutex);
}

double get_total_memory_latency() {
    return memory_latency;
}