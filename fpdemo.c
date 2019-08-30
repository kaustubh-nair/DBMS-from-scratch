#include<stdio.h>
#include<stdlib.h>
#include"contact.h"

void somedemo( void (*f)(struct Contact *c), struct Contact *contact)
{
  f(contact);
}
void print1(struct Contact *c)
{
  printf("%d\n", c->contact_id);
}
void print2(struct Contact*c)
{
  printf("%s\n",c->contact_name);
}
void main()
{
  struct Contact demo;
  demo.contact_id = 100;
  strcpy(demo.contact_name, "some demo");
  somedemo(print1, &demo);
  somedemo(print2, &demo);
}


