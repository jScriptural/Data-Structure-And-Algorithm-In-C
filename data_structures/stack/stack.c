/*
 * STACK.C
 * 
 * Author: Isonguyo John Sunday <isongjohn014@gmail.com>
 * created on 15/05/2024
 *
 *
 * Modified by: Isonguyo John Sunday
 * Last Modified: 19/05/2024
 *
 */


#include "stack.h"
#include <stdlib.h>

struct __stacknode {
  SDATA _data;
  struct __stacknode *_next;
};

struct __stack {
  Stacknode *_top;
  size_t _size;
  int _type;
};



Stack *stack_create(int type)
{
  Stack *_sk;
  if((_sk = malloc(sizeof(Stack))) == NULL)
    return NULL;

  _sk->_top = NULL;
  _sk->_size = 0;
  _sk->_type = type;

  return _sk;
}


size_t stack_size(Stack *sk)
{
  return sk->_size;
}



int stack_isempty(Stack *sk)
{
  return !sk->_size; 
}


int stack_type(Stack *sk)
{
  return sk->_type;
}


int stack_push(Stack *sk, SDATA *data)
{
  Stacknode *sn;
  if((sn = malloc(sizeof(Stacknode))) == NULL)
    return -1;

  memmove(&sn->_data,data,sizeof(SDATA));
  
  if(sk->_size == 0)
  {
    sk->_top = sn;
    sn->_next = NULL;
  }
  else
  {
    Stacknode *tmp = sk->_top;
    sk->_top = sn;
    sn->_next = tmp;
  }
  ++sk->_size;

  return 0;
}


int stack_pop(Stack *sk,SDATA *data)
{
  Stacknode *target;
  if(sk->_size == 0)
    return -1;

  target = sk->_top;
  sk->_top = target->_next;

  memmove(data,&target->_data,sizeof(SDATA));
  --sk->_size;

  free(target);
  return 0;
}


void stack_clear(Stack *sk)
{
  Stacknode  *curr,*prev;
  if(sk->_size == 0)
    return;

  curr = sk->_top;
  prev = NULL;

  while(curr != NULL)
  {
    prev = curr;
    curr = curr->_next;
    free(prev);
  }

  sk->_top = NULL;
  sk->_size = 0;

}

void stack_destroy(Stack **sk)
{
  stack_clear(*sk);
  free(*sk);

  *sk = NULL;
}


int stack_peek(Stack *sk,SDATA *data)
{
  if(sk->_size == 0)
    return -1;

  memmove(data,&sk->_top->_data,sizeof(SDATA));
  return sk->_type;
}

