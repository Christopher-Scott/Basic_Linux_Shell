// search the directories in path_list and attempt to access executable
// if successful, modifies the cmd_node to have full path
// returns 1 on success or 0 on failure
#include "c_shell.h"
int buildpath(char **path, cmd_node *cmd){
    char buffer[MAX_PATH];
    char *temp;
    int i;
    while(*path != NULL){
        strcpy(buffer, *path);
        i = strlen(buffer) - 1;
        // if there is a pathname in the pathlist without an ending '/'
        // assume it is a directory and append a '/'
        if(buffer[i] != '/')
            strcat(buffer, "/");
        strcat(buffer, cmd->cmd);
        if(access(buffer, X_OK) != -1){ // full path found
            temp = cmd->argv[0];
            size_t n = strlen(buffer);
            if((cmd->argv[0] = (char *) malloc(n)) == NULL){
                fprintf(stderr, "%s\n", "Error: Allocation");
                return EXIT_FAILURE;
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
