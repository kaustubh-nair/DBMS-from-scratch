#include <stdio.h>
#include <string.h>

void temp(void *x)
{
  int *b = (int *)x;
  *b = 30;
}
void main()
{
  char a[] = "qwe";
  char b[] = "asd";
  strcpy(a, b);
  printf("%s",a);
  
}
