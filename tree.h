# ifndef _TREE_H_
# define _TREE_H_

# include "hash_table.h"

struct tree
{
  struct tree *left, *right;
  char key;
  int value;
};

struct tree *newTree();

void printTree(struct tree *tree);

void freeTree(struct tree *tree);

# endif /* _TREE_HTABLE_H */
