// Determine if the arg cmd is a built in function
// return the index where it is found or -1 if not a built in
#include "c_shell.h"
#define NUM_BUILTINS 8
int is_builtin(const char *cmd){
    char *builtins[NUM_BUILTINS] = {"cd", "dir", "environ", "clr", "echo", "help", "pause", "exit"};
    for(int i = 0; i < NUM_BUILTINS; i++){
        if(strcmp(builtins[i], cmd) == 0)
            return i;
    }
    return -1;
}
