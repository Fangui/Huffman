# ifndef VECTOR_H_
# define VECTOR_H_
 
# include <stdlib.h>
# include <stdio.h>

struct Tuple
{
  char t1;
  int t2;
};

struct vector {
  size_t        capacity, size;
  struct Tuple **data;
};
 
struct vector* vector_make(size_t capacity);
 
void vector_push(struct vector *vect, struct Tuple *tup);
 
void freeVect(struct vector *vect);

void printVect(struct vector *vect);
 
# endif
