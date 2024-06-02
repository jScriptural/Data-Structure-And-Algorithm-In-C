/* CBT.C
 * 
 * Author: Isonguyo, John Sunday <isongjohn014@gmail.com>
 * Created on 30/05/2024
 *
 * Implementing the API for complete binary tree.
 *
 * A complete binary tree is a type of binary tree that
 * satisfies two conditions:
 * 1. Every level must be completely filled before filling
 * the next level.
 * 2. All nodes must appear as far left as possible.
 */

#include <stdlib.h>
#include <stddef.h>
#include "cbt.h"

struct __cbt_node {
  int _data;
  struct __cbt_node *_right;
  struct __cbt_node *_left;
};

struct __CBT {
  struct __cbt_node *_root;
  size_t _sz; /*the number of nodes in the tree*/
};

/* HELPER FUNCTIONS */
static inline cbt_node *_create_node(int data)
{
  cbt_node *node;
  if((node = malloc(sizeof(cbt_node))) == NULL)
    return NULL;

  node->_left = NULL;
  node->_right = NULL;
  node->_data = data;

  return node;
}

static cbt_node *_grow_helper(cbt_node *node, int data)
{

}


/* PUBLIC INTERFACE IMPLEMENTATION */

CBT *cbt_create(void)
{
  CBT *_c;
  if((_c = malloc(sizeof(CBT))) == NULL)
    return NULL;

  _c->_root = NULL;
  _c->_sz = 0;

  return _c;
}

size_t cbt_degree(CBT *cbt)
{
  return cbt->_sz;
}


CBT *cbt_grow(CBT *cbt, int data)
{

}
