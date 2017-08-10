#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct json {
    int val;
    struct list list;
};

int main(void) {
    // declare a list head
    LIST_HEAD(list_head);

    // add json elements to the list
    int i;
    struct json *jsonP;
    for (i = 0; i < 10; i++) {
        jsonP = (struct json *)malloc(sizeof(struct json));

        jsonP->val = i;

        list_add(&jsonP->list, &list_head);
    }

    // iterate all elements in list_head
    list_for_each_entry(jsonP, &list_head, list) {
        printf("%d ", jsonP->val);
    }
    printf("\n");

    // remove one of the element
    // you can only delete node with this safe iterator method
    // 'next' is just a temp variant
    struct json *next;
    list_for_each_entry_safe(jsonP, next, &list_head, list) {
        if (jsonP->val == 5) {
            // use 'list_del' to delete this node
            // use 'list_entry' to get parent structure of list
            free(list_entry(list_del(&jsonP->list), struct json, list));
        }
    }

    // we can also use another iterator method
    struct list *listP;
    list_for_each(listP, &list_head) {
        jsonP = list_entry(listP, struct json, list);

        printf("%d ", jsonP->val);
    }
    printf("\n");

    // create a new list
    LIST_HEAD(another_list);

    // add some elements
    for (i = 0; i < 3; i++) {
        jsonP = (struct json *)malloc(sizeof(struct json));

        jsonP->val = i + 10;

        list_add(&jsonP->list, &another_list);
    }

    // add this list to the tail of list_head
    list_concat(&another_list, &list_head);

    // iterate all elements in list_head
    list_for_each_entry(jsonP, &list_head, list) {
        printf("%d ", jsonP->val);
    }
    printf("\n");

    // push 2 elements
    for (i = 0; i < 2; i++) {
        jsonP = (struct json *)malloc(sizeof(struct json));

        jsonP->val = i + 20;

        list_push(&jsonP->list, &list_head);
    }

    // unshift 2 elements
    for (i = 0; i < 2; i++) {
        jsonP = (struct json *)malloc(sizeof(struct json));

        jsonP->val = i - 20;

        list_unshift(&jsonP->list, &list_head);
    }

    // iterate all elements in list_head
    list_for_each_entry(jsonP, &list_head, list) {
        printf("%d ", jsonP->val);
    }
    printf("\n");

    // pop 1 element
    printf("popped:%d\n", list_entry(list_pop(&list_head), struct json, list)->val);

    // shift 1 element
    printf("shifted:%d\n", list_entry(list_shift(&list_head), struct json, list)->val);

    // iterate all elements in list_head
    list_for_each_entry(jsonP, &list_head, list) {
        printf("%d ", jsonP->val);
    }
    printf("\n");

    return 0;
}
