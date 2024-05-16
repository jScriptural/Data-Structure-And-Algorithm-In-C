/*JARRAY.C
 *
 * Author: Isonguyo John <isongjohn014@gmail.com>
 * Created on 14/05/2024.
 *
 *
 * Modified by: Isonguyo John Sunday
 * Last modified: 16/05/2024
 *
 *
 * Implementing JavaScript's array-like structure in C
 *
 */


#include <stdarg.h>
#include "jarray.h"
#include <errno.h>


struct __sJa_node {
  JAVALUE _val;
  struct __sJa_node *_prev;
  struct __sJa_node *_next;
};

struct __Jarray {
  Ja_node *_head;//point to first node element
  Ja_node *_tail;//point to last node element
  uint32_t _len; //total nodes in `head`
};

static int set_appropriate_value_and_type(Ja_node *jn,JAVALUE *value)
{
  if(value->type == INT || value->type == CHAR || value->type == STRING)
  {
    memmove(&jn->_val,value,sizeof(JAVALUE));
    return 0;
  }

  return -1;
}


Jarray *jarray_create(void)
{
  Jarray *_h;
  if((_h = malloc(sizeof(Jarray))) == NULL)
    return NULL;

  _h->_head = NULL;
  _h->_tail = NULL;
  _h->_len = 0;

  return _h;
}


void jarray_destroy(Jarray *ja)
{
  Ja_node *curr,*prev;
  for(prev = ja->_head,curr = prev->_next; prev != NULL; prev = curr,curr = curr->_next)
  {
    if(prev !=  NULL)
    {
      free(prev);
      if(curr == NULL)
	break;
    }
  }

  free(ja);
  ja = NULL;
}


uint32_t jarray_len(const Jarray *ja)
{
  return ja->_len;
}


Jarray *jarray_set(Jarray *ja,JAVALUE *value)
{
  Ja_node *jn;

  /* If the index exist then change the value and the
   * corresponding type field.
   */
  if(value->index < ja->_len && value->index >= 0)
  {
    jn = jarray_get(ja,NULL,value->index);
    if(set_appropriate_value_and_type(jn,value) < 0)
    {
      errno = EINVAL;
      return NULL;
    }
  }
  /* Otherwise create a new `Ja_node` and attach it 
   * to the end of the list 
   */
  else
  {
    if((jn = malloc(sizeof(Ja_node))) == NULL)
      return NULL;

    if(set_appropriate_value_and_type(jn,value) < 0)
    {
      free(jn);
      errno = EINVAL;
      return NULL;
    }

    jn->_next = NULL;
    if(ja->_len == 0)
    {
      jn->_prev = NULL;
      ja->_head = jn;
      ja->_tail = jn;
    }
    else 
    {
      Ja_node *tmp;
      tmp = ja->_tail;
      tmp->_next = jn;
      jn->_prev = tmp;
      ja->_tail = jn;
    }
    jn->_val.index = ja->_len++;
  }

  return ja;
}


Ja_node *jarray_get(Jarray *ja,JAVALUE *value,uint32_t index)
{
  if(ja->_len == 0)
    return NULL;

  Ja_node *p;
  for(p = ja->_head; p != NULL; p=p->_next)
  {
    if(p->_val.index == index)
    {
      if(value != NULL)
	memmove(value,&p->_val,sizeof(JAVALUE));
      return p;
    }
  }

  if(value != NULL)
    value = NULL;
  return NULL;
}


int jarray_remove(Jarray *ja,JAVALUE *value,uint32_t index)
{
  //printf("r1\n");
  Ja_node *target,*next;
  if(index >= ja->_len)
  {
    if(value != NULL)
      value = NULL;
    return -1;
  }

 // printf("r2\n");
  if((target = jarray_get(ja,NULL,index)) == NULL)
  {
    if(value != NULL)
      value = NULL;
    return -1;
  }

  if(index  == 0)
  {
    ja->_head = target->_next;
    ja->_head->_prev = NULL;
  }
  else if(index > 0 && index < (ja->_len - 1))
  {
    target->_next->_prev = target->_prev;
    target->_prev->_next = target->_next;
  }
  else
  {
    ja->_tail = target->_prev;
    ja->_tail->_next = NULL;
  }

  for(next = target->_next; next != NULL; next = next->_next)
    next->_val.index = index++;

  if(value != NULL)
    memmove(value,&target->_val,sizeof(JAVALUE));

  --ja->_len;
  free(target);
  return 0;
}


int jarray_pop(Jarray *ja, JAVALUE *value)
{
  Ja_node *target;
  if(ja->_len == 0)
  {
    if(value != NULL)
      value = NULL;
    return -1;
  }

  if(ja->_len == 1)
  {
    target = ja->_tail;
    ja->_tail = NULL;
    ja->_head = NULL;
  }
  else
  {
    target  = ja->_tail;
    ja->_tail = target->_prev;
    ja->_tail->_next = NULL;
  }

  if(value != NULL)
    memmove(value,&target->_val,sizeof(JAVALUE));

  --ja->_len;
  free(target);
  return 0;
  
}


