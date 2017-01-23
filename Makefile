CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -O3 -o huffman
LDFLAGS=
LDLIBS=
 
SRC= hash.c hash_table.c huffman.c tree.c vector.c 

OBJ= ${SRC:.c=.o} 
all: huffman

huffman: ${OBJ} 
 
clean:
	rm -f ${OBJ}
	rm -f *.o
	rm huffman
