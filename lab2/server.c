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
	int bind_result = bind(serverFileDescriptor, (struct sockaddr*) &sock_var, sizeof(sock_var));

	if (bind_result < 0) {
		perror("Failed to create server socket");
		return -1;
	}

	printf("nsocket has been created\n");
	listen(serverFileDescriptor, 2000);

	set_up_client_handler(array_length);

	while(1) {
		int clientFileDescriptor = accept(serverFileDescriptor, NULL, NULL);
		printf("nConnected to client %d\n", clientFileDescriptor);

		pthread_t* pthread = malloc(sizeof(pthread_t));
		handle_client_params_t* params = malloc(sizeof(handle_client_params_t));
		params->socket = clientFileDescriptor;
		params->theArray = the_array;

		pthread_create(pthread, NULL, handle_client, (void *)params);
	}
	close(serverFileDescriptor);

	return 0;
}

int main() {
	char** theArray;
	int total = 100;
	int i =0;

	allocate_the_array(&theArray, total);
	return run_server(3000, theArray, total);
}