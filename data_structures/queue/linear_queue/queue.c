/* QUEUE.C
 *
 *
 * Author: Isonguyo, John Sunday <isongjohn014@gmail.com>
 * Created on 19/05/2024
 *
 *
 * Linked list implementations of queue data structure.
 */

#include "queue.h"
#include <stdlib.h>


struct __qnode {
  int _val;
  struct __qnode *_next;
};

struct __queue {
  struct __qnode *_head;
  struct __qnode *_tail;
  size_t _size;
};


Queue *queue_create(void)
{
  Queue *_q;
  if((_q = malloc(sizeof(Queue))) == NULL)
    return NULL;

  _q->_head = NULL;
  _q->_tail = NULL;
  _q->_size = 0;

  return _q;
}


void queue_clear(Queue *qu)
{
  if(qu->_size == 0)
    return;

  Qnode *curr = qu->_head,*prev = NULL;
  while(curr != NULL)
  {
    prev = curr;
    curr = curr->_next;
    free(prev);
  }

  qu->_size =0;
  qu->_head = NULL;
  qu->_tail = NULL;

}

void queue_destroy(Queue **qu)
{
  queue_clear(*qu);
  free(*qu);
  *qu = NULL;
}


int queue_enqueue(Queue *qu, int data)
{
  Qnode *qn;

  if((qn = malloc(sizeof(Qnode))) == NULL)
    return -1;

  qn->_val = data;
  qn->_next = NULL;

  if(qu->_size == 0)
  {
    qu->_head = qn;
    qu->_tail = qn;
  }
  else
  {
    qu->_tail->_next = qn;
    qu->_tail = qn;
  }

  ++qu->_size;
  return 0;
}

size_t queue_size(Queue *qu)
{
  return qu->_size;
}


int queue_dequeue(Queue *qu, int *data)
{
  Qnode *qn;
  if(qu->_size == 0)
    return -1;
  else if(qu->_size == 1)
  {
    qn = qu->_head;
    *data = qn->_val;
    qu->_head = NULL;
    qu->_tail = NULL;
  }
  else
  {
    qn = qu->_head;
    qu->_head = qn->_next;
    *data = qn->_val;
  }

  free(qn);
  --qu->_size;
  return 0;
}

int queue_peek(Queue *qu, int *data)
{
  if(qu->_size == 0)
    return -1;

  *data = qu->_head->_val;
  return 0;
}


int queue_isempty(Queue *qu)
{
  return !qu->_size;
}


char *queue_tostring(Queue *qu, char buf[], size_t nbytes)
{
  Qnode *qn;
  if(qu->_size == 0)
    return NULL;

  size_t i=0;
  qn=qu->_head;
  for(; i < (nbytes-1) && qn != NULL; ++i,qn = qn->_next)
  {
    buf[i] = (char) qn->_val;
  }

  buf[i] = '\0';
  return buf;
}
