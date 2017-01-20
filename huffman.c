# include "huffman.h"
# include "hash.h"

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
  if(!tree->left)
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
    return occ_rec;
  }
  occ[size] = '1';
  return encodeData_rec(tree->right, c, occ, size + 1, capacity);
}

char *encodeData(struct tree *tree, char *data)
{
  char *s = calloc(1 ,sizeof(char)), *occ = NULL;
  struct htab *htab = create_htab(8);
  struct pair_ *pair = NULL;
  size_t size = 1, len = 0;

  while(*data != '\0')
  {
    pair = access_htab(htab, *data);
    if(pair)
    {
      occ = calloc(pair->size, sizeof(char));
      occ = pair->data;
      len = pair->size;
    }
    else
    {
      occ = calloc(4, sizeof(char));
      occ = encodeData_rec(tree, *data, occ, 0, 4);
      len = strlen(occ);
      add_htab(htab, *data, occ, len);
    }
    size += len;
    s = realloc(s, size);
    s = strcat(s, encodeData_rec(tree, *data, occ, 0, 4));
    ++data;
  }
  clear_htab(htab);
  return s;
}

int toDecimal(char *data)
{
  int r = 0;
  while(*data != '\0')
  {
    r *= 2;
    if(*data == '1')
      ++r;
    ++data;
  }
  return r;
}

char *toBinaire(int x)
{
  char *data = calloc(9, sizeof(char));
  size_t i = 0;
  while(x > 0)
  {
    data[7 - i] = x % 2 + '0';
    x /= 2;
    ++i;
  }
  while(i < 8)
  {
    data[7 - i] = '0';
    ++i;
  }
  return data;
}

char *encodeTree_rec(struct tree *tree, char *data, size_t size)
{
  if(!tree)
    return "";

  if(tree->left)
  {
    char *cpy = calloc(size + 2, sizeof(char));
    cpy[0] = '0';
    cpy = strcat(cpy, data);
    ++size;
    data = strcat(cpy, encodeTree_rec(tree->left, data, size));
    while(data[size] != '\0')
    {
      ++size;
    }
    cpy = calloc(size + 1, sizeof(char));
    cpy = strcpy(cpy, data);
    data = strcat(cpy, encodeTree_rec(tree->right, data + size, size));
    return data;
  }
  else
  {
    data = strcat(data, "1");
    data = strcat(data, toBinaire(tree->key));
    return data;
  }
}

char *encodeTree(struct tree *tree)
{
  char *data = calloc(5000, sizeof(char));
  return encodeTree_rec(tree, data, 0);
}

int main()
{
  struct vector *vect = buildFrequency("bbaabtttaabtctce");
  struct tree *tree = huffmanTree(vect);
  printTree(tree);
  char *data = encodeData(tree, "bbaabtttaabtctce");
  printf("%s\n", data);
  char *dataTree = encodeTree(tree);
  printf("%s\n", dataTree);
  return 0;
}
