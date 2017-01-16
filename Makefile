CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -g -o huffman
LDFLAGS=
LDLIBS=
 
SRC= vector.c huffman.c hash_table.c tree.c

OBJ= ${SRC:.c=.o} 
all: huffman

huffman: ${OBJ} 
 
clean:
	rm -f ${OBJ}
	rm -f *.o
	rm huffman
