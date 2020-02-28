// search the directories in path_list and attempt to access executable
// if successful, modifies the cmd_node to have full path
// returns 1 on success or 0 on failure
#include "c_shell.h"
#define MAX_PATH 256
int buildpath(char **path, cmd_node *cmd){
    char buffer[MAX_PATH];
    char *temp;
    while(*path != NULL){
        strcpy(buffer, *path);
        strcat(buffer, cmd->cmd);
        if(access(buffer, X_OK) != -1){ // full path found
            temp = cmd->argv[0];
            size_t n = strlen(buffer);
            if((cmd->argv[0] = (char *) malloc(n)) == NULL){
                fprintf(stderr, "%s\n", "Error: Allocation");
                exit(EXIT_FAILURE);
            }
            memcpy(cmd->argv[0], buffer, n);
            cmd->cmd = cmd->argv[0];
            free(temp); // free the token that was previously held
            return 1;
        }
        path++;
    }
    return 0;
}
