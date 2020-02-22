#include "c_shell.h"

int main(){
    char **argv = NULL;
    char *toks[3]  = {"echo", "blahblah", NULL};
    printf("argv at: %p", argv);
    int n = create_argv(&argv, toks);
    printf("%d toks copied to argv at: %p", n, argv);
    while(*argv != NULL){
        printf("%s ", *argv++);
    }
    puts("");
}
