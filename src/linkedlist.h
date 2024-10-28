#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

// Datatypes
typedef struct node {
  // TODO: Rethink if the node should store a reference to the linked-list.
  struct node* prev;
  struct node* next;
  size_t data;
} node_t;


// Creation
node_t* node_create(size_t data);

// Checks
bool is_head_node(node_t* node);
bool is_tail_node(node_t* node);
bool is_middle_node(node_t* node);

// Inserting
void ll_insert_at_beginning(node_t** headRef, size_t data);
node_t* ll_insert_at_end(node_t** headRef, size_t data);
node_t* ll_insert_after(node_t* after, size_t data);

// Deleting
void ll_delete(node_t* node);
void ll_delete_from_beginning(node_t** headRef);
void ll_delete_from_end(node_t** headRef);
void ll_free(node_t** headRef);

// Printing
void ll_print(node_t* node);
void ll_print_ex(node_t* node, bool reverse);

#endif // _LINKED_LIST_H_
