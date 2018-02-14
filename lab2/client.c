#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include "common.h"

void* request_handler(void* socket_param) {
	int socket = (int) socket_param;

	send_int(socket, 0);
	send_int(socket, 5);

	int message_size = receive_int(socket);
	char buffer[message_size];
	receive_chars(socket, buffer, message_size, message_size);

	printf("%s\n", buffer);
	close(socket);

	return NULL;
}

int main() {
	struct sockaddr_in sock_var;
	int clientFileDescriptor=socket(AF_INET, SOCK_STREAM, 0);

	sock_var.sin_addr.s_addr=inet_addr("127.0.0.1");
	sock_var.sin_port=3000;
	sock_var.sin_family=AF_INET;

	int connectionResult = connect(clientFileDescriptor, (struct sockaddr*) &sock_var, sizeof(sock_var));
	if (connectionResult < 0) {
		perror("socket creation failed");
		return -1;
	}

	printf("Connected to server %dn",clientFileDescriptor);
	pthread_t* client_thread = malloc(sizeof(pthread_t));

	pthread_create(client_thread, NULL, request_handler, (void*) clientFileDescriptor);

	return 0;
}