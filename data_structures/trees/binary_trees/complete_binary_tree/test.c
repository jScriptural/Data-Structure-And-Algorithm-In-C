#include <stdio.h>
#include "cbt.h"


int main(void)
{
  CBT *cbt;
  cbt = cbt_create();

  printf("size: %zu\n",cbt_degree(cbt));
}


