# ifndef _HASH_TABLE_H_
# define _HASH_TABLE_H_
 
# include <stdint.h>
# include "vector.h"
 
struct pair {
  uint32_t             hkey;
  char                 key;
  int                  value;
  struct pair          *next;
};
 
struct htable {
  size_t                size, capacity;
  struct pair         **tab;
};
 
uint32_t hash(char data);
 
struct htable *create_htable(size_t capacity);
 
struct pair *access_htable(struct htable *htable, char key);
 
int add_htable(struct htable *htable, char key, int value);
 
void remove_htable(struct htable *htable, char key);
 
void clear_htable(struct htable *htable);
 
# endif /* _HASH_TABLE_H_ */
