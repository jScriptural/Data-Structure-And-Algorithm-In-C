#include "jarray.h"


int main(void)
{
  Jarray *ja;
  ja = jarray_create();


  int v1 = 23;
  char c = 'A';
  char *p = "Nigeria";

  jarray_set(ja,"hello, world!",STRING,0);
  jarray_set(ja,p,STRING,1);
  jarray_set(ja,&v1,INT,2);
  jarray_set(ja,&c,CHAR,3);
  jarray_set(ja,"To C or not to C",STRING,4);

  printf("length: %u\n",jarray_len(ja));

  for(uint32_t i = 0; i < jarray_len(ja); ++i)
  {
    JAVALUE jv;
    if(jarray_get(ja,&jv,i) == NULL)
      break;
    switch(jv.type)
    {
      case INT:
	printf("ival[%u] = %d\n",i,jv.javal.ival);
	break;
      case CHAR:
	printf("cval[%u] = %c\n",i,jv.javal.ival);
	break;
      case STRING:
	printf("pval[%u] = %s\n",i,jv.javal.pval);
	break;
      default:
	break;
    }
  }

  if(jarray_pop(ja,NULL) < 0)
  {
    perror("jarray_remove");
    exit(EXIT_FAILURE);
  }

  jarray_set(ja,"What's popping?",STRING,0);
  printf("length: %u\n",jarray_len(ja));

  for(uint32_t i = 0; i < jarray_len(ja); ++i)
  {
    JAVALUE jv;
    if(jarray_get(ja,&jv,i) == NULL)
      break;
    switch(jv.type)
    {
      case INT:
	printf("ival[%u] = %d\n",i,jv.javal.ival);
	break;
      case CHAR:
	printf("cval[%u] = %c\n",i,jv.javal.ival);
	break;
      case STRING:
	printf("pval[%u] = %s\n",i,jv.javal.pval);
	break;
      default:
	break;
    }
  }
}

