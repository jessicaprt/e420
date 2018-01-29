CC = gcc

all: main matrixgen serialtester

main: multi_threaded_mult.c lab1_IO.o
	$(CC) multi_threaded_mult.c lab1_IO.o -g -o main

matrixgen: matrixgen.c
	$(CC) matrixgen.c -g -o matrixgen

serialtester: serialtester.c lab1_IO.o
	$(CC) serialtester.c lab1_IO.o -g -o serialtester

lab1_IO.o: lab1_IO.c
	$(CC) -g -c lab1_IO.c

clean:
	rm *.o matrixgen serialtester main