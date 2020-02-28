#include "c_shell.h"

int run_builtin(const cmd_node * cmd, const int index){
    switch(index){
        case CD:
        case DIR:
        case ENVIRON:
        case CLR:
        case ECHO:
        case HELP:
        case PAUSE:
        case EXIT:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Running %s\n", cmd->cmd);
            break;
    }
    return 0;
}
