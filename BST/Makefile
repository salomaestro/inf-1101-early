# Sample makefile for linked list implementation

SRC=main.c binarysearch.c
HEADERS=include

SRC:=$(patsubst %.c,src/%.c, $(SRC))

CFLAGS=-Wall -Wextra -g

# $(CLFAGS) -lm

binarysearch: $(SRC) $(HEADERS)
	gcc -o $@ $(SRC) -I$(HEADERS)

clean:
	rm -f *~ *.o binarysearch
