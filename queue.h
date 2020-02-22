#ifndef QUEUE_H
#define QUEUE_H

#include "c_shell.h"

typedef struct node{
    struct cmd_node * datum;
    struct node * next;
} node;

typedef struct queue{
    size_t size;
    node * head;
    node * tail;
    short background;
} queue;

queue * init_queue(void);
int enqueue(queue *, const struct cmd_node *);
struct cmd_node * dequeue(queue *);
void print_queue(queue *);

#endif
