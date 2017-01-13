# ifndef _TREE_H_
# define _TREE_H_

# include "hash_table.h"

struct tree
{
  struct tree *left, *right;
  char key;
  int value;
}

struct tree *newTree();



# endif /* _TREE_HTABLE_H */
