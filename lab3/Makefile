CC = gcc
CFLAGS = --std=c99
PACKAGE_NAME = 1396458-H42

IO_OBJ = Lab3IO.o

all: original.out shared_parallel_guided.out shared_parallel_static.out shared_parallel_dynamic.out

lab: original.out shared_parallel_guided.out shared_parallel_static.out shared_parallel_dynamic.out datagen serialtester

original.out: original.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -fopenmp -g -o $@

shared_parallel_guided.out: shared_parallel_guided.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -fopenmp -g -o $@

shared_parallel_static.out: shared_parallel_static.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -fopenmp -g -o $@

shared_parallel_dynamic.out: shared_parallel_dynamic.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -fopenmp -g -o $@

datagen: datagen.c $(IO_OBJ)
	$(CC) $^ -g -o $@

serialtester: serialtester.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -g -o $@ -lm

$(IO_OBJ): Lab3IO.c
	$(CC) $(CFLAGS) -g -c Lab3IO.c

clean:
	rm *.o *.out
	rm -f datagen serialtester original

push:
	ssh e420 -t "mkdir -p lab3; rm -rf ./lab3/*"
	scp Makefile *.c *.h *.sh *.py *.txt e420:~/lab3/

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile original.c shared_parallel_dynamic.c shared_parallel_guided.c shared_parallel_static.c Lab3IO.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)