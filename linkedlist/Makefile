# Sample makefile for linked list implementation

SRC=src
HEADERS=include

SRC:=$(patsubst %.c,src/%.c, $(SRC))

CFLAGS=-Wall -Wextra -g

linkedlist: $(SRC) $(HEADERS)
	gcc -o $@ $(SRC) -I$(HEADERS)

clean:
	rm -f *~ *.o linkedlist
