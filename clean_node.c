// frees allocated memory in cmd structure

#include "c_shell.h"

int clean_node(cmd_node * cmd){
    char **temp;
    cmd_node *prev;
    while(cmd != NULL){
        temp = cmd->argv;
        while(*temp != NULL){ // iterate over argv
            free(*temp); // free the allocated string
            temp++;
        }
        free(*temp); // free the last element
        free(cmd->argv); // free the array
        prev = cmd;
        cmd = cmd->pipe;
        free(prev); // free the previous command node
    }
    return 0;
}
