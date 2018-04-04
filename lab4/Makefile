CC = gcc
MPICC = mpicc
CFLAGS = --std=c99
PACKAGE_NAME = 1396458-H42

IO_OBJ = Lab4_IO.o

lab: datatrim serialtester

main: main.c
	$(MPICC) $^ -g -o $@

datatrim: datatrim.c $(IO_OBJ)
	$(CC) $^ -g -o $@

serialtester: serialtester.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -g -o $@ -D LAB4_EXTEND -lm

$(IO_OBJ): Lab4_IO.c
	$(CC) $(CFLAGS) -g -c Lab4_IO.c -lm

clean:
	rm *.o *.out
	rm -f datagen serialtester original

push:
	ssh e420 -t "mkdir -p lab4; rm -rf ./lab4/*"
	scp Makefile *.c *.h *.sh *.txt e420:~/lab4/

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile original.c shared_parallel_dynamic.c shared_parallel_guided.c shared_parallel_static.c Lab3IO.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)