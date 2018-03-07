CC = gcc
CFLAGS = --std=c99
PACKAGE_NAME = 1396458-H42

IO_OBJ = Lab3IO.o

lab: original datagen serialtester

original: original.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -fopenmp -g -o $@

datagen: datagen.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -g -o $@

serialtester: serialtester.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -g -o $@ -lm

$(IO_OBJ): Lab3IO.c
	$(CC) $(CFLAGS) -g -c Lab3IO.c

clean:
	rm *.o datagen serialtester original

push:
	ssh e420 -t "mkdir -p lab3; rm -rf ./lab3/*"
	scp Makefile *.c *.h *.txt *.sh e420:~/lab3/

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile main.c Lab3IO.c main_executable.out *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)