# klist

## intro

This project is inspired by list implemented in Linux Kernel. If you are familiar with Linux Kernel, you will not meet any barrier when using it. I rewrite the code with c99 standard to remove all hardware and system details, making it suitable for general C application. And I also add some useful interface such as 'concat', 'push', 'pop', 'shift', 'unshift', i love JavaScipt :P

See these links if you still have doubts:
1. [Linked Lists](https://kernelnewbies.org/FAQ/LinkedLists)
2. [klist](http://isis.poly.edu/kulesh/stuff/src/klist/)

## How to install

copy the source files directly or use cmake to generate a static library.

## Usage

Just put the `struct list` into your own struct, and you can operate it with API in klist:

```c
struct node {
    int val;
    struct list list_node;
};
```

for more, see `examples/example.c`

## API

### hints

1. Every list has a head, and head is an instance of `struct list`(no matter what kind of data structure it really stores)
2. We called container of `struct list` -- entry, for example, `struct node`
3. If you get a `struct list`, you can use `list_entry` to get its container

### iterator

```c
struct list list_head;
struct list *node, *next
struct node *entry;

list_for_each(node, &list_head) {
    // 'node' will pointed to 'struct list' in each 'struct node'
}

// 'list_node' represents the name of 'struct list' in its container
list_for_each_entry(entry, &list_head, list_node) {
    // 'entry' will point to each 'struct node' in list
}

list_for_each_safe(node, next, &list_head, list_node) {
    // the same as 'list_for_each', but you can safely remove the during the iteration
}

list_for_each_entry_safe(entry, next, &list_head, list_node) {
    // 'entry' is pointed to the entry of 'struct list'
}

// these interfaces have the same usage with those above, but have opposite iteration direction
list_for_each_reverse()
list_for_each_reverse_entry()
list_for_each_reverse_safe()
list_for_each_reverse_entry_safe()
```

### init

Three ways to init a list are available:
```c
// first one: static declaration in a structure
// LIST_HEAD_INIT(name)
// hint: data in my node will not be iterated, to avoid this, use second one
struct node mynode = {
    12,
    LIST_HEAD_INIT(&mynode.list_node)
}

// second: decarle an variant
// LIST_HEAD(name)
// equal to 'struct list list_head = {&list_head, &list_head}'
LIST_HEAD(list_head);

// third: dynamic init
// INIT_LIST_HEAD(&list_head);
// equal to '&list_head->next=&list_head;&list_head->prev=&list_head'
INIT_LIST_HEAD(&list_head)

```

### operation

see `src/klist.h` from line 68 to the end

## At last

Further test and bug report are need. I'm VERY VERY VERY appreciated if you send your suggestion, bug report or pull request to me.
