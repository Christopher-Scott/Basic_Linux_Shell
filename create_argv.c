#include "c_shell.h"
#define DEF_ARRSIZE 3

// create_argv takes a pointer to an array of strings argv and an array of string tokens
// allocates space in argv for the tokens and copies them over
// returns -1 on a failure
int create_argv(char ***argv, char **tokens){
    size_t argv_size = DEF_ARRSIZE;
    int n = 0;
    char *tok = *(tokens + n);
    if((*argv = (char **) malloc(sizeof(char *) * argv_size)) == NULL)
        return -1;
    while(tok != NULL
        && strcmp(tok, "&") != 0
        && strcmp(tok, "<") != 0
        && strcmp(tok, ">") != 0
        && strcmp(tok, ">>") != 0
        && strcmp(tok, "|") != 0){
        if(n == argv_size){
            argv_size += 2; // add two more so there is space for NULL at end
            if((*argv = (char **) realloc(*argv, sizeof(char *) * argv_size)) == NULL)
                return -1;
        }
        if((*(*argv + n) = (char *) malloc(sizeof(tok))) == NULL)
            return -1;
        memcpy(*(*argv + n++), tok, sizeof(*tok));
        tok = *(tokens + n);
    }
    *(*argv + (n + 1)) = NULL; // terminate argv
    return n;
}
