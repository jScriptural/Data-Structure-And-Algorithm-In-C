/* STRUCT_JA_NODE.H
 *
 * Author: Isonguyo John Sunday <isongjohn014@gmail.com>
 * Created on 14/05/2024
 *
 * Macros, structures and type definitions
 */

#pragma once

#include <stdint.h>


typedef union {
  int ival;
  char *pval;
} Jarrayv;

/*Client code should used this to obtain the value
 * stored in the array.
 * Modifying this object does not modify the 
 * corresponding node in the Jarray.
 */
typedef struct {
  Jarrayv val;
  int16_t type;
} JAVALUE;

/* Internal use only.
 * Do not assume its members
 * The opaque structure used to implement the node 
 * of the list representing the jarray element.
 */
struct __sJa_node {
  int16_t _type; // the data type contain in `_val`
  uint32_t _index; // index of the node
   Jarrayv _val; // the value to store. 
  struct __sJa_node *_prev; // pointer to the previous node
  struct __sJa_node *_next; // pointer to the previous node
};
typedef struct *__sJa_node Ja_node;


/*Internal use only*/
struct __Jarray {
  Ja_node  *_head;
  Ja_node *_tail;
  uint32_t _len; //total nodes in `head`;  
};


