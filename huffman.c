# include "huffman.h"

struct vector *buildFrequency(char *data)
{
  struct vector *vect = vector_make(100);
  struct htable *htab = create_htable(8);
  struct pair *pair = NULL, *insert = NULL;
  struct Tuple *tup = NULL;

  while(*data != '\0')
  {
    pair = access_htable(htab, *data);
    if(pair)
      ++pair->value;
    else
      add_htable(htab, *data, 1);
    ++data;
  }

  for(size_t i = 0; i < htab->capacity; ++i)
  {
    insert = htab->tab[i];
    while(insert)
    {
      tup = malloc(sizeof(struct Tuple));
      tup->t1 = insert->key;
      tup->t2 = insert->value;
      vector_push(vect, tup);
      insert = insert->next;
    }
    
  }
  return vect;
}



int main()
{
  struct vector *vect = buildFrequency("bbaabtttaabtctce");
  printVect(vect);
  return 0;
}
