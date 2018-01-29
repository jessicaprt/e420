CC = gcc

all: main matrixgen serialtester

main: multi_threaded_mult.c
	$(CC) multi_threaded_mult.c lab1_IO.o -o main
matrixgen: matrixgen.c
	$(CC) matrixgen.c -o matrixgen

serialtester: serialtester.c lab1_IO.o
	$(CC) serialtester.c lab1_IO.o -o serialtester

lab1_IO.o: lab1_IO.c
	$(CC) -c lab1_IO.c

clean:
	rm *.o matrixgen serialtester