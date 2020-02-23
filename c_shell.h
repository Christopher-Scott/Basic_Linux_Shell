

#ifndef LAB2_C_SHELL_H
#define LAB2_C_SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct cmd_node{
    char * cmd;
    char ** argv;
    char * input;
    char * output;
    char * append;
    struct cmd_node * pipe; // a pointer to the next command in a pipe chain
}cmd_node;

// Data Structures
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

// Data Structure Functions
queue * init_queue(void);
int enqueue(queue *, struct cmd_node *);
struct cmd_node * dequeue(queue *);
void print_queue(queue *);

// Shell functions
int parse(char *, queue *);
int create_argv(char ***, char **);


#endif //LAB2_C_SHELL_H
