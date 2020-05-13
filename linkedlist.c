#include"linkedlist.h"

Node_ptr create_node(void)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = malloc(sizeof(Element));
  new_node->next = NULL;
  return new_node;
}

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr new_node = create_node();
  if(new_node == NULL) return Failure;
  new_node->element = element;

  if (list->first == NULL)
  {
    list->first = new_node;
  } 
  else 
  {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node();
  if(new_node == NULL) return Failure;
  new_node->element = element;

  if(list->first == NULL)
  {
    list->last = new_node;
  }
  new_node->next = list->first;
  list->first = new_node;
  list->length++;
  return Success;
}

Element remove_from_start(List_ptr list)
{
  if (list->length == 0) return NULL;
  if (list->length == 1) 
  {
    Element element = list->first;
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return element;
  }
  Node *first_node = list->first;
  list->first = first_node->next;
  list->length--;
  return first_node->element;
}

List_ptr reverse(List_ptr list)
{
  List_ptr reverse_list = create_list();
  if(list->length == 0) return reverse_list;
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_start(reverse_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return reverse_list;
}

Status clear_list(List_ptr list)
{
  if (list->length == 0) return Failure;
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    Node_ptr next = p_walk->next;
    free(p_walk);
    p_walk = next;
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return Success;
}
