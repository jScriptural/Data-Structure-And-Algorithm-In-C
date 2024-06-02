/* CBT.H
 * 
 * Author: Isonguyo, John Sunday <isongjohn014@gmail.com>
 * Created on 30/05/2024
 *
 * Header for cbt.c 
 *
 *
 * A complete binary tree is a type of binary tree that 
 * satisfies two conditions:
 * 1. Every level must be completely filled before filling
 * the next level.
 * 2. All nodes must appear as far left as possible.
 */

#ifndef CBT_H
#define CBT_H

#include <stddef.h>


/* Hidden structures.
 * Client code should use the provided API.
 * Members of these structures should not be assumed by 
 * client.
 */

struct __cbt_node;
typedef struct __cbt_node cbt_node;

struct __CBT;
typedef struct __CBT CBT;

/* PUBLIC INTERFACE*/
/*[cbt_create]-
 *
 */
CBT *cbt_create(void);


/*[cbt_destroy]-
 *
 */
void cbt_destroy(CBT *cbt);


/*[cbt_grow]-
 *
 */
CBT *cbt_grow(CBT *cbt, int data);

/*[cbt_degree]-
 *
 */
size_t cbt_degree(CBT *cbt);

#endif
