#include "list.h"

struct list *list_add(struct list *node, struct list *list_head) {
    node->prev = list_head;
    node->next = list_head->next;
    list_head->next->prev = node;
    list_head->next = node;

    return node;
}

struct list *list_add_tail(struct list *node, struct list *list_head) {
    node->next = list_head;
    node->prev = list_head->prev;
    list_head->prev->next = node;
    list_head->prev = node;

    return node;
}

struct list *list_del(struct list *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    return node;
}

struct list *list_del_init(struct list *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    INIT_LIST_HEAD(node);

    return node;
}

struct list *list_splice(struct list *part, struct list *head) {
    struct list *first = part->next;
    struct list *last = part->prev;

    if (!list_is_empty(part)) {
        first->prev = head;
        last->next = head->next;
        head->next->prev = last;
        head->next = first;
    }

    return head;
}

struct list *list_splice_tail(struct list *part, struct list *head) {
    struct list *first = part->next;
    struct list *last = part->prev;

    if (!list_is_empty(part)) {
        first->prev = head->prev;
        last->next = head;
        head->prev->next = first;
        head->prev = last;
    }

    return head;
}

int list_is_empty(struct list *list_head) {
    if (list_head->next == list_head) return 1;

    return 0;
}
