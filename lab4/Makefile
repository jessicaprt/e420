CC = gcc
MPICC = mpicc
CFLAGS = --std=c99
PACKAGE_NAME = 1396458-H42

IO_OBJ = Lab4_IO.o

lab: main datatrim serialtester

main: main.c $(IO_OBJ)
	$(MPICC) $^ -g -o $@

datatrim: datatrim.c $(IO_OBJ)
	$(CC) $^ -g -o $@ -lm

serialtester: serialtester.c $(IO_OBJ)
	$(CC) $(CFLAGS) $^ -g -o $@ -lm

$(IO_OBJ): Lab4_IO.c
	$(CC) $(CFLAGS) -g -c Lab4_IO.c

clean:
	rm *.o *.out
	rm -f datagen serialtester original

push:
	@echo Syncing to main system
	rsync -arvz -e "ssh" --progress Makefile *.c *.h *.sh *.txt e420:~/lab4/

	@echo Syncing main system with the rest of the cluster
	ssh e420 -t cd "lab4/; \
		rsync -arvz -e "ssh" --progress Makefile *.c *.h *.sh *.txt 192.168.0.173:~/lab4/; \
		rsync -arvz -e "ssh" --progress Makefile *.c *.h *.sh *.txt 192.168.0.38:~/lab4/; \
		rsync -arvz -e "ssh" --progress Makefile *.c *.h *.sh *.txt 192.168.0.27:~/lab4/"

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile original.c shared_parallel_dynamic.c shared_parallel_guided.c shared_parallel_static.c Lab3IO.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)