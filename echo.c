#include "c_shell.h"

int echo(char **string){
    while(*string != NULL){
        printf("%s ", *string);
        string++;
    }
    puts("");
    return 1;
}
