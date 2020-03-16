// display the manual for the shell using the 'less' program
#include "c_shell.h"
#define READ 0
#define WRITE 1

int help(void){
    int status;
    pid_t pid;
    extern char shell_path[];
    char buffer[MAX_PATH];
    // grab the path to the shell program directory and concat the readme filename
    strncpy(buffer, shell_path, strlen(shell_path) - strlen("myshell"));
    strcat(buffer, "readme");


    if((pid = fork()) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if(pid == 0){ // child
        // Using exec ensures that the help command supports redirection
        execlp("less", "less", buffer, NULL);
        return EXIT_FAILURE;
    }
    else{ // parent
        waitpid(pid, &status, 0);
    }
    // clear buffer, not sure why but this fixes a bug where "readme" would
    // be concatenated twice onto buffer on subsequent calls to help.
    memset(buffer, '\0', sizeof(buffer));
    return EXIT_SUCCESS;
}
