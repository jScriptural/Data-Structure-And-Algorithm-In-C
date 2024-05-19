#include "queue.h"
#include <stdlib.h>

#define putd(s,d) printf("%s: %d\n",s,d)
#define putul(s,d) printf("%s: %zu\n",s,d)


int main(void)
{

  Queue *q = queue_create();

  queue_enqueue(q,'h');
  queue_enqueue(q,'e');
  queue_enqueue(q,'l');
  queue_enqueue(q,'l');
  queue_enqueue(q,'o');
  queue_enqueue(q,-65);

  putul("size",queue_size(q));

  char buf[10];
  puts(queue_tostring(q,buf,10));

}
