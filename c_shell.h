

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
#include <dirent.h>

#define MAX_PATH 256

typedef struct cmd_node{
    char * cmd;
    char ** argv;
    char * input;
    char * output;
    char * append;
    struct cmd_node * pipe; // a pointer to the next command in a pipe chain
    short background;
}cmd_node;

enum builtins{
    CD, B_DIR, ENV, CLR, ECHO, HELP, PAUSE, EXIT
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
int clean_node(cmd_node *);
cmd_node *init_cmd(void);
void prompt(char *);
char *fullpath(char *, const char *, const char *, size_t);

// built ins
int echo(char **);
int cd(char *);
int clr(void);
int dir(char *);
int env(char *);
int help(void);
void c_pause(void);


#endif //LAB2_C_SHELL_H
