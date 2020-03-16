// Pause the shell until enter is pressed
#include "c_shell.h"

void c_pause(void){
    int c;
    while((c = getchar()) != '\n'){
        fflush(stdin);
    }
}
