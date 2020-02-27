

#ifndef LAB2_C_SHELL_H
#define LAB2_C_SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct cmd_node{
    char * cmd;
    char ** argv;
    char * input;
    char * output;
    char * append;
    struct cmd_node * pipe; // a pointer to the next command in a pipe chain
}cmd_node;

enum builtins{
    CD, DIR, ENVIRON, CLR, ECHO, HELP, PAUSE, EXIT
};

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
int is_builtin(const char *);
int run_builtin(const cmd_node *, const int);
int buildpath(char **, cmd_node *);


#endif //LAB2_C_SHELL_H
