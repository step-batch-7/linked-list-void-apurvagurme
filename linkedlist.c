#include"linkedlist.h"

Node_ptr create_node(Element element)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = element;
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
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) return Failure;

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
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) return Failure;

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
    Element element = list->first->element;
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

Element remove_from_end(List_ptr list)
{
  if(list->length == 0) return NULL;
  if (list->length == 1) 
  {
    Element element = list->first->element;
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return element;
  }
  Node_ptr p_walk = list->first;
  Element removed_element;

  while (p_walk->next != NULL)
  {
    if (p_walk->next->next == NULL)
    {
      list->last = p_walk;
      removed_element = p_walk->next->element;
      p_walk->next = NULL;
      list->length--;
    }
    p_walk = p_walk->next;
  }
  if (list->length == 0)
  {
    list->first = NULL;
    list->last = NULL;
  }
  return removed_element;
}

Status is_valid_position(int position, int count)
{
  if (position > count || position < 0)
  {
    return Failure;
  }
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{ 
  int valid = is_valid_position(position, list->length);
  if (!valid) return Failure;
  
  if (position == 0)
  {
    return add_to_start(list, element); 
  }
  if (list->length == position)
  {
    return add_to_list(list, element);
  }
  
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) return Failure;

  Prev_curr_ptr prev_curr = malloc(sizeof(Prev_curr_ptr));
  prev_curr->current = list->first;
  prev_curr->previous = list->first;
  int count = 0;  
  while (count < position)
  {
    prev_curr->previous = prev_curr->current;
    prev_curr->current = prev_curr->current->next;
    count++;
  }
  new_node->next = prev_curr->current;
  prev_curr->previous->next = new_node;
  list->length++;
  return Success;
}

Element remove_at(List_ptr list, int position)
{
  int valid = is_valid_position(position, list->length - 1);
  if (!valid) return NULL;
  if (position == 0)
  {
    return remove_from_start(list);
  }

  if (position == list->length - 1)
  {
    return remove_from_end(list);
  }
  
  Node_ptr p_walk = list->first;
  int count = 0;
  while (count < position - 1)
  {
    p_walk = p_walk->next;
    count++;
  }

  Node_ptr next = p_walk->next->next;
  Element removed_element = p_walk->next->element;
  p_walk->next = next;
  list->length--;
  if (list->length == 0)
  {
    list->first = NULL;
    list->last = NULL;
  }
  return removed_element;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  int position = 0;
  Element removed_element = NULL;
  while (p_walk != NULL)
  {
    if (matcher(p_walk->element,element) == Success) 
    {
      removed_element = remove_at(list, position);
      return removed_element;
    }
    p_walk = p_walk->next;
    position++;
  }
  return removed_element;
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  int position = 0;
  List_ptr removed_elements_list = create_list();
  while (p_walk != NULL)
  {
    if (matcher(p_walk->element, element) == Success)
    {
      remove_at(list, position);
      add_to_list(removed_elements_list, element);
      position--;
    }
    p_walk = p_walk->next;
    position++;
  }
  return removed_elements_list;
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr new_node = create_node(element);
  Node_ptr p_walk = list->first;
  if (list->first == NULL)
  {
    list->first = new_node;
    list->last = new_node;
    list->length++;
    return Success;
  }
  while (p_walk != NULL && matcher(p_walk->element, element) == Failure)
  {
    if (p_walk->next == NULL)
    {
      p_walk->next = new_node;
      list->last = new_node;
      list->length++;
      return Success;
    }
    p_walk = p_walk->next;
  }
  return Failure;
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
