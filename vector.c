# include <stdio.h>
# include <stdlib.h>
# include "vector.h"

void print_vect(int *vect,size_t j)
{
  for(size_t i = 0;i < j;++i)
    printf("%d |",vect[i]);
  printf("\n");
}

static void double_vector_size(struct vector *vect)
{
  if(vect->capacity == 0)
    vect->capacity = 1;
  
  while(vect->capacity <= vect->size)
  {
    vect->capacity *= 2;
    vect->data = realloc(vect->data, sizeof(int) * vect->capacity);
  }
}

struct vector* vector_make(size_t capacity)
{
  struct vector *vect = malloc(sizeof(struct vector));
  vect->capacity = capacity;
  vect->size = 0;
  vect->data = malloc(sizeof(int) * capacity);
  return vect;
}

void vector_push_back(struct vector *vect, int x)
{
  double_vector_size(vect);
  
  vect->data[vect->size] = x;
  ++(vect->size);
  
}

int vector_pop_back(struct vector *vect, int *x)
{
  if(vect->size > 0)
  {
    --(vect->size);
    *x = vect->data[vect->size];
    return 1;
  }

  return 0;
}

void vector_push_front(struct vector *vect, int x)
{
  double_vector_size(vect);

  for(size_t i = vect->size; i > 0; --i)
    vect->data[i] = vect->data[i - 1];
  
  vect->data[0] = x;
  ++(vect->size);
}

int vector_pop_front(struct vector *vect, int *x)
{
  if(vect->size> 0)
  {
    *x = vect->data[0];
    --(vect->size);
    for(size_t i = 0; i < vect->size ; ++i)
      vect->data[i] = vect->data[i + 1];
    return 1;
  }
  return 0;
}

int vector_insert_at(struct vector *vect, size_t pos, int x)
{
  if(pos > vect->size)
    return 0;

  double_vector_size(vect);
  
  ++(vect->size); 
  for(size_t i = pos; i < vect->size; ++i)
    vect->data[i + 1] = vect->data[i];
  vect->data[pos] = x;
  
  return 1;
}

int vector_extract_at(struct vector *vect, size_t pos, int *x)
{
  if(vect->size == 0 || pos >= vect->size)
    return 0;
  
  *x = vect->data[pos];
  for(;pos < vect->size; ++pos)
    vect->data[pos] = vect->data[pos + 1];

  --(vect->size);
 
  return 1;
}

struct vector *vector_clone(struct vector *vect)
{
  struct vector *copy = malloc(sizeof(struct vector));
  copy->capacity = vect->capacity;
  copy->size = vect->size;
  copy->data = malloc(sizeof(int) * copy->size);
  for(size_t i = 0; i < copy->size; ++i)
    copy->data[i] = vect->data[i];
  
  return copy;
}
/*
int main()
{
  int *x = malloc(sizeof(int));
  struct vector* vect = vector_make(1);
  vector_push_back(vect, 5);
  vector_push_back(vect, 9);
  vector_push_front(vect,3);
  
  print_vect(vect->data,vect->size);

  vector_pop_back(vect,x);
  printf("%d\n", *x);

  vector_insert_at(vect, 2, 9);
  vector_insert_at(vect, 3, 12);
  vector_insert_at(vect, 4, 15);
  
  vector_extract_at(vect, 4, x);
  print_vect(vect->data, vect->size);
  
  struct vector *clone = vector_clone(vect);
  
  print_vect(clone->data,clone->size);

  free(vect->data);
  free(vect);
  free(clone->data);
  free(clone);
  free(x);
}*/
