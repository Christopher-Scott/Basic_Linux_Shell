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
    char **tok_arr;
    int i = 0;
    int n_cmds = 0;
    size_t tok_size = DEF_TOKENS;

    // Tokenize
    if((tok_arr = (char **)malloc(sizeof(char*) * tok_size)) == NULL)
        return -1;
    tok = strtok(cmd_string, delim);
    tok_arr[i] = (char *) malloc(sizeof(tok))
    memcpy(tok_arr[i++], tok , sizeof(tok));
    while((tok = strtok(NULL,delim)) != NULL){
        tok_arr[i] = (char*) malloc(sizeof(tok))
        memcpy(tok_arr[i++], tok, sizeof(*tok));
        if( i >= tok_size){
            tok_size = (int) tok_size * 1.5; // set up new array size
            tok_arr = (char *) realloc(tok_arr, sizeof(char *) * tok_size);
        }
        i++;
    }
    if(i == tok_size){ // somehow ended with precisely the array size
        tok_arr = (char *) realloc(tok_arr, sizeof(char *) * tok_size + 1);
    }
    tok_arr[i] = NULL; // NULL terminate tok_arr
    // enqueue copies data into its own allocated memory so first is local variable
    cmd_node first;
    cmd_node *cmd = &first;
    n_cmds++;
    cmd->argv = NULL;
    int toks_read;
    char *kword;
    enqueue(the_queue, cmd);
    while(*tok_arr != NULL){
        toks_read = create_argv(&cmd->argv, tok_arr);
        tok_arr += toks_read;
        cmd->cmd = argv[0];
        kword = *tok_arr++; // save the next keyword and advance to next tok
        if(strcmp(kword, "&") == 0){
            the_queue->background = 1;
            enqueue(the_queue, cmd) // if background operator is seen it is the last cmd in chain
            if((cmd = (cmd_node *) malloc(sizeof(cmd_node) == NULL){
                fprintf(stderr, "%s\n", "Error: Mem alloc issue in parse");
                exit(1);
            }

        } else if(strcmp(kword, "<") == 0){
            // memcpy(*tok_arr++, cmd->input);
            cmd->input = *tok_arr++;
        } else if(strcmp(kword, ">") == 0){
            // memcpy(*tok_arr++, cmd->output);
            cmd->output = *tok_arr++;
        }else if(strcmp(kword, ">>") == 0){
            // memcpy(*tok_arr++, cmd->append);
            cmd->append = *tok_arr++;
        }else if(strcmp(kword, "|") == 0){
            cmd->pipe = (cmd *) malloc(sizeof(cmd_node));
            cmd = cmd->pipe; // move to next in chain
            toks_read = create_argv(&cmd->argv, tok_arr);
            tok_arr += toks_read
            cmd->cmd = argv[0];
            n_cmds++;
        }

    }
    return n_cmds;
}
