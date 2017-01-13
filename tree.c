# include "tree.h"

struct tree *newTree()
{
  struct tree *tree = malloc(sizeof(struct tree));
  tree->left = NULL;
  tree->right = NULL;
}


