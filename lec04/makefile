
# Changing the Makefile for more files

all: myexe
	
myexe: prog1.o mysub.o myadd.o mydiv.o mymul.o ./d1/mymod.o
	gcc prog1.o mysub.o myadd.o mydiv.o mymul.o ./d1/mymod.o -o myexe

myadd.o: myadd.c
	gcc -c myadd.c
mysub.o: mysub.c
	gcc -c mysub.c
mydiv.o: mydiv.c 
	gcc -c mydiv.c 

prog1.o: prog1.c mymath.h d1/mymod.h
	gcc -c -I. -Id1/ prog1.c

include: ./d1/makefile

clean:
	@rm -f *.o
	@rm -f ./d1/mymod.o

install: myexe
	@cp myexe /usr/bin
	@chmod a+x /usr/bin/myexe
	@chmod og-w /usr/bin/myexe 
	@echo "myexe successfully installed in /usr/bin"

uninstall:
	@rm -f /usr/bin/myexe
	@echo "myexe successfully un-installed from /usr/bin"


