CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -O3 -o Hex
LDFLAGS=
LDLIBS=
 
SRC= Hex.c matrix.c tree.c vector.c AI.c

OBJ= ${SRC:.c=.o} 
all: Hex

Hex: ${OBJ} 
 
clean:
	rm -f ${OBJ}
	rm -f *.o
	rm Hex
