# include "hash.h"

uint32_t hash_(char data)
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

struct htab *create_htab(size_t capacity)
{
  struct htab *hash = malloc(sizeof (struct htab));
  hash->size = 0;
  hash->capacity = capacity;
  hash->tab = calloc(hash->capacity,sizeof (struct pair_*)); 
  return hash;
}

struct pair_ *access_htab(struct htab *htable, char key)
{
  uint32_t h = hash_(key);
  uint32_t index = h % htable->capacity;

  struct pair_ *pair = htable->tab[index];
 
  while(pair && h != pair->hkey && key != pair->key)
    pair = pair->next;
  
  return pair;
}

void add_htab(struct htab *htable, char key, char *data, size_t len)
{
   uint32_t h = 0;
   uint32_t index = 0;

   float size = htable->size + 1;
   float capacity = htable->capacity;
  
   if(size / capacity > 0.75)
   {
    struct htab *htab = create_htab(htable->capacity * 2);
    htab->size = htable->size;
    for(size_t i = 0; i < htable->capacity; ++i)
     {
        struct pair_ *next = NULL;
        do {
        struct pair_ *p = htable->tab[i];
         if(!p)
           continue;
         h = p->hkey;
         index = h % (htab->capacity);

         struct pair_ *pa = p;
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
 
  h = hash_(key); 
  index = h % htable->capacity;

  struct pair_ *insert = malloc(sizeof (struct pair_));
  insert->key= key;
  insert->data = data;
  insert->size = len;
  insert->hkey = h;

  insert->next = htable->tab[index];
  htable->tab[index] = insert;
  ++(htable->size);
}
  
static void toFree(struct pair_ *pair)
{
  if(pair)
  {
    toFree(pair->next);
    free(pair->data);
    free(pair);
  }
}


void clear_htab(struct htab *htable)
{
  for(size_t i = 0; i < htable->capacity; ++i)
  { 
    toFree(htable->tab[i]);
    htable->tab[i] = NULL;
  }
  htable->size = 0;
  free(htable->tab);
  free(htable);
}


