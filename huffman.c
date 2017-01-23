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
    strcat(s, occ);
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

char *encodeTree_rec(struct tree *tree)
{
  if(!tree)
    return "";
  char *s = NULL;
  char *data = NULL;
  if(tree->left)
  {
    s = calloc(2, sizeof(char));
    s[0] = '0';
    data = encodeTree_rec(tree->left);
    size_t size = strlen(data) + 2;
    s = realloc(s, size);
    strcat(s, data);
    s[size - 1] = '\0';
    free(data);
    data = encodeTree_rec(tree->right);
    size += strlen(data); 
    s = realloc(s, size);
    strcat(s, data);
    free(data);
    s[size - 1] = '\0';
    return s;
  }
  else
  {
    s = calloc(10, sizeof(char));
    s[0] = '1';
    data = toBinaire(tree->key);
    strcat(s, data);
    free(data);
    return s;
  }
}
char *encodeTree(struct tree *tree)
{
  return encodeTree_rec(tree);
}

struct Tup *toBinary(char *data)
{
  int decimal;
  size_t i = 0, len = strlen(data), capacity = len / 8 + 2;
  char *s = NULL, *res = calloc(capacity, sizeof(char)), *str = NULL;
  while(i + 8 < len)
  {
    s = calloc(9, sizeof(char));
    str = calloc(2, sizeof(char));
    for(size_t j = 0; j < 8; ++j)
    {
      s[j] = data[i];
      ++i;
    }
    decimal = toDecimal(s);
    str[0] = decimal;
    strcat(res, str);
    free(str);
    free(s);
   }

   size_t cpt = 0;
   s = calloc(9, sizeof(char));
   str = calloc(2, sizeof(char));
   while(i < len)
   {
     s[cpt] = data[i];
     ++cpt;
     ++i;
   }
   for(size_t j = cpt; j < 8; ++j)
     s[j] = '0';

   decimal = toDecimal(s);
   str[0] = decimal;
   strcat(res, str);
   free(str);
   free(s);
   struct Tup *tup = malloc(sizeof(struct Tup));
   tup->t1 = res;
   tup->t2 = cpt;
   return tup;
}

/*============================Decompression====================================*/

char *decode(char *data, size_t alignement)
{
  char *s = calloc(1, sizeof(char)), *add = NULL;
  size_t i = 0, size = 1;
  while(data[i + 1] != '\0')
  {
    size += 8;
    s = realloc(s, size);
    add = toBinaire(data[i]);
    strcat(s, add);
    s[size - 1] = '\0';
    free(add);
    ++i;
  }
  size += 8;
  s = realloc(s, size);
  add = toBinaire(data[i]);
  strcat(s, add + alignement);
  s[size - 1] = '\0';
  free(add);
  return s;
}

struct tup *decodeTree_rec(char *data, size_t size)
{
  if(*data != '\0')
  {
    struct tree *tree = NULL;
    struct tup *tup = NULL;

    if(data[size] == '0')
    {
      tree = newTree();
      ++size;
      tup = decodeTree_rec(data, size);
      tree->left = tup->t1;
      size = tup->t2;
      free(tup);
      tup = decodeTree_rec(data, size);
      tree->right = tup->t1;
      size = tup->t2;
      free(tup);
    }
    else
    {
      ++size;
      char *str = calloc(9, sizeof(char));
      for(size_t i = 0; i < 8; ++i)
      {
        str[i] = data[size];
        ++size;
      }
      tree = newTree();
      tree->key = toDecimal(str);
      free(str);
    }
    tup = malloc(sizeof(struct tup));
    tup->t1 = tree;
    tup->t2 = size;
    return tup;
  }
  return NULL;
}

struct tree *decodeTree(char *data, size_t alignement)
{
  char *str = decode(data, alignement);
//  struct tup *tup = decodeTree_rec(str, 0);
  struct tup *tup = decodeTree_rec("0010111010010110001001011000010101100011101100101", 0);
  struct tree *tree = tup->t1;
  free(str), free(tup);
  return tree;
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
  struct Tup *tup = toBinary(data);
  char *binary = tup->t1;
  size_t align1 = tup->t2;
  struct Tup *tup2 = toBinary(dataTree);
  char *binaryTree = tup2->t1;
  size_t align2 = tup2->t2;
  printf("%s\n", binary);
  printf("%s\n", binaryTree);

  char *decodeData = decode(binary, align1);
  printf("%s\n", decodeData);
  struct tree *huff = decodeTree(binaryTree, align2);
  printTree(huff);
  free(data), free(dataTree), free(binary), freeTree(tree);
  free(vect->data), free(vect), free(binaryTree), freeTree(huff);
  free(tup), free(tup2), free(decodeData);
  return 0;
}
