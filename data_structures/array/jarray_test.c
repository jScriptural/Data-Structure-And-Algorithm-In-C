#include "jarray.h"


int main(void)
{
  Jarray *ja;
  ja = jarray_create();

  JAVALUE jav;
  jav.jv.pval = "hello, world!";
  jav.type = STRING;
  jav.index = 0;
  jarray_set(ja,&jav);
  jav.jv.pval = "Nigeria";
  jav.index = 1;
  jarray_set(ja,&jav);
  jav.jv.ival = 23;
  jav.index = 2;
  jav.type = INT;
  jarray_set(ja,&jav);
  jav.jv.ival = 'A';
  jav.type = CHAR;
  jav.index = 3;
  jarray_set(ja,&jav);
  jav.jv.pval = "To C or not to C";
  jav.index = 4;
  jav.type = STRING;
  jarray_set(ja,&jav);

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

  if(jarray_pop(ja,NULL) < 0)
  {
    perror("jarray_remove");
    exit(EXIT_FAILURE);
  }

  memset(&jav, 0,sizeof(JAVALUE));
  jav.jv.pval = "What is popping";
  jav.type = STRING;
  jav.index = 0;
  jarray_set(ja,&jav);
  printf("length: %u\n",jarray_len(ja));


  memset(&jav, 0,sizeof(JAVALUE));
  jav.jv.ival = 404;
  jav.type = INT;
  if(jarray_push(ja,&jav) < 0)
    perror("jarray_push");

  jarray_unshift(ja,&jav);
  jav.jv.ival = 500;
  jarray_unshift(ja,&jav);
  jarray_shift(ja,NULL);
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

