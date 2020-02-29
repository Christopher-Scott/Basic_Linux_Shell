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

    // // reset any previous state
    // the_queue->background = 0;

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
    cmd_node *cmd;
    if((cmd = init_cmd()) == NULL){
        fprintf(stderr, "%s\n", "Error: Mem alloc in parse");
        exit(1);
    }
    cmd_node *head = cmd; // save the head of the list
    cmd->argv = NULL;
    int toks_read;
    // char *tok_arr[20];
    // enqueue(the_queue, cmd);
    while(*tok_arr != NULL){
        // strcpy(*tok_arr, *tok_arr); // save the next keyword and advance to next tok
        if(strcmp(*tok_arr, "&") == 0){
            tok_arr++;
            head->background = 1;
            enqueue(the_queue, head); // if background operator is seen it is the last cmd in chain
            if((cmd = init_cmd()) == NULL){
                fprintf(stderr, "%s\n", "Error: Mem alloc in parse");
                exit(1);
            }
            head = cmd;
        } else if(strcmp(*tok_arr, "<") == 0){
            tok_arr++;
            cmd->input = strdup(*tok_arr++);
            // cmd->input = *tok_arr++;
        }else if(strcmp(*tok_arr, ">>") == 0){
            tok_arr++;
            cmd->append = strdup(*tok_arr++);
            // cmd->append = *tok_arr++;
        }else if(strcmp(*tok_arr, ">") == 0){
            tok_arr++;
            cmd->output = strdup(*tok_arr++);
            // cmd->output = *tok_arr++;
        }else if(strcmp(*tok_arr, "|") == 0){
            tok_arr++;
            cmd->pipe = init_cmd();
            cmd = cmd->pipe; // move to next in chain
            toks_read = create_argv(&cmd->argv, tok_arr);
            tok_arr += toks_read;
            cmd->cmd = cmd->argv[0];
            n_cmds++;
        }
        else{ // next token is a command
            toks_read = create_argv(&cmd->argv, tok_arr);
            tok_arr += toks_read;
            cmd->cmd = cmd->argv[0];
            n_cmds++;
        }


    }
    enqueue(the_queue, head);
    // clean up the token array
    i = 0;
    for(; *(tok_arr_cpy + i) != NULL; i++)
        free(*(tok_arr_cpy + i));
    // free(*(tok_arr_cpy + i)); // free last pointer
    free(tok_arr_cpy); // free array pointer
    return n_cmds;
}
