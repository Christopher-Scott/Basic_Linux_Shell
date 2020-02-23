#include "c_shell.h"
#define DEF_TOKENS 20

// Command string is tokenized, then tokens are traversed
// Queue is essentially a 2 dimensional linked List
// Each element(inner list) will be a chain of nodes representing commands that pipe to one another
// Different elements for parallel commands ie. cmd1 & cmd2 & cmd3
// For most commands, queue will likely contain only 1 element
int parse(char *cmd_string, queue *the_queue){
    char *delim = " ";
    char *tok, *temp;
    char **tok_arr, **tok_arr_cpy;
    int i = 0;
    int n_cmds = 0;
    int tok_size = DEF_TOKENS;
    size_t size;

    // Tokenize
    if((tok_arr = (char **)malloc(sizeof(char*) * tok_size)) == NULL)
        return -1;
    tok = strtok(cmd_string, delim);
    // *(tok_arr + i) = strdup(tok);
    size = strlen(tok) + 1;
    tok_arr[i] = (char *)malloc(size);
    memcpy(tok_arr[i], tok, size);
    i++;
    while((tok = strtok(NULL,delim)) != NULL){
        // *(tok_arr + i) = strdup(tok);
        size = strlen(tok) + 1;
        tok_arr[i] = (char *)malloc(size);
        memcpy(tok_arr[i], tok, size);
        if( i >= tok_size){
            tok_size = (int) tok_size * 1.5; // set up new array size
            tok_arr = (char **) realloc(tok_arr, sizeof(char *) * tok_size);
        }
        i++;
    }
    if(i == tok_size){ // somehow ended with precisely the array size
        tok_arr = (char **) realloc(tok_arr, sizeof(char *) * tok_size + 1);
    }
    tok_arr[i] = NULL; // NULL terminate tok_arr
    tok_arr_cpy = tok_arr;
    // enqueue assumes space has already been allocated
    cmd_node *cmd = (cmd_node *) malloc(sizeof(cmd_node));
    n_cmds++;
    cmd->argv = NULL;
    int toks_read;
    char kword[20];
    enqueue(the_queue, cmd);
    while(*tok_arr != NULL){
        toks_read = create_argv(&cmd->argv, tok_arr);
        tok_arr += toks_read;
        cmd->cmd = cmd->argv[0];
        if(*tok_arr != NULL){
            strcpy(kword, *tok_arr++); // save the next keyword and advance to next tok
            if(strcmp(kword, "&") == 0){
                the_queue->background = 1;
                enqueue(the_queue, cmd); // if background operator is seen it is the last cmd in chain
                if((cmd = (cmd_node *) malloc(sizeof(cmd_node))) == NULL){
                    fprintf(stderr, "%s\n", "Error: Mem alloc issue in parse");
                    exit(1);
                }

            } else if(strcmp(kword, "<") == 0){
                cmd->input = strdup(*tok_arr++);
                // cmd->input = *tok_arr++;
            } else if(strcmp(kword, ">") == 0){
                cmd->output = strdup(*tok_arr++);
                // cmd->output = *tok_arr++;
            }else if(strcmp(kword, ">>") == 0){
                cmd->append = strdup(*tok_arr++);
                // cmd->append = *tok_arr++;
            }else if(strcmp(kword, "|") == 0){
                cmd->pipe = (cmd_node *) malloc(sizeof(cmd_node));
                cmd = cmd->pipe; // move to next in chain
                toks_read = create_argv(&cmd->argv, tok_arr);
                tok_arr += toks_read;
                cmd->cmd = cmd->argv[0];
                n_cmds++;
            }
        }

    }
    // clean up the token array
    i = 0;
    for(; *(tok_arr_cpy + i) != NULL; i++)
        free(*(tok_arr_cpy + i));
    free(*(tok_arr_cpy + i)); // free last pointer
    free(tok_arr_cpy); // free array pointer
    return n_cmds;
}
