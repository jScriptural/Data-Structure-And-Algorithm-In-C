/*JARRAY.C
 *
 * Author: Isonguyo John <isongjohn014@gmail.com>
 * Created on 14/05/2024.
 *
 *
 * Implementing JavaScript's array-like structure in C
 *
 */



#include "jarray.h"
#include <errno.h>


struct __sJa_node {
  int16_t _type;
  uint32_t _index;
  Jarrayv _val;
  struct __sJa_node *_prev;
  struct __sJa_node *_next;
};

struct __Jarray {
  Ja_node *_head;
  Ja_node *_tail;
  uint32_t _len; //total nodes in `head`;
};

static int set_appropriate_value_and_type(Ja_node *jn,void *value,int16_t type)
{
  switch(type)
  {
    case INT:
      ;
    case CHAR:
      jn->_val.ival = *(int *)value;
      break;
    case STRING:
      jn->_val.pval = (char *)value;
      break;
    default:
      return -1;
  }
  jn->_type = type;
  return 0;
}
Jarray *jarray_create(void)
{
  Jarray *_h;
  if((_h = malloc(sizeof(Jarray))) == NULL)
  {
    return NULL;
  }
  _h->_head = NULL;
  _h->_tail = NULL;
  _h->_len = 0;

  return _h;
}


uint32_t jarray_len(const Jarray *ja)
{
  return ja->_len;
}


Jarray *jarray_set(Jarray *ja,void *value, int16_t type,uint32_t index)
{
  Ja_node *jn;

  /* If the index exist then change the value and the
   * corresponding type field.
   */
  if(index < ja->_len && index >= 0)
  {
    jn = jarray_get(ja,NULL,index);
    if(set_appropriate_value_and_type(jn,value,type) < 0)
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

    if(set_appropriate_value_and_type(jn,value,type) < 0)
    {
      free(jn);
      errno = EINVAL;
      return NULL;
    }

    if(ja->_len == 0)
    {
      jn->_next = NULL;
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
      jn->_next = NULL;
      ja->_tail = jn;
    }
    jn->_index = ja->_len++;
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
    if(p->_index == index)
    {
      if(value != NULL)
      {
	memmove(&value->javal,&p->_val,sizeof(Jarrayv));
	value->type = p->_type;
      }
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
  }

    return -1;
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
    next->_index = index++;

  if(value != NULL)
  {
    memmove(&value->javal,&target->_val,sizeof(Jarrayv));
    value->type = target->_type;
  }


  --ja->_len;
  free(target);
  return 0;
}


int jarray_pop(Jarray *ja, JAVALUE *value)
{
  Ja_node *target;
  if(ja->_len == 0)
  {
    if(value)
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
  {
    memmove(&value->javal,&target->_val,sizeof(Jarrayv));
    value->type = target->_type;
  }

  --ja->_len;
  free(target);
  return 0;
  
}
