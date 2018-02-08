#include <unistd.h>
#include <sys/socket.h>
#include <math.h>
#include "common.h"

#define min(a, b) ( (a) < (b) ? (a) : (b) )

const int READ_REQUEST_TYPE = 0;
const int WRITE_REQUEST_TYPE = 1;

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