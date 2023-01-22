# Sample makefile for linked list implementation

SRC=binarysearch.c compare.c
HEADERS=include

SRC:=$(patsubst %.c,src/%.c, $(SRC))

CFLAGS=-Wall -Wextra -g

# $(CLFAGS) -lm

binarysearch: src/main.c $(SRC) $(HEADERS)
	gcc -o $@ src/main.c $(SRC) -I$(HEADERS)
sysfind: src/sysfind.c $(SRC) $(HEADERS)
	gcc -o $@ src/sysfind.c $(SRC) -I$(HEADERS)
clean:
	rm -f *~ *.o binarysearch sysfind
