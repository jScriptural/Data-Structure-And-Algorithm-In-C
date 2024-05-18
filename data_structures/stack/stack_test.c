#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  Stack *sk = stack_create(SK_INT);
  SDATA sd;

  for(int i = 100; i < 1000; i += 100)
  {
    sd.ival = i;
    stack_push(sk,&sd);
  }


  memset(&sd,0,sizeof(sd));
  stack_pop(sk,&sd);
  stack_peek(sk,&sd);

  //stack_destroy(&sk);

  //sk = NULL;
  if(sk)
    puts("valid");
  else
    puts("invalid");

  stack_push(sk,&sd);
  printf("size: %zu\n",stack_size(sk));
  printf("type: %d\n",stack_type(sk));

  if(stack_isempty(sk))
    printf("empty\n");
  else
    printf("not empty\n");

  printf("data: %d\n",sd.ival);
}


