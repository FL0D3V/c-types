#include <stdio.h>

#include "linkedlist.h"
#include "darray.h"
#include "stringslice.h"

#define COUNT 100

void test_linked_list();
void test_dynamic_array_and_string_slice();

int main()
{
  test_linked_list();

  test_dynamic_array_and_string_slice();
}

void test_linked_list()
{
  printf("Testing the linked-list\n\n");

  node_t* head = NULL;

  // Example 1
  {
    printf("Example 1:\n");
    printf("Testing insert-at-beginning and different printing variations:\n");
  
    for (size_t i = 0; i < COUNT; ++i)
      ll_insert_at_beginning(&head, i);

    printf("Printing normally:\n");
    ll_print(head);

    printf("Printing reversed:\n");
    ll_print_ex(head, true);
  
    ll_free(&head);
  
    printf("\n");
  }

  // Example 2
  {
    printf("Example 2:\n");
    printf("Testing insert at end:\n");
  
    size_t i = 0; 
    
    ll_insert_at_beginning(&head, i++);

    for (; i < COUNT; ++i)
      ll_insert_at_end(&head, i);
  
    printf("Printing normally:\n");
    ll_print(head);
    
    ll_free(&head);

    printf("\n");
  }

  // Example 3
  {
    printf("Example 3:\n");
    printf("Testing insert-after and insert-at-beginning with different variations:\n");
  
    size_t i = 0;
    
    ll_insert_at_beginning(&head, i++);
    
    node_t* tmp = head;
    node_t* test;
  
    for (; i < COUNT; ++i) {
      if (i < COUNT / 2) {
        tmp = ll_insert_after(tmp, i);

        if (i == COUNT / 4)
          test = tmp;
      }
      else {
        test = ll_insert_after(test, i);
      }
    }
    
    printf("Printing normally:\n");
    ll_print(head);

    printf("Printing reversed:\n");
    ll_print_ex(head, true);

ll_free(&head);

    printf("\n");
  }

  // Example 4
  {
    printf("Example 4:\n");
    printf("Testing the deletion of nodes in a specific range:\n");

    // Filling the linked-list.
    size_t i = 0;

    ll_insert_at_beginning(&head, i++);
    
    node_t* fillTemp = head;

    for (; i < COUNT; ++i)
        fillTemp = ll_insert_after(fillTemp, i);

    size_t start = 50, range = 10;
    node_t* current = head;
  
    printf("Deleting inclusive from index %zu to exclusive %zu:\n", start, start + range);

    // Go forward till the start of the deletion range.
    for (size_t cursor = 0; current && cursor < start; ++cursor)
      current = current->next;
  
    // Delete the selected range.
    node_t* tmp = current;

    for (size_t i = 0; tmp && i < range; i++) {
      tmp = current->next;
      ll_delete(current);
      current = tmp;
    }
  
    printf("Printing normally:\n");
    ll_print(head);

    ll_free(&head);

    printf("\n");
  }

  // Example 5
  {
    printf("Example 5:\n");
    printf("Trying to delete the current head:\n");
    
    // Filling the linked-list.
    size_t i = 0;

    ll_insert_at_beginning(&head, i++);
    
    node_t* tmp = head;

    for (; i < COUNT; ++i)
        tmp = ll_insert_after(tmp, i);

    // INFO: This will result in an error!
    //ll_delete(head);
    ll_delete_from_beginning(&head);
  
    printf("Printing normally:\n");
    ll_print(head);

    ll_free(&head);

    printf("\n");
  }

  // Example 6
  {
    const size_t INSERT_AT_INDEX = COUNT / 2;

    printf("Example 6:\n");
    printf("Trying to insert and delete at index=%zu:\n", INSERT_AT_INDEX);

    // Inserting till the specified index to test on a full list.
    size_t i = 0;

    ll_insert_at_beginning(&head, i++);

    node_t* tmp = head;
    
    // Insert only halve the values with this method just to have enough room
    // for the rest.
    for (; i < INSERT_AT_INDEX; ++i)
      tmp = ll_insert_after(tmp, i);
    
    size_t finalIndex = i;

    // Testing the insertion at a specific index.
    for (; i < COUNT; ++i)
      ll_insert_at(&head, finalIndex, i);
    
    printf("Printing normally:\n");
    ll_print(head);
    
    // Testing the deletion at the index.
    const size_t DELETE_AT_INDEX = INSERT_AT_INDEX + COUNT / 4;
    
    printf("Deleting at a specific index:\n");
    
    for (size_t di = 0; di < 10; ++di)
      ll_delete_at(&head, DELETE_AT_INDEX);
    
    printf("Printing normally:\n");
    ll_print(head);

    ll_free(&head);

    printf("\n");
  }
}


void test_dynamic_array_and_string_slice()
{
  printf("Testing the dynamic-array and string-slice\n\n");

  string_slice_t ss = {0};
  string_builder_t sb = {0};

  const char* input = "   a b c 1 2 3  ";

  ss_init(&ss, input);

  printf("Input='%s', Length='%zu'\n", input, strlen(input));

  while (ss_in_range(&ss))
  {
    ss_seek_spaces(&ss);

    if (!ss_in_range(&ss))
      break;

    sb_append_char(&sb, ss_get_current(&ss));

    ss_seek(&ss);
  }

  printf("Checked='%s'; Length='%zu'\n", sb.items, sb.count);

  printf("\n");

  sb_free(sb);
}
