#include <stdio.h>
#include "linked-list.h"

int int_comparator(void *x, void *y) {
    int *value_x = (int *)x;
    int *value_y = (int *)y;

    if (value_x == NULL) {
        return -1;
    }

    if (value_y == NULL) {
        return -1;
    }

    return *value_x - *value_y;
}

void int_node_print(int index, Node *node) {
    printf("item %d: %d\n", index, *((int*)(node->data)));
}

int insert_node_tail(Linked_list *list, int value, Error_information *error_info) {
    int *data = NULL;
    if (NULL == (data = calloc(1, sizeof(int)))) {
        return 0;
    }

    *data = value;

    if (NULL == linked_list_insert_tail(list, data, error_info)) {
        free(data);
        data = NULL;
        return 0;
    }

    return 1;
}

int insert_node_head(Linked_list *list, int value, Error_information *error_info) {
    int *data = NULL;
    if (NULL == (data = calloc(1, sizeof(int)))) {
        return 0;
    }

    *data = value;

    if (NULL == linked_list_insert_head(list, data, error_info)) {
        free(data);
        data = NULL;
        return 0;
    }

    return 1;
}

int populate_list(Linked_list *list, Error_information *error_info) {
    if (!insert_node_head(list, 1, error_info)) {
        return 0;
    }

    if (!insert_node_head(list, 3, error_info)) {
        return 0;
    }

    if (!insert_node_head(list, 2, error_info)) {
        return 0;
    }

    if (!insert_node_tail(list, 1, error_info)) {
        return 0;
    }

    if (!insert_node_tail(list, 3, error_info)) {
        return 0;
    }

    if (!insert_node_tail(list, 2, error_info)) {
        return 0;
    }

    return 1;
}

int pop_list_head(Linked_list *list, Error_information *error_info, int *value) {
    Node *popped_node = NULL;

    if (NULL == (popped_node = linked_list_pop_head(list, error_info))) {
        return 0;
    }

    *value = (*(int *)(popped_node->data));
    return 1;
}

int pop_list_tail(Linked_list *list, Error_information *error_info, int *value) {
    Node *popped_node = NULL;
    
    if (NULL == (popped_node = linked_list_pop_tail(list, error_info))) {
        return 0;
    }

    *value = (*(int *)(popped_node->data));
    return 1;
}

int pop_list(Linked_list *list, Error_information *error_info) {
    int i = 0;
    int popped_value = 0;

    for (i = 0; i < 3; i++) {
        if (!pop_list_head(list, error_info, &popped_value)) {
            return 0;
        }
        printf("popped from head: %d\n", popped_value);
    
        if (!pop_list_tail(list, error_info, &popped_value)) {
            return 0;
        }
        printf("popped from tail: %d\n", popped_value);
    }

    if (pop_list_head(list, error_info, &popped_value)) {
        printf("Unexpected success from pop_list_head (%d)!\n", popped_value);
    }

    if (pop_list_tail(list, error_info, &popped_value)) {
        printf("Unexpected success from pop_list_tail (%d)!\n", popped_value);
    }

    return 1;
}

int main(int argc, char **argv) {
    Error_information error_info = {0, ""};
    Linked_list_create_params linked_list_create_params = {
        .comparator = int_comparator,
        .print_node = int_node_print
    };
    Linked_list *list = NULL;

    printf("Initializing list... ");
    if (NULL == (list = linked_list_create(&linked_list_create_params, &error_info))) {
        printf("failed!\nError code: %d\nError message: %s\n", error_info.error_code, error_info.error_message);
        return -1;
    }
    printf("done.\n");

    printf("Inserting into list...");
    if (!populate_list(list, &error_info)) {
        printf("failed!\nError code: %d\nError message: %s\n", error_info.error_code, error_info.error_message);
        return -1;
    }
    printf("done.\n");

    printf("Printing list...\n");
    linked_list_print(list);
    printf("done.\n");

    printf("Popping off list...\n");
    if (!pop_list(list, &error_info)) {
        printf("failed!\nError code: %d\nError message: %s\n", error_info.error_code, error_info.error_message);
        return -1;
    }
    printf("done.\n");

    printf("Printing list...\n");
    linked_list_print(list);
    printf("done.\n");

    printf("destroying list... ");
    linked_list_destroy(list);
    list = NULL;
    printf("done.\n");

    return 0;
}
