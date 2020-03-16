// helper function to allocate space and initialize the member variables of
// a command node
#include "c_shell.h"

cmd_node *init_cmd(void){
    cmd_node *cmd;
    if((cmd = (cmd_node *) malloc(sizeof(cmd_node))) == NULL){
        return NULL;
    }
    cmd->cmd = NULL;
    cmd->argv = NULL;
    cmd->input = NULL;
    cmd->output = NULL;
    cmd->append = NULL;
    cmd->pipe = NULL;
    cmd->background = 0;
    return cmd;
}
