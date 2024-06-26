/*JARRAY.C
 *
 * Author: Isonguyo John Sunday <isongjohn014@gmail.com>
 * Created on 14/05/2024
 *
 *
 * Modified by: Isonguyo John Sunday
 * Last modified: 18/05/2024
 *
 *
 * Header for jarray.c
 *
 */

#ifndef JARRAY_H
#define JARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


typedef union {
  int ival;
  char *pval;
} Jarrayv;

typedef struct {
  Jarrayv jv;
  int16_t type;
  uint32_t index;
} JAVALUE;

struct __sJa_node;
typedef struct __sJa_node Ja_node;

struct __Jarray;
typedef struct __Jarray Jarray;

/* POSSIBLE VALUES FOR TYPE */
#define JA_INT 0
#define JA_CHAR 1 
#define JA_STRING 2



/*[jarray_create]-
 *
 *
 */
Jarray *jarray_create(void);


/*[jarray_destroy]-
 *
 *
 */
void jarray_destroy(Jarray **ja);


/*[jarray_get]- retrieves the node at the specified 
 * `index` from the Jarray.
 * If the node is found and `value` is non-null,
 * it copies its value to the `value`.
 * Returns a pointer to a `Ja_node` structure on 
 * success, and returns NULL on failure.
 */
Ja_node *jarray_get(Jarray *ja,JAVALUE *value, uint32_t index);



/*[jarray_set]-
 *
 *
 *
 *
 */
Jarray *jarray_set(Jarray *ja, JAVALUE *value);


/*[jarray_len]-
 *
 *
 *
 */
uint32_t  jarray_len(const Jarray *ja);


/*[jarray_remove]-
 *
 *
 */
int jarray_remove(Jarray *ja,JAVALUE *value,uint32_t index);


/*[jarray_pop]-
 *
 *
 */
int jarray_pop(Jarray *ja, JAVALUE *value);


/*[jarray_push]-
 *
 * 
 */
int jarray_push(Jarray *ja, JAVALUE *value);


/*[jarray_shift]-
 *
 *
 */
int jarray_shift(Jarray *ja, JAVALUE *value);



/*[jarray_unshift]-
 *
 *
 */
int jarray_unshift(Jarray *ja, JAVALUE *value);

/*[jarray_concat]-
 *
 *
 */
Jarray *jarray_concat(Jarray *dst,int count, ...);


/*[jarray_reverse]-
 *
 *
 */
Jarray *jarray_reverse(Jarray *ja);

/*[jarray_tostring]-
 *
 *
 *
 */
char *jarray_tostring(Jarray *ja, char str[],size_t *nbytes);


/*[jarray_slice]-
 *
 *
 */
Jarray *jarray_slice(Jarray *ja, int start, int end);


/*[jarray_find]-
 *
 *
 */
int jarray_indexof(Jarray *ja, JAVALUE *value);


/*[jarray_map]-
 *
 *
 */
Jarray *jarray_map(Jarray *ja, JAVALUE *(*mapfn)(JAVALUE value));
#endif
