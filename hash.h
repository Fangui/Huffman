# ifndef _HASH_H_
# define _HASH_H_
 
# include "hash_table.h"
 
struct pair_ {
  uint32_t             hkey;
  char                 key;
  char                 *data;
  size_t               size;
  struct pair_          *next;
};
 
struct htab {
  size_t                size, capacity;
  struct pair_         **tab;
};
 
uint32_t hash_(char data);
 
struct htab *create_htab(size_t capacity);

struct pair_ *access_htab(struct htab *htable, char key);
 
void add_htab(struct htab *htable, char key, char *data, size_t size);

void clear_htab(struct htab *htable);
 
# endif /* _HASH_H_ */
