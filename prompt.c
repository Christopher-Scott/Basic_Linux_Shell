#include "c_shell.h"
void prompt(char * host, char * pwd){

    printf("%s:\033[1;34m%s\033[0m%s ", host, pwd, "~");
    return;
}
