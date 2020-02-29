#include "c_shell.h"
void prompt(char * pwd){
    // printf("(%u)\033[1;34m%s\033[0m%s ",getpid(), pwd, "~");
    printf("\033[1;34m%s\033[0m%s ", pwd, "~");
    return;
}
