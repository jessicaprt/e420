CC = gcc
PACKAGE_NAME = 1396458-H42

all: main matrixgen serialtester

main: main.c lab1_IO.o
	$(CC) multi_threaded_mult.c lab1_IO.o -g -o main

matrixgen: matrixgen.c
	$(CC) matrixgen.c -g -o matrixgen

serialtester: serialtester.c lab1_IO.o
	$(CC) serialtester.c lab1_IO.o -g -o serialtester

lab1_IO.o: lab1_IO.c
	$(CC) -g -c lab1_IO.c

clean:
	rm *.o matrixgen serialtester main

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile *.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)