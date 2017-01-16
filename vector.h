# ifndef VECTOR_H_
# define VECTOR_H_
 
# include "tree.h"

struct Tuple
{
  char t1;
  int t2;
};

struct vector {
  size_t        capacity, size;
  struct tree **data;
};
 
struct vector* vector_make(size_t capacity);
 
void vector_push(struct vector *vect, struct tree *tree);
 
void freeVect(struct vector *vect);

void printVect(struct vector *vect);
 
# endif
