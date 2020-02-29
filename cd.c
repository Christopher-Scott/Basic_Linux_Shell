// change the current working directory
#include "c_shell.h"

int cd(char *path){
    char buffer[MAX_PATH];
    if(path == NULL){
        printf("%s\n", getcwd(buffer, MAX_PATH));
    }
    else if(*path == '.'){ // relative path
        getcwd(buffer, MAX_PATH);
        path++;
        strcat(buffer, path);
        if(chdir(buffer) < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    else{ // path is an absolute path
        if(chdir(path) < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;

}
