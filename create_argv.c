#include "c_shell.h"
#define DEF_ARRSIZE 3

// create_argv takes a pointer to an array of strings argv and an array of string tokens
// allocates space in argv for the tokens and copies them over
// returns -1 on a failure
int create_argv(char ***argv, char **tokens){
    // size_t argv_size = DEF_ARRSIZE;
    size_t argv_size = 1;
    int n = 0;
    char *tok = *tokens; // get the first token
    size_t size;
    if((*argv = (char **) calloc(argv_size, sizeof(char *) * argv_size)) == NULL)
        return -1;
    while(tok != NULL
        && strcmp(tok, "&") != 0
        && strcmp(tok, "<") != 0
        && strcmp(tok, ">") != 0
        && strcmp(tok, ">>") != 0
        && strcmp(tok, "|") != 0){
        if(n == argv_size - 1){
            argv_size += 2; // add two more so there is space for NULL at end
            if((*argv = (char **) realloc(*argv, sizeof(char *) * argv_size)) == NULL)
                return -1;
        }
        // duplicate strings
        // allocate space for string
        // if(((*(*argv + n) = (char *) malloc(strlen(tok) + 1))) == NULL)
            // return -1;
        // copy tok
        // memcpy(*(*argv + n++), tok, strlen(tok) + 1);
        size = strlen(tok) + 1;
        (*argv)[n] = (char *) malloc(size);
        memcpy((*argv)[n], tok, size);
        n++;
        tok = *(tokens + n);
    }
    // (*argv)[n + 1] = (char *) malloc(sizeof(NULL)); // terminate argv
    // (*argv)[n + 1] = NULL;
    return n;
}
