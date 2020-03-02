// Clear the current terminal window of previous commands
#include "c_shell.h"

int clr(void){
    printf("%s","\033[H\033[2J");
    return EXIT_SUCCESS;
}
