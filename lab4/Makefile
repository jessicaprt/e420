CC = gcc
MPICC = mpicc
CFLAGS = --std=c99
PACKAGE_NAME = 1396458-H42
PUSH_FILES = Makefile *.c *.h *.sh *.txt
IO_OBJ = Lab4_IO.o

all-clusters:
	ssh e420 -t "cd lab4/; make lab; \
		ssh 192.168.0.173 -t 'cd lab4/; make lab'; \
		ssh 192.168.0.38 -t 'cd lab4/; make lab'; \
		ssh 192.168.0.27 -t 'cd lab4/; make lab'"

lab: main datatrim serialtester

main: main.c $(IO_OBJ)
	$(MPICC) $^ -g -o $@ -lm

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
	rsync -arvz -e "ssh" --progress $(PUSH_FILES) e420:~/lab4/

	@echo Syncing main system with the rest of the cluster
	ssh e420 -t cd "lab4/; \
		rsync -arvz -e "ssh" --progress $(PUSH_FILES) 192.168.0.173:~/lab4/; \
		rsync -arvz -e "ssh" --progress $(PUSH_FILES) 192.168.0.38:~/lab4/; \
		rsync -arvz -e "ssh" --progress $(PUSH_FILES) 192.168.0.27:~/lab4/"

push-and-build: push all-clusters

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp Makefile original.c shared_parallel_dynamic.c shared_parallel_guided.c shared_parallel_static.c Lab3IO.c *.h *.txt $(PACKAGE_NAME)/
	@zip -r $(PACKAGE_NAME).zip $(PACKAGE_NAME)/
	@rm -rf $(PACKAGE_NAME)