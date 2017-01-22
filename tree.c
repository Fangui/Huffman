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
    printf("key->%c\n"/* , value->%d\n"*/, tree->key/*, tree->value*/);
    printTree(tree->left);
    printTree(tree->right);
  }
}

void freeTree(struct tree *tree)
{
  if(tree)
  {
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
  }
}
