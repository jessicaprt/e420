CC = gcc
LAB_DIRECTORY = lab2
PACKAGE_NAME = 1396458-H42
PUSH_CONTENTS = Makefile *.c *.h *.py
PACKAGE_CONTENTS = Makefile *.txt *.c *.h

all: client server_single_mutex.out server_multiple_mutex.out server_multiple_rwlock.out server_single_rwlock.out

client: client.c common.o
	$(CC) -g client.c common.o -lm -pthread -o $@

server_multiple_mutex.out: server.c multiple_mutex_client_handler.o common.o
	@echo "Building multiple mutex based server"
	$(CC) -g server.c multiple_mutex_client_handler.o common.o -lm -pthread -o $@

server_single_mutex.out: server.c single_mutex_client_handler.o common.o
	@echo "Building single mutex based server"
	$(CC) -g server.c single_mutex_client_handler.o common.o -lm -pthread -o $@

server_multiple_rwlock.out: server.c multiple_rwlock_client_handler.o common.o rw_lock.o
	@echo "Building multiple rwlock based server"
	$(CC) -g server.c multiple_rwlock_client_handler.o common.o rw_lock.o -lm -pthread -o $@

server_single_rwlock.out: server.c single_rwlock_client_handler.o common.o rw_lock.o
	@echo "Building single rwlock based server"
	$(CC) -g server.c single_rwlock_client_handler.o common.o rw_lock.o -lm -pthread -o $@

multiple_mutex_client_handler.o: multiple_mutex_client_handler.c rw_lock.o
	$(CC) -g -c multiple_mutex_client_handler.c -o $@

single_mutex_client_handler.o: single_mutex_client_handler.c
	$(CC) -g -c single_mutex_client_handler.c -o $@

multiple_rwlock_client_handler.o: multiple_rwlock_client_handler.c
	$(CC) -g -c multiple_rwlock_client_handler.c -o $@

single_rwlock_client_handler.o: single_rwlock_client_handler.c
	$(CC) -g -c single_rwlock_client_handler.c -o $@

common.o: common.c
	$(CC) -g -c $^ -o $@

rw_lock.o: rw_lock.c
	$(CC) -g -c $^ -o $@

clean:
	rm -rf *.out *.o *.dSYM client

push:
	ssh e420 -t "mkdir -p $(LAB_DIRECTORY); rm -rf ./$(LAB_DIRECTORY)/*"
	scp $(PUSH_CONTENTS) e420:~/$(LAB_DIRECTORY)/

package:
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_CONTENTS)