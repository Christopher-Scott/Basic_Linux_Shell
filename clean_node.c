// frees allocated memory in cmd structure

#include "c_shell.h"

int clean_node(cmd_node * cmd){
    char **temp = NULL;
    cmd_node *prev;
    while(cmd != NULL){
        temp = cmd->argv;
        while(*temp != NULL){ // iterate over argv
            free(*temp); // free the allocated string
            temp++;
        }
        free(cmd->argv); // free the array
        prev = cmd;
        cmd = cmd->pipe;
        free(prev);
    //     free(prev); // free the previous command node
        // for(int i = 0; cmd->argv[i] != NULL; i++){
        //     temp = cmd->argv[i];
        //     free(temp);
        // }
        // free(cmd->argv);
        // prev = cmd;
        // cmd = cmd->pipe;
        // free(prev);
    }

    return 0;
}
