# include "tree.h"

struct tree *newTree()
{
  struct tree *tree = malloc(sizeof(struct tree));
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

void printTree(struct tree *tree)
{
  if(tree)
  {
    printf("key->%c, value->%d\n", tree->key, tree->value);
    printTree(tree->left);
    printTree(tree->right);
  }
}

