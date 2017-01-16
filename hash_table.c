# include <stdint.h>
# include <string.h>

# include "hash_table.h"

uint32_t hash(char data)
{
  uint32_t h = 0;
  h += data;
  h *= 1025;
  h = (h ^ (h / 64));
  h *= 9;
  h = (h ^ (h / 2048));
  h *= 32769;
  return h;
}

struct htable *create_htable(size_t capacity)
{
  struct htable *hash = malloc(sizeof (struct htable));
  hash->size = 0;
  hash->capacity = capacity;
  hash->tab = calloc(hash->capacity,sizeof (struct pair*)); 
  return hash;
}

struct pair *access_htable(struct htable *htable, char key)
{
  uint32_t h = hash(key);
  uint32_t index = h % htable->capacity;

  struct pair *pair = htable->tab[index];
 
  while(pair && h != pair->hkey && key != pair->key)
    pair = pair->next;
  
  return pair;
}

void add_htable(struct htable *htable, char key, int value)
{
   uint32_t h = 0;
   uint32_t index = 0;

   float size = htable->size + 1;
   float capacity = htable->capacity;
  
   if(size / capacity > 0.75)
   {
    struct htable *htab = create_htable(htable->capacity * 2);
    htab->size = htable->size;
    for(size_t i = 0; i < htable->capacity; ++i)
     {
        struct pair *next = NULL;
        do {
        struct pair *p = htable->tab[i];
         if(!p)
           continue;
         h = p->hkey;
         index = h % (htab->capacity);

         struct pair *pa = p;
         next = p->next;
         
         pa->next = htab->tab[index];
         htab->tab[index] = pa;
       } while( next );
     } 
     htable->capacity *= 2;
     free(htable->tab);
     htable->tab = htab->tab;
     free(htab);
   } 
 
  h = hash(key); 
  index = h % htable->capacity;

  struct pair *insert = malloc(sizeof (struct pair));
  insert->key = key;
  insert->value = value;
  insert->hkey = h;

  insert->next = htable->tab[index];
  htable->tab[index] = insert;
  ++(htable->size);
}  

void remove_htable(struct htable *htable, char key)
{
  uint32_t index = hash(key) % htable->capacity;
  struct pair *pair = htable->tab[index];
  struct pair *prev = NULL;

  while(pair && key != pair->key)
  {
    prev = pair;
    pair = pair->next;
  }

  if(!prev)
  {
    if(pair)
    {
      free(pair);
      htable->tab[index] = NULL;
      --(htable->size);
    }
    return;
  }
  if(pair)
  {
    prev->next = pair->next;
    free(pair);
    --(htable->size);
  }
}
static void Free(struct pair *pair)
{
  if(pair)
  {
    Free(pair->next);
    free(pair);
  }
}


void clear_htable(struct htable *htable)
{
  for(size_t i = 0; i < htable->capacity; ++i)
  { 
    Free(htable->tab[i]);
    htable->tab[i] = NULL;
  }
  htable->size = 0;
}


