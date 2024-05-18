/*
 * STACK.H
 *
 * Author: Isonguyo John Sunday <isongjohn014@gmail.com>
 * Created on 15/05/2024
 *
 * Modified by: Isonguyo John Sunday
 * Last modified: 18/05/2024
 *
 * Header for stack.c
 */


#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#define SK_INT 0
#define SK_CHAR 1
#define SK_STRING 2

typedef union __stack_data {
 int ival;
 char *pval;
} SDATA; 

struct __stack;
typedef struct __stack Stack;

struct __stacknode;
typedef struct __stacknode Stacknode;

/*[stack_create]-
 *
 *
 */
Stack *stack_create(int type);

/*[stack_destroy]-
 *
 *
 */
void stack_destroy(Stack **sk);

/*[stack_size]-
 *
 *
 */
size_t stack_size(Stack *sk);

/*[stack_isempty]-
 *
 *
 */
int stack_isempty(Stack *sk);

/*[stack_type]-
 *
 *
 */
int stack_type(Stack *sk);

/*[stack_push]-
 *
 *
 */
int stack_push(Stack *sk,SDATA *data);

/*[stack_pop]-
 *
 *
 */
int stack_pop(Stack *sk,SDATA *data);

/*[stack_peek]-
 *
 *
 */
int stack_peek(Stack *sk, SDATA *data);

/*[stack_clear]
 *
 *
 */
void stack_clear(Stack *sk);
#endif
