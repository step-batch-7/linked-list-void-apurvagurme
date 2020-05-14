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
  return removed_element;
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
  return removed_element;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  int position = 0;
  Status status = Failure;
  while (p_walk != NULL)
  {
    if (p_walk->element == element) 
    {
      return remove_at(list, position);
    }
    p_walk = p_walk->next;
    position++;
  }
  return NULL;
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr new_node = create_node();
  new_node->element = element;
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
