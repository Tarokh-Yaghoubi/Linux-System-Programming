
# Changing the Makefile for more files

all: myexe
CC=gcc
CFLAGS= -std=c11 -O0 -Wall -g
LIBS = -lc
OBJS = myadd.o prog1.o mysub.o mydiv.o mymul.o ./d1/mymod.o
INSDIR = /usr/bin

myexe: $(OBJS)
	$(CC) -o myexe $(OBJS) $(LIBS)

myadd.o: myadd.c
	$(CC) -c myadd.c $(CFLAGS)
mysub.o: mysub.c
	$(CC) -c mysub.c $(CFLAGS)
mydiv.o: mydiv.c 
	$(CC) -c mydiv.c $(CFLAGS)

prog1.o: prog1.c mymath.h d1/mymod.h
	$(CC) -c $(CFLAGS) -I$(INCLUDES) -Id1/ prog1.c

include: ./d1/makefile

clean:
	-@rm -f $(OBJS)

install: myexe
	@if [ -d $(INSDIR) ]; \
	then\
		cp myexe $(INSDIR) && \
		chmod a+x $(INSDIR)/myexe && \
		chmod og-w $(INSDIR)/myexe && \
	        echo "myexe installed successfully in $(INSDIR)"; \
	fi

uninstall:
	@rm -f $(INSDIR)/myexe
	@echo "myexe successfully un-installed from $(INSDIR)"


