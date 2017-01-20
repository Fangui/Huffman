# include "vector.h"

void printVect(struct vector *vect)
{
  for(size_t i = 0 ; i < vect->size; ++i)
    printf("t1->%c | t2->%d\n",vect->data[i]->key, vect->data[i]->value);
  printf("\n");
}

static void double_vector_size(struct vector *vect)
{
  if(vect->capacity == 0)
    vect->capacity = 1;
  
  while(vect->capacity <= vect->size)
  {
    vect->capacity *= 2;
    vect->data = realloc(vect->data, sizeof(struct tree) * vect->capacity);
  }
}

struct vector* vector_make(size_t capacity)
{
  struct vector *vect = malloc(sizeof(struct vector));
  vect->capacity = capacity;
  vect->size = 0;
  vect->data = malloc(sizeof(struct tree) * capacity);
  return vect;
}

void vector_push(struct vector *vect, struct tree *tree)
{
  double_vector_size(vect);

  size_t i = 0;
  while(i < vect->size && tree->value < vect->data[i]->value)
    ++i;

  for(size_t j = vect->size; j > i; --j)
    vect->data[j] = vect->data[j - 1];

  vect->data[i] = tree;
  ++(vect->size);
}

void freeVect(struct vector *vect)
{
  for(size_t i = 0; i < vect->size; ++i)
    free(vect->data[i]);

  free(vect->data);
  free(vect);
}
