# include "vector.h"

void printVect(struct vector *vect)
{
  for(size_t i = 0 ; i < vect->size; ++i)
    printf("t1->%c | t2->%d\n",vect->data[i]->t1, vect->data[i]->t2);
  printf("\n");
}

static void double_vector_size(struct vector *vect)
{
  if(vect->capacity == 0)
    vect->capacity = 1;
  
  while(vect->capacity <= vect->size)
  {
    vect->capacity *= 2;
    vect->data = realloc(vect->data, sizeof(struct Tuple) * vect->capacity);
  }
}

struct vector* vector_make(size_t capacity)
{
  struct vector *vect = malloc(sizeof(struct vector));
  vect->capacity = capacity;
  vect->size = 0;
  vect->data = malloc(sizeof(struct Tuple) * capacity);
  return vect;
}

void vector_push(struct vector *vect, struct Tuple *tup)
{
  double_vector_size(vect);

  size_t i = 0;
  while(i < vect->size && tup->t2 <= vect->data[i]->t2)
    ++i;

  for(size_t j = vect->size; j > i; --j)
    vect->data[j] = vect->data[j - 1];

  vect->data[i] = tup;
  ++(vect->size);
}

void freeVect(struct vector *vect)
{
  for(size_t i = 0; i < vect->size; ++i)
    free(vect->data[i]);

  free(vect->data);
  free(vect);
}
