// Pause the shell until enter is pressed
#include "c_shell.h"

void c_pause(void){
    int c;
    while((c = getchar()) != '\n'){
        // printf("%s\n", "Shell is paused - press enter to unpause");
        fflush(stdin);
    }
}
