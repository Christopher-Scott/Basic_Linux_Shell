#include "c_shell.h"

int run_builtin(const cmd_node * cmd, const int index){
    switch(index){
        case CD:
            cd(cmd->argv[1]); // cd expects 1 arg, ok if NULL
            break;
        case B_DIR:
            dir(cmd->argv[1]); // dir expects 1 arg, ok if NULL
            break;
        case ENV:
            env(cmd->argv[1]);
            break;
        case CLR:
            clr();
            break;
        case ECHO:
            echo((cmd->argv + 1));
            break;
        case HELP:
            help();
            break;
        case PAUSE:
            c_pause();
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
