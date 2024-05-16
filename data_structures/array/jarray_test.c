#include "jarray.h"

void printvalue(Jarray *ja);

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

  printvalue(ja);

  Jarray *arr = jarray_slice(ja,1,0);

  char buf[100] = {0};
  size_t n = 100;
  
  jarray_tostring(ja,buf,&n);

  printf("ja: %zu: %s\n",n,buf);
  memset(buf,0,n);
  jarray_tostring(arr,buf,&n);
  printf("j: %zu: %s\n",n,buf);

  jarray_destroy(arr);


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
