# Sample makefile for linked list implementation

SRC=main.c hashtable.c
HEADERS=include

SRC:=$(patsubst %.c,src/%.c, $(SRC))

CFLAGS=-Wall -Wextra -g

# $(CLFAGS) -lm

hashtable: $(SRC) $(HEADERS)
	gcc -o $@ $(SRC) -I$(HEADERS)

clean:
	rm -f *~ *.o hashtable
