// Main Shell loop
#include "c_shell.h"

int main(int argc, char **argv){
    queue *cmd_queue = init_queue();
    cmd_node *current, *cmd;
    char *prompt = "> ";
    char *line = NULL;
    size_t n = 0;
    ssize_t chars_read = 0;
    int builtin_index;
    pid_t pid;
    int status;

    char *path_list[] = {"/bin/", "/usr/bin/", NULL};

    if(argc > 2){
        fprintf(stderr, "%s\n", "Usage: myshell or myshell <batch file>");
        return EXIT_FAILURE;
    }
    else if(argc == 2){
        fprintf(stdout, "%s\n", "Running in batch mode");
        return EXIT_SUCCESS;
    }
    printf("%s", prompt);
    while((chars_read = getline(&line, &n, stdin)) > 0){
        *(line + (chars_read - 1)) = '\0';  // get rid of newline character
        parse(line, cmd_queue);
        while((current = dequeue(cmd_queue)) != NULL){
            if(current->input != NULL){ // Setup input redirection
                printf("Setting input redirect to: %s\n", current->input);
            }
            if(current->output != NULL && current->append != NULL){ // can't have both
                printf("Redirection Error\n");
            }
            else if(current->output != NULL){ // Setup output redirection
                printf("Setting output redirect to: %s\n", current->output);
            }
            else if(current->append != NULL){ // setup append output redirection
                printf("Setting append redirect to: %s\n", current->append);
            }
            if(current->pipe == NULL){ // No piping
                if((builtin_index = is_builtin(current->cmd)) >= 0){
                    run_builtin(current, builtin_index);
                }
                else{
                    // buildpath(path_list, current);
                    // printf("Executing: %s\n", current->cmd);
                    if((pid = fork()) < 0){
                        fprintf(stderr, "%s\n", strerror(errno));
                    }
                    if(pid == 0){ // child, constuct full path and exec cmd
                        buildpath(path_list, current);
                        // printf("Executing: %s\n", current->cmd);
                        execv(current->cmd, current->argv);
                    }
                    else {
                        if(!cmd_queue->background){
                            // printf("Running in the background\n");
                            wait(&status);
                        }

                    }
                    // if(cmd_queue->background){
                    //     printf("Running in the background\n");
                    // }
                }
            }
            else{ // Piping
                cmd = current;
                // int read = STDIN_FILENO;
                while(cmd != NULL){
                    for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
                        printf("%s ", cmd->argv[i]);
                    puts("");

                    cmd = cmd->pipe;
                }
                if(cmd_queue->background){
                    printf("Running in the background\n");
                }
            }
        }
    printf("%s", prompt);
    }

    return EXIT_SUCCESS;
}
