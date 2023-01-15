# Sample makefile for linked list implementation

SRC=main.c common.c list.c binarysearch.c
HEADERS=include

SRC:=$(patsubst %.c,src/%.c, $(SRC))

CFLAGS=-Wall -Wextra -g

binarysearch: $(SRC) $(HEADERS)
	gcc -o $@ $(SRC) -I$(HEADERS) $(CLFAGS) -lm

clean:
	rm -f *~ *.o binarysearch
