# include "tree.h"

struct tree *newTree()
{
  struct tree *tree = malloc(sizeof(struct tree));
  tree->left = NULL;
  tree->right = NULL;
}

struct tree *vectToTree(struct vector *vect)
{
  struct tree *tree = newTree();
  

}
