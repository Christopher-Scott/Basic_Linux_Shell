#include "c_shell.h"

// Iteratively prints the elements in the queue to stdout
void print_queue(queue *const the_queue){
    node * where = the_queue->head;
    cmd_node * cmd;
    int i = 0;
    while(where->next != NULL){
        puts("");
        printf("%d: %p {%s}\n", i, where, where->datum->cmd);
        cmd = where->datum;
        while(cmd != NULL){ // iterate cmd list
            for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
                printf("%s ", cmd->argv[i]);
            printf("\ninput: %s \noutput: %s \nappend: %s\npipe: %p\n",
                cmd->input, cmd->output, cmd->append, cmd->pipe);
            cmd = cmd->pipe;
            puts("");
        }
        where = where->next;
        i++;
    }
    puts("");
    printf("%d: %p {%s}\n", i, where, where->datum->cmd);
    cmd = where->datum;
    while(cmd != NULL){ // iterate cmd list
        for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
            printf("%s ", cmd->argv[i]);
        printf("\ninput: %s \noutput: %s \nappend: %s\npipe: %p\n",
            cmd->input, cmd->output, cmd->append, cmd->pipe);
        cmd = cmd->pipe;
        puts("");
    }
}
