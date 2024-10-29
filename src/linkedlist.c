#include "linkedlist.h"

#include <stdio.h>
#include <assert.h>

node_t* node_create(size_t data)
{
  node_t* node = (node_t*) malloc(sizeof(node_t));
  
  assert(node && "Not enough memory!");

  node->prev = NULL;
  node->next = NULL;
  node->data = data;
  
  return node;
}


bool is_head_node(node_t* node)
{
  assert(node && "Given 'node' was NULL!");

  return !node->prev;
}

bool is_tail_node(node_t* node)
{
  assert(node && "Given 'node' was NULL!");

  return !node->next;
}

bool is_middle_node(node_t* node)
{
  assert(node && "Given 'node' was NULL!");

  return !node->next && !node->prev;
}


void ll_insert_at_beginning(node_t** headRef, size_t data)
{
  if (*headRef)
    assert(is_head_node(*headRef) && "Given 'headRef' was NOT the head-node!");

  node_t* newHead = node_create(data);

  newHead->next = *headRef;

  if (*headRef)
    (*headRef)->prev = newHead;

  *headRef = newHead;
}

node_t* ll_insert_at_end(node_t** headRef, size_t data)
{
  assert(*headRef && "Given 'headRef' was NULL!");

  node_t* tmp = *headRef;
  
  while (!is_tail_node(tmp))
    tmp = tmp->next;
  
  node_t* newNode = node_create(data);
  
  tmp->next = newNode;
  newNode->prev = tmp;

  return newNode;
}

node_t* ll_insert_after(node_t* after, size_t data)
{
  assert(after && "Given 'node' was NULL!");

  node_t* tmp = after->next;

  node_t* newNode = node_create(data);
  
  after->next = newNode;

  if (tmp) {
    newNode->next = tmp;
    tmp->prev = newNode;
    after->next = newNode;
  }

  newNode->prev = after;

  return newNode;
}

node_t* ll_insert_at(node_t** headRef, size_t index, size_t data)
{
  assert(*headRef && "Given 'headRef' was NULL!");

  if (index <= 0)
    ll_insert_at_beginning(headRef, data);

  node_t* tmp = (*headRef)->next;

  for (size_t i = 0; tmp && i < index - 2; ++i)
    tmp = tmp->next;
  
  // TODO: Rethink if this should be an assert!
  assert(tmp && "Out of bounds!");

  return ll_insert_after(tmp, data);
}

void ll_delete(node_t* node)
{
  assert(node && "Given 'node' was NULL!");
  assert(!is_head_node(node) && "Can't delete the 'head-node' here! Use: ll_delete_from_beginning(..) for this.");
  
  if (is_tail_node(node))
    node->prev->next = NULL;
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  free(node);
}

void ll_delete_at(node_t** headRef, size_t index)
{
  assert(*headRef && "Given 'headRef' was NULL");
  
  if (index <= 0)
    ll_delete_from_beginning(headRef);

  node_t* tmp = (*headRef)->next;

  for (size_t i = 0; tmp && i < index; ++i)
    tmp = tmp->next;

  // TODO: Rethink if this should be an assert!
  assert(tmp && "Out of bounds!");

  ll_delete(tmp);
}

void ll_delete_from_beginning(node_t** headRef)
{
  assert(*headRef && "Given 'headRef' was NULL!");
  
  node_t* tmp = *headRef;
  
  *headRef = (*headRef)->next;
  (*headRef)->prev = NULL;

  free(tmp);
}

void ll_delete_from_end(node_t** headRef)
{
  assert(*headRef && "Given 'headRef' was NULL!");

  if (!(*headRef)->next)
  {
    free(*headRef);
    *headRef = NULL;
    return;
  }

  node_t* tmp = *headRef;

  while (!is_tail_node(tmp->next))
    tmp = tmp->next;

  free(tmp->next);
  tmp->next = NULL;
}

void ll_free(node_t** headRef)
{
  assert(headRef && "Given 'headRef' was NULL!");

  node_t* tmp;

  while (*headRef)
  {
    tmp = *headRef;
    *headRef = (*headRef)->next;
    
    free(tmp);
  }

  free(*headRef);
}


void ll_print(node_t* node)
{
  assert(node && "Given 'node' was NULL!");

  node_t* tmp = node;
  
  while (tmp)
  {
    printf("%zu", tmp->data);

    if (!is_tail_node(tmp))
      printf(",");
    
    tmp = tmp->next;
  }

  printf("\n");
}

void ll_print_ex(node_t* node, bool reverse)
{
  if (!reverse) {
    ll_print(node);
    return;
  }

  assert(node && "Given 'node' was NULL!");

  node_t* tmp = node;
    
  while (tmp->next)
    tmp = tmp->next;
  
  while(!is_head_node(tmp)) {
    printf("%zu,", tmp->data);
    tmp = tmp->prev;
  }

  printf("%zu\n", tmp->data);
}
