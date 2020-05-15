#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

Status int_matcher(Element element1, Element element2)
{
  return *(int *)element1 == *(int *)element2 ? Success : Failure;
}

void display_int(Element element)
{
  printf("\n%d\n", *(int *)element);
}

void display_list(List_ptr list, Display_data displayer)
{
  Node_ptr p_walk = list->first;
  printf("List is:");
  while (p_walk != NULL)
  {
    displayer(p_walk->element);
    p_walk = p_walk->next;
  }
}

int main()
{
  List_ptr list = create_list();
  int number_1 = 1;
  int number_2 = 2;
  int number_3 = 3;
  add_to_list(list, &number_1);
  add_to_list(list, &number_2);
  add_to_list(list, &number_3);
  display_list(list, &display_int);
  remove_at(list, 2);
  display_list(list, &display_int);
  return 0;
}
