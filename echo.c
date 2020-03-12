#include "c_shell.h"

int echo(char **string){
    if(*string == NULL){ // no argument specified
        return 1;
    }
    while(*string != NULL){
        printf("%s ", *string);
        string++;
    }
    puts("");
    return 1;
}
