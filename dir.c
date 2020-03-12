// list the current files/subdirectories in the current directory

#include "c_shell.h"
int dir(char * path){
    char buffer[MAX_PATH] = {'\0'};
    if(path == NULL){ // use the current directory
        getcwd(buffer, MAX_PATH);
        path = buffer;
    }
    DIR *dir_stream;
    if((dir_stream = opendir(path)) == NULL){ // open the argument path
        fprintf(stderr, "%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    struct dirent *dir;
    while((dir = readdir(dir_stream)) != NULL){ // read file names and print
        printf("%s\n", dir->d_name);
    }
    return EXIT_SUCCESS;
}
