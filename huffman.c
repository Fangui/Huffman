# include "huffman.h"

/*=================================COMPRESSION================================*/

struct vector *buildFrequency(char *data)
{
  struct vector *vect = vector_make(100);
  struct htable *htab = create_htable(8);
  struct pair *pair = NULL, *insert = NULL;
  struct tree *tree = NULL;

  while(*data != '\0')
  {
    pair = access_htable(htab, *data);
    if(pair)
      ++pair->value;
    else
      add_htable(htab, *data, 1);
    ++data;
  }

  for(size_t i = 0; i < htab->capacity; ++i)
  {
    insert = htab->tab[i];
    while(insert)
    {
      tree = newTree();
      tree->key = insert->key;
      tree->value = insert->value;
      vector_push(vect, tree);
      insert = insert->next;
    }    
  }
  clear_htable(htab);
  return vect;
}

struct tree *huffmanTree(struct vector *vect)
{
  struct tree *tree = NULL;
  while(vect->size > 1)
  {
    tree = malloc(sizeof(struct tree));
    tree->left = vect->data[vect->size - 2];
    tree->right = vect->data[vect->size - 1];
    tree->value = tree->left->value + tree->right->value;
    tree->key = ' ';
    vect->size -= 2;
    vector_push(vect, tree);
  }
  return tree;
}

char *encodeData_rec(struct tree *tree, char c, char *occ, size_t size, size_t capacity)
{
  if(tree && !tree->left)
  {
    if(tree->key == c)
      return occ;
    return "no code found";
  }
  if(size + 1 >= capacity)
  {
    capacity *= 2;
    occ = realloc(occ, capacity);
  }
  occ[size + 1] = '\0';
  occ[size] = '0';
  char *occ_rec = encodeData_rec(tree->left, c, occ, size + 1, capacity);
  if( strcmp(occ_rec, "no code found") )
  {
    occ = realloc(occ, size + 1);
    return occ_rec;
  }
  occ[size] = '1';
  return encodeData_rec(tree->right, c, occ, size + 1, capacity);
}

char *encodeData(struct tree *tree, char *data)
{
  char *s = calloc(1 ,sizeof(char)), *occ = NULL;
  while(*data != '\0')
  {
    occ = calloc(2, sizeof(char));
    s = strcat(s, encodeData_rec(tree, *data, occ, 0, 4));
    ++data;
  }
  return s;
}

int main()
{
  struct vector *vect = buildFrequency("bbaabtttaabtctce");
  struct tree *tree = huffmanTree(vect);
  printTree(tree);
  char *data = encodeData(tree, "bbaabtttaabtctce");
  printf("%s\n", data);
 
  return 0;
}
