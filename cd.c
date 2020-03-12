// change the current working directory
#include "c_shell.h"

int cd(char *path){
    char buffer[MAX_PATH];
    if(path == NULL){
        printf("%s\n", getcwd(buffer, MAX_PATH));
    }

    else{
        if(chdir(path) < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;

}
