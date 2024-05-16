#include "jarray.h"
#include <ctype.h>

void printvalue(Jarray *ja);

JAVALUE jval;
JAVALUE *mapfn(JAVALUE val)
{
  jval.type = val.type;
  if(val.type == INT)
  {
    jval.jv.ival = 3 * val.jv.ival;
    
    return &jval;
  }
  return &jval;
}

int main(void)
{
  Jarray *ja;
  ja = jarray_create();

  JAVALUE jav;
  jav.jv.ival = 'h';
  jav.type = CHAR;
  jav.index = 0;
  jarray_set(ja,&jav);
  jav.jv.ival = 'e';
  jav.index = 1;
  jarray_set(ja,&jav);
  jav.jv.ival = 'l';
  jav.index = 2;
  jarray_set(ja,&jav);
  jav.jv.ival = 'l';
  jav.index = 3;
  jarray_set(ja,&jav);
  jav.jv.ival = 'o';
  jav.index = 4;
  jarray_set(ja,&jav);

 // printvalue(ja);

  Jarray *j = jarray_create();
  char b[] = "Kingdom";
  memset(&jav,0,sizeof(JAVALUE));
  jav.type = CHAR;
  for(int i =0; i < strlen(b); ++i)
  {
    jav.jv.ival = b[i];
    jarray_push(j,&jav);
  }
  
  memset(&jav,0,sizeof(JAVALUE));
  jav.jv.ival = 'g';
  jav.type = CHAR;
  if(jarray_indexof(j,&jav) == 0)
  {
    printf("val: %c\n",jav.jv.ival);
    printf("index: %u\n",jav.index);
  }
  else
  {
    printf("val: %c not found\n",jav.jv.ival);
  }
  printf("\n*********************************\n\n");

  Jarray *n = jarray_create();
  jav.type = INT;
  for(int i =0; i < 10; ++i)
  {
    jav.jv.ival = i;
    jarray_push(n,&jav);
  }

  Jarray *m = jarray_map(n,mapfn);

  printvalue(n);
  printvalue(m);

  printf("\n*********************************\n\n");
  printvalue(jarray_reverse(n));

  jarray_destroy(m);
  jarray_destroy(ja);
  jarray_destroy(j);
}




void printvalue(Jarray *ja)
{
  printf("length: %u\n",jarray_len(ja));
  for(uint32_t i = 0; i < jarray_len(ja); ++i)
  {
    JAVALUE jv;
    if(jarray_get(ja,&jv,i) == NULL)
      break;
    switch(jv.type)
    {
      case INT:
	printf("ival[%u] = %d\n",i,jv.jv.ival);
	break;
      case CHAR:
	printf("cval[%u] = %c\n",i,jv.jv.ival);
	break;
      case STRING:
	printf("pval[%u] = %s\n",i,jv.jv.pval);
	break;
      default:
	break;
    }
  }
}
