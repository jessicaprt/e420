#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>

#include "client_handler.h"

int get_total_digits_of(int number) {
	if (number == 0) {
		return 1;
	}
	return floor(log10(abs(number))) + 1;
}

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

int run_server(int port, char** the_array) {
			struct sockaddr_in sock_var;
	int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
	int clientFileDescriptor;
	int i;
	pthread_t t[20];

	sock_var.sin_addr.s_addr=inet_addr("127.0.0.1");
	sock_var.sin_port=3000;
	sock_var.sin_family=AF_INET;

	int bind_result = bind(serverFileDescriptor,(struct sockaddr*)&sock_var,sizeof(sock_var));

	if (bind_result < 0) {
		printf("Failed to create server socket.\n");
		return -1;
	}

	printf("nsocket has been created");
	listen(serverFileDescriptor,2000);

	while(1) {
		for(i = 0; i < 20; i++) {
			clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);
			printf("nConnected to client %dn",clientFileDescriptor);
			pthread_create(&t, NULL, handle_client, (void *)clientFileDescriptor);
		}
	}
	close(serverFileDescriptor);

	return 0;
}

int main() {
	char** theArray;
	int total = 100;
	int i =0;

	allocate_the_array(&theArray, total);

	for (i = 0; i < total; i++) {
		printf("%s\n", theArray[i]);
	}

	return run_server(3000, theArray);
}