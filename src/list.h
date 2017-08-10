#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

#ifndef _DS_SHARED_MACRO_
#define _DS_SHARED_MACRO_

// this macro is a simplified version of 'container_of' in Linux Kernel,
// it remove the type checking.
#define container_of(ptr, type, member) ((type *)((char *)(ptr)-offsetof(type, member)))

#endif

struct list {
    struct list *next;
    struct list *prev;
};

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_for_each(ptr, head) \
    for(ptr=(head)->next; \
        (ptr)!=(head); \
        ptr=(ptr)->next)

#define list_for_each_safe(ptr, next, head) \
    for(ptr=(head)->next, next=(ptr)->next; \
        (ptr)!=(head); \
        ptr=next, next=(ptr)->next)

#define list_for_each_entry(ptr, head, member) \
    for(ptr=list_entry((head)->next, __typeof__(*ptr), member); \
        &((ptr)->member)!=(head); \
        ptr=list_entry(((ptr)->member.next), __typeof__(*ptr), member))

#define list_for_each_entry_safe(ptr, next, head, member) \
    for(ptr=list_entry((head)->next, __typeof__(*ptr), member), \
        next=list_entry((ptr)->member.next, __typeof__(*ptr), member); \
        &((ptr)->member)!=(head); \
        ptr=next, next=list_entry((ptr)->member.next, __typeof__(*ptr), member))

#define list_for_each_reverse(ptr, head) \
    for(ptr=(head)->prev; \
        ptr!=head; \
        ptr=ptr->prev)

#define list_for_each_reverse_safe(prt, prev, head) \
    for(ptr=(head)->prev, prev=ptr->prev; \
        ptr!=head; \
        ptr=prev, prev=ptr->prev)

#define list_for_each_reverse_entry(ptr, head, member) \
    for(ptr=list_entry((head)->prev, __typeof__(*ptr), member); \
        &(ptr->member)!=(head); \
        ptr=list_entry(((ptr)->member.prev), __typeof__(*ptr), member))

#define list_for_each_reverse_entry_safe(ptr, prev, head, member) \
    for(ptr=list_entry((head)->prev, __typeof__(*ptr), member), \
        prev=list_entry((ptr)->member.prev, __typeof__(*ptr), member); \
        &((ptr)->member)!=(head); \
        ptr=prev, prev=list_entry((ptr)->member.prev, __typeof__(*ptr), member))

#define LIST_HEAD_INIT(list) {&(list), &(list)}
#define LIST_HEAD(name) struct list name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(list_head) ({(list_head)->next=list_head;(list_head)->prev=list_head;})

int list_is_empty(struct list *list_head);
#define list_empty(head) list_is_empty(head)

struct list *list_add(struct list *node, struct list *list_head);
struct list *list_add_tail(struct list *node, struct list *list_head);

struct list *list_del(struct list *node);
struct list *list_del_init(struct list *node);

struct list *list_splice(struct list *part, struct list *head);
struct list *list_splice_tail(struct list *part, struct list *head);

#define list_concat(part, list) list_splice(part, list)

#define list_move(node, head) list_add(list_del(node), head)
#define list_move_tail(node, head) list_add_tail(list_del(node), head)

#define list_push(node, head) list_add(node, head)
#define list_pop(head) list_del((head)->next)
#define list_shift(head) list_del((head)->prev)
#define list_unshift(node, head) list_add_tail(node, head)

#endif
