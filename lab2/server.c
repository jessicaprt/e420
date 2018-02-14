#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
#include "common.h"
#include "client_handler.h"

int LENGTH_OF_INITAL_LINE_WITHOUT_INDEX = 27; // do this better
const int NUMBER_REQUESTS = 1000;

void allocate_the_array(char*** pointer_to_the_array, int total_lines) {
	char** the_array = malloc(total_lines * sizeof(char*));

	int i;
	for (i = 0; i < total_lines; i++) {
		int length_of_line = LENGTH_OF_INITAL_LINE_WITHOUT_INDEX + get_total_digits_of(i);
		the_array[i] = malloc(length_of_line * sizeof(char));
		snprintf(the_array[i], length_of_line, "String %d: the initial value", i);
	}

	*pointer_to_the_array = the_array;
}

void free_the_array(char** the_array, int total_lines) {
	int i;
	for (i = 0; i < total_lines; i++) {
		free(the_array[i]);
	}
	free(the_array);
}

int run_server(int port, char** the_array, int array_length) {
	struct sockaddr_in sock_var;

	sock_var.sin_family = AF_INET;
	sock_var.sin_addr.s_addr = INADDR_ANY;
	sock_var.sin_port = htons(port);

	int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEPORT, &(int){ 1 }, sizeof(int));
	setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));

	int bind_result = bind(serverFileDescriptor, (struct sockaddr*) &sock_var, sizeof(sock_var));

	if (bind_result < 0) {
		perror("Failed to create server socket");
		return -1;
	}

	printf("nsocket has been created\n");
	listen(serverFileDescriptor, 2000);

	set_up_client_handler(array_length);

	pthread_t* thread_handles = malloc(NUMBER_REQUESTS * sizeof(pthread_t));
	handle_client_params_t* thread_params = malloc(NUMBER_REQUESTS * sizeof(handle_client_params_t));

	int i = 0;
	for (i = 0; i < NUMBER_REQUESTS; i++) {
		int clientFileDescriptor = accept(serverFileDescriptor, NULL, NULL);
		printf("nConnected to client %d\n", clientFileDescriptor);

		handle_client_params_t* params = &thread_params[i];
		params->socket = clientFileDescriptor;
		params->theArray = the_array;

		pthread_create(&thread_handles[i], NULL, handle_client, (void *)params);
	}


	for (i = 0; i < NUMBER_REQUESTS; i++) {
		pthread_join(thread_handles[i], NULL);
	}

	free(thread_handles);
	free(thread_params);

	close(serverFileDescriptor);

	printf("%f\n", get_total_memory_latency());

	return 0;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage: %s port array_size\n", argv[0]);
		return -1;
	}

	char** theArray;
	int port = atoi(argv[1]);
	int total = atoi(argv[2]);
	int i = 0;

	allocate_the_array(&theArray, total);
	return run_server(port, theArray, total);
}