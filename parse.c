#include "c_shell.h"
#include <string.h>

// tokenize a string and place the tokens in a NULL terminated array
int parse(char **args, size_t size, char *input){
    char * delim = " ";
    char *tok;
    unsigned int ret = 0;
    int i = 0;
    tok = strtok(input, delim);
    for(;tok != NULL && i < size; i++){
        if(strcmp(tok, "<"))
            ret | IN_REDIR;
        else if(strcmp(tok, ">"))
            ret | OUT_REDIR;
        else if(strcmp(tok, ">>"))
            ret | OUT_APPEN;
        else if(strcmp(tok, "|"))
            ret | PIPING;
        tok = strtok(NULL, delim);
        memcpy(*args++, tok, strlen(tok));
    }
    if( i >= size) {
        //TODO: handle error
        printf("%s", "Command string exceeds args size");
    }

}

