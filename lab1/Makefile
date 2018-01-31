CC = gcc
PACKAGE_NAME = 1396458-H42

lab: main matrixgen serialtester

main: main.c lab1_IO.o
	$(CC) main.c lab1_IO.o -g -o main -lpthread -lm

matrixgen: matrixgen.c
	$(CC) matrixgen.c -g -o matrixgen

serialtester: serialtester.c lab1_IO.o
	$(CC) serialtester.c lab1_IO.o -g -o serialtester

lab1_IO.o: lab1_IO.c
	$(CC) -g -c lab1_IO.c

clean:
	rm *.o matrixgen serialtester main

push:
	ssh e420 -t "mkdir -p lab1; rm -rf ./lab1/*"
	scp Makefile *.c *.h *.txt *.sh e420:~/lab1/

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile main.c lab1_IO.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)