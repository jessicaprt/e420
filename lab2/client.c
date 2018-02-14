#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include "common.h"
#include "timer.h"

int array_size;
const int NUMBER_REQUESTS = 1000;

int get_random_int(int max) {
	return rand() % (max + 1);
}

void* request_handler(void* socket_param) {
	int socket = (int) socket_param;

	int request_type;
	int request_chance = get_random_int(100);

	if (request_chance < 5) {
		request_type = WRITE_REQUEST_TYPE;
	} else {
		request_type = READ_REQUEST_TYPE;
	}

	int request_index = get_random_int(array_size - 1);

	send_int(socket, request_type);
	send_int(socket, request_index);

	int message_size = receive_int(socket);
	char buffer[message_size];
	receive_chars(socket, buffer, message_size, message_size);

	printf("%s\n", buffer);
	close(socket);

	return NULL;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Ussage: %s port array_size\n", argv[0]);
		return -1;
	}

	int port_number = atoi(argv[1]);
	array_size = atoi(argv[2]);

	unsigned seed;
	srand((int) &seed);

	struct sockaddr_in sock_var;

	sock_var.sin_addr.s_addr=inet_addr("127.0.0.1");
	sock_var.sin_port= htons(port_number);
	sock_var.sin_family=AF_INET;

	pthread_t* thread_handles = malloc(NUMBER_REQUESTS * sizeof(pthread_t));

	double start_time, end_time;

	GET_TIME(start_time);

	int i = 0;
	for (i = 0; i < NUMBER_REQUESTS; i++) {
		int clientFileDescriptor=socket(AF_INET, SOCK_STREAM, 0);
		int connectionResult = connect(clientFileDescriptor, (struct sockaddr*) &sock_var, sizeof(sock_var));

		if (connectionResult < 0) {
			perror("socket creation failed");
			return -1;
		}

		pthread_create(&thread_handles[i], NULL, request_handler, (void*) clientFileDescriptor);
	}

	for (i = 0; i < NUMBER_REQUESTS; i++) {
		pthread_join(thread_handles[i], NULL);
	}

	GET_TIME(end_time);

	free(thread_handles);

	printf("Elapsed time: %f\n", end_time - start_time);

	return 0;
}