CC = gcc
LAB_DIRECTORY = lab2
PACKAGE_NAME = 1396458-H42
PUSH_CONTENTS = Makefile *.c *.h *.txt
PACKAGE_CONTENTS = Makefile *.c *h

all: client server

client: client.c
	$(CC) -g client.c -o client

server: server.c
	$(CC) -g server.c -o server

clean:
	rm *.o

push:
	ssh e420 -t "mkdir -p $(LAB_DIRECTORY); rm -rf ./$(LAB_DIRECTORY)/*"
	scp $(PUSH_CONTENTS) e420:~/$(LAB_DIRECTORY)/

package:
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_CONTENTS)