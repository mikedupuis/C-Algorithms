#ifndef __C_ALGORITHMS_LINKED_LIST
#define __C_ALGORITHMS_LINKED_LIST

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    LINKED_LIST_ERROR_NULL_LIST = -1000,
    LINKED_LIST_ERROR_EMPTY_LIST = -1001,
    LINKED_LIST_ERROR_ALLOC_FAILURE = -1002,
    LINKED_LIST_ERROR_NULL_COMPARATOR = -1003,
    LINKED_LIST_ERROR_NULL_NODE_PRINT = -1004
} Linked_list_api_error_code;

typedef struct {
    Linked_list_api_error_code error_code;
    char error_message[512];
} Error_information;

typedef struct node {
    struct node *next;
    void *data;
} Node;

typedef int (*comparator_function)(void *x, void *y);
typedef void (*node_print_function)(int index, Node *node);

typedef struct {
    Node *head;
    Node *tail;
    comparator_function comparator;
    node_print_function print_node;
} Linked_list;

typedef struct {
    comparator_function comparator;
    node_print_function print_node;
} Linked_list_create_params;

// Destroy a linked list
void linked_list_destroy(Linked_list *list);

// Create a linked list and return it. Returns NULL on error
Linked_list *linked_list_create(Linked_list_create_params *params, Error_information *error_info);

// Create a Node with given data and insert into the tail of the list. Returns created node or NULL on error.
Node *linked_list_insert_tail(Linked_list *list, void *data, Error_information *error_info);

// Create a Node with given data and insert into the head of the list. Returns created node or NULL on error.
Node *linked_list_insert_head(Linked_list *list, void *data, Error_information *error_info);

// Find the first node in list matching the given data. Returns found node or NULL on error.
Node *linked_list_find(Linked_list *list, void *data, Error_information *error_info);

// Remove the first node in the list. Returns deleted node or NULL on error.
Node *linked_list_pop_head(Linked_list *list, Error_information *error_info);

// Remove the last node in the list. Returns deleted node or NULL on error.
Node *linked_list_pop_tail(Linked_list *list, Error_information *error_info);

// Print the lists using the list's printing functions
void linked_list_print(Linked_list *list);

#endif // __C_ALGORITHMS_LINKED_LIST
