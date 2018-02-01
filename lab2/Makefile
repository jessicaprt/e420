CC = gcc
LAB_DIRECTORY = lab2
PACKAGE_NAME = 1396458-H42

clean:
	rm *.o

push:
	ssh e420 -t "mkdir -p $(LAB_DIRECTORY); rm -rf ./$(LAB_DIRECTORY)/*"
	scp Makefile *.c *.h *.txt e420:~/$(LAB_DIRECTORY)/

package:
	@zip -r $(PACKAGE_NAME).zip Makefile *.c *h