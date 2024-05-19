/* QUEUE.H
 *
 * Author: Isonguyo, John Sunday <isongjohn014@gmail.com>
 * Created on 19/05/2024
 *
 *
 * Header for linear queue implementation that stores int
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>


struct __qnode;
typedef struct __qnode Qnode;

struct __queue;
typedef struct __queue Queue;


/*[queue_create]-
 *
 *
 */
Queue *queue_create(void);


/*[queue_dequeue]-
 *
 *
 */
int queue_dequeue(Queue *qu,int *data);


/*[queue_enqueue]-
 *
 */
int queue_enqueue(Queue *qu,int data);


/*[queue_peek]-
 *
 *
 */
int queue_peek(Queue *qu, int *data);


/*[queue_clear]-
 *
 *
 */
void queue_clear(Queue *qu);


/*[queue_destroy]-
 *
 *
 */
void queue_destroy(Queue **qu);


/*[queue_size]-
 *
 *
 */
size_t queue_size(Queue *qu);


/*[queue_isempty]-
 *
 *
 */
int queue_isempty(Queue *qu);


/*[queue_tostring]-
 *
 *
 */
char *queue_tostring(Queue *qu, char buf[],size_t nbytes);

#endif


