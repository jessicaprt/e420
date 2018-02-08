CC = gcc
LAB_DIRECTORY = lab2
PACKAGE_NAME = 1396458-H42
PUSH_CONTENTS = Makefile *.c *.h *.txt
PACKAGE_CONTENTS = Makefile *.c *h

all: client server_single_mutex.out

client: client.c
	$(CC) -g client.c -o $@

server_multiple_mutex.out: server.c multiple_mutex_client_handler.o common.o
	$(CC) -g server.c multiple_mutex_client_handler.o common.o -o $@

server_single_mutex.out: server.c single_mutex_client_handler.o common.o
	$(CC) -g server.c single_mutex_client_handler.o common.o -o $@

multiple_mutex_client_handler.o: multiple_mutex_client_handler.c
	$(CC) -g -c multiple_mutex_client_handler.c -o $@

single_mutex_client_handler.o: single_mutex_client_handler.c
	$(CC) -g -c single_mutex_client_handler.c -o $@

common.o: common.c
	$(CC) -g -c common.c -o $@

clean:
	rm *.out *.o client

push:
	ssh e420 -t "mkdir -p $(LAB_DIRECTORY); rm -rf ./$(LAB_DIRECTORY)/*"
	scp $(PUSH_CONTENTS) e420:~/$(LAB_DIRECTORY)/

package:
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_CONTENTS)