#include "linked-list.h"

void linked_list_destroy(Linked_list *list) {
    if (list == NULL) {
        return;
    }

    if (list->head != NULL) {
        free(list->head);
        list->head = NULL;
    }

    if (list->tail != NULL) {
        free(list->tail);
        list->tail = NULL;
    }

    free(list);
}

// Create a linked list and return it. Returns NULL on error
Linked_list *linked_list_create(Linked_list_create_params *params, Error_information *error_info) {
    Linked_list *result = NULL;

    if (params->comparator == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_COMPARATOR;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot create a linked list with NULL comparator!");
        }

        return NULL;
    }

    if (params->print_node == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_NODE_PRINT;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot create a linked list with NULL node printer!");
        }

        return NULL;
    }

    if (NULL == (result = calloc(1, sizeof(Linked_list)))) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_ALLOC_FAILURE;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Failed to allocate space for list!");
        }

        goto error_return;
    }

    if (NULL == (result->head = calloc(1, sizeof(Node)))) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_ALLOC_FAILURE;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Failed to allocate space head node!");
        }

        goto error_return;
    }

    if (NULL == (result->tail = calloc(1, sizeof(Node)))) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_ALLOC_FAILURE;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Failed to allocate space tail node!");
        }

        goto error_return;
    }

    result->head->next = result->tail;

    result->comparator = params->comparator;
    result->print_node = params->print_node;

    return result;

error_return:
    if (result != NULL) {
        if (result->head != NULL) {
            free(result->head);
            result->head = NULL;
        }

        if (result->tail != NULL) {
            free(result->tail);
            result->tail = NULL;
        }

        free(result);
        result = NULL;
    }

    return NULL;
}

static Node *create_node(void *data, Error_information *error_info) {
    Node *new_node = NULL;

    if (NULL == (new_node = calloc(1, sizeof(Node)))) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_ALLOC_FAILURE;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Failed to allocate space for new node!");
        }

        return NULL;
    }

    new_node->data = data;

    return new_node;
}

// Create a Node with given data and insert into list. Returns created node or NULL on error.
Node *linked_list_insert_tail(Linked_list *list, void *data, Error_information *error_info) {
    Node *current_node = NULL;
    Node *previous_node = NULL;
    Node *new_node = NULL;

    if (list == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot insert into a NULL list!");
        }

        return NULL;
    }

    if (NULL == (new_node = create_node(data, error_info))) {
        return NULL;
    }

    // Find the node before the tail
    for (current_node = list->head; current_node != list->tail; previous_node = current_node, current_node = current_node->next) {
        ; // Do nothing, just traverse the list
    }

    new_node->next = previous_node->next;
    previous_node->next = new_node;

    return new_node;
}

Node *linked_list_insert_head(Linked_list *list, void *data, Error_information *error_info) {
    Node *new_node = NULL;

    if (list == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot insert into a NULL list!");
        }

        return NULL;
    }

    if (NULL == (new_node = create_node(data, error_info))) {
        return NULL;
    }

    new_node->next = list->head->next;
    list->head->next = new_node;

    return new_node;
}

// Find the first node in list matching the given data. Returns found node or NULL on error.
Node *linked_list_find(Linked_list *list, void *data, Error_information *error_info) {
    if (list == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot find from a NULL list!");
        }

        return NULL;
    }
    
    return NULL;
}

// TODO: Consider returning the node's data and freeing the node here, instead of putting that on the user
// Remove the first node in the list. Returns deleted node or NULL on error.
Node *linked_list_pop_head(Linked_list *list, Error_information *error_info) {
    Node *result = NULL;

    if (list == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot pop from a NULL list!");
        }

        return NULL;
    }

    if (list->head->next == list->tail) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_EMPTY_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot pop from an empty list!");
        }

        return NULL;
    }
    
    result = list->head->next;
    list->head->next = list->head->next->next;

    return result;
}

// Remove the last node in the list. Returns deleted node or NULL on error.
Node *linked_list_pop_tail(Linked_list *list, Error_information *error_info) {
    Node *current_node = NULL;
    Node *previous_node = NULL;
    Node *result = NULL;

    if (list == NULL) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_NULL_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot pop from a NULL list!");
        }

        return NULL;
    }

    if (list->head->next == list->tail) {
        if (error_info != NULL) {
            error_info->error_code = LINKED_LIST_ERROR_EMPTY_LIST;
            snprintf(error_info->error_message, sizeof(error_info->error_message), "Cannot pop from an empty list!");
        }

        return NULL;
    }

    // Find the node before the tail
    for (current_node = list->head; current_node->next != list->tail; previous_node = current_node, current_node = current_node->next) {
        ; // Do nothing, just traverse the list
    }

    result = current_node;
    previous_node->next = current_node->next;

    return result;
}

void linked_list_print(Linked_list *list) {
    Node *node = NULL;
    int i = 0;

    if (list == NULL) {
        return;
    }

    for (i = 0, node = list->head->next; node != list->tail; i++, node = node->next) {
        list->print_node(i, node);
    }
}