int jarray_push(Jarray *ja, JAVALUE *value)
{
  Ja_node *jn;

  if((jn = malloc(sizeof(Ja_node))) == NULL)
    return -1;

  if(set_appropriate_value_and_type(jn,value) < 0)
  {
    free(jn);
    return -1;
  }

  jn->_next = NULL;

  if(ja->_len == 0)
  {
    jn->_prev = NULL;
    ja->_head = jn;
    ja->_tail = jn;
  }
  else
  {
    Ja_node *tmp;
    tmp = ja->_tail;
    jn->_prev = tmp;
    tmp->_next = jn;
    ja->_tail = jn;
  }

  ja->_tail->_val.index = ja->_len++;
  value->index = ja->_tail->_val.index; 
  return 0;
}


int jarray_shift(Jarray *ja, JAVALUE *value)
{
  Ja_node *target,*next;
  uint32_t index = 0;

  if(ja->_len ==  0)
  {
    if(value != NULL)
      value = NULL;
    return -1;
  }

  target = ja->_head;
  if(ja->_len == 1)
  {
    ja->_head = NULL;
    ja->_tail = NULL;
  }
  else
  {
    ja->_head = target->_next;
    ja->_head->_prev = NULL;
  }

  for(next = ja->_head; next != NULL; next=next->_next)
    next->_val.index = index++;

  --ja->_len;
  if(value != NULL)
    memmove(value,&target->_val,sizeof(JAVALUE));
  return 0;
}


int jarray_unshift(Jarray *ja, JAVALUE *value)
{
  Ja_node *jn,*next;
  uint32_t index = 0;

  if((jn = malloc(sizeof(Ja_node))) == NULL)
    return -1;

  jn->_prev = NULL;
  memmove(&jn->_val, value,sizeof(JAVALUE));

  if(ja->_len == 0)
  {
    jn->_next = NULL;
    ja->_head = jn;
    ja->_tail = jn;
  }
  else
  {
    Ja_node *tmp;
    tmp = ja->_head;
    jn->_next = tmp;
    tmp->_prev = jn;
    ja->_head = jn;
  }

  for(next = ja->_head; next != NULL; next=next->_next)
    next->_val.index = index++;

  ++ja->_len;
  return 0;  
}


Jarray *jarray_concat(Jarray *dst, int count, ...)
{
  va_list ap;
  va_start(ap, count);

  for(int i =0; i < count; ++i)
  {
    Ja_node *ja = va_arg(ap, Jarray *)->_head;
    while(ja != NULL)
    {
      jarray_push(dst,&ja->_val);
      ja = ja->_next;
    }
  }

  return dst;
}


Jarray *jarray_reverse(Jarray *ja)
{
  Ja_node *p = ja->_head, *q = ja->_tail;

  if(ja->_len < 2)
    return ja;

  while(p->_val.index < q->_val.index)
  {
    JAVALUE tmp = p->_val;
    uint32_t index = q->_val.index;
    p->_val = q->_val;
    p->_val.index = tmp.index;
    q->_val = tmp;
    q->_val.index = index;
    q = q->_prev;
    p = p->_next;
  }

  return ja;
}


char *jarray_tostring(Jarray *ja,char str[],size_t *nbytes)
{
  size_t maxsz = 1024*1024;
  char *buf;
  Ja_node *jn;

  if(ja->_len == 0)
  {
    *nbytes = 0;
    return NULL;
  }

  if((buf = calloc(maxsz,sizeof(char))) == NULL)
  {
    *nbytes = 0;
    return NULL;
  }

  for(jn = ja->_head; jn != NULL && strlen(buf) < maxsz; jn = jn->_next)
  {
    if(jn->_val.type == STRING)
      strncat(buf+strlen(buf),jn->_val.jv.pval,maxsz-strlen(buf));
    else if(jn->_val.type == INT)
      snprintf(buf+strlen(buf),maxsz - strlen(buf),"%d",jn->_val.jv.ival);
    else if(jn->_val.type == CHAR)
      snprintf(buf+strlen(buf),maxsz-strlen(buf),"%c",jn->_val.jv.ival);

  }

  strncpy(str,buf,*nbytes);
  *nbytes = strlen(buf);

  free(buf);
  return str;  
}


Jarray *jarray_slice(Jarray *ja, int start, int end)
{
  Ja_node *jn;
  int toend = start <= end ? 0 : 1;
  Jarray *newja = jarray_create();

  if(ja->_len == 0 || ja->_len < (start+1))
    return newja;

  if(start < 0 || end < 0)
    return newja;

  jn = jarray_get(ja,NULL,start);

  if(toend)
  {
    for(; jn != NULL; jn = jn->_next)
      jarray_push(newja,&jn->_val);
  }
  else 
  {
    for(; jn != NULL && jn->_val.index < end; jn = jn->_next)
      jarray_push(newja,&jn->_val);
  }

  return newja;
}
