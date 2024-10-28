#include <stdio.h>

#include "linkedlist.h"

#define COUNT 100

int main()
{
  node_t* head = NULL;


  // Example 1
  {
    printf("Example 1:\n");
  
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

    size_t cursor = 0, start = 50, range = 10;
    node_t* current = head;
  
    printf("Deleting inclusive from index %zu to exclusive %zu:\n", start, start + range);

    // Go forward till the start of the deletion range.
    while (current && cursor < start) {
      current = current->next;
      ++cursor;
    }
  
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
}
