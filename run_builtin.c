#include "c_shell.h"

int run_builtin(const cmd_node * cmd, const int index){
    switch(index){
        case CD:
            // printf("Running %s\n", cmd->cmd);
            cd(cmd->argv[1]); // cd expects 1 arg, ok if NULL
            break;
        case DIR:
            printf("Running %s\n", cmd->cmd);
            break;
        case ENVIRON:
            printf("Running %s\n", cmd->cmd);
            break;
        case CLR:
            printf("Running %s\n", cmd->cmd);
            break;
        case ECHO:
            // printf("Running %s\n", cmd->cmd);
            echo((cmd->argv + 1));
            break;
        case HELP:
            printf("Running %s\n", cmd->cmd);
            break;
        case PAUSE:
            printf("Running %s\n", cmd->cmd);
            break;
        case EXIT:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Running %s\n", cmd->cmd);
            break;
    }
    return 0;
}
