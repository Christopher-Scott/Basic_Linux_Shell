// Main Shell loop
#include "c_shell.h"

#define READ 0
#define WRITE 1

int main(int argc, char **argv){
    queue *cmd_queue = init_queue();
    cmd_node *current, *cmd;
    char *line = NULL;
    size_t n = 0;
    ssize_t chars_read = 0;
    int builtin_index;
    pid_t pid;
    int status;
    int fd[2], in = 0, out = 1, append = 1, save_in, save_out;

    char pwd[MAX_PATH], buf[MAX_PATH] = {'\0'};
    char *path_list[] = {"/bin/", "/usr/bin/", NULL};

    if(argc > 2){
        fprintf(stderr, "%s\n", "Usage: myshell or myshell <batch file>");
        return EXIT_FAILURE;
    }
    else if(argc == 2){
        fprintf(stdout, "%s\n", "Running in batch mode");
        return EXIT_SUCCESS;
    }
    getcwd(pwd, MAX_PATH);
    strcat(pwd, "/"); // TODO: Better solution than this

// ================ INTERACTIVE LOOP =================
    prompt(pwd);
    while((chars_read = getline(&line, &n, stdin)) > 0){
        if(strcmp(line, "\n") == 0){ // user hit enter only
            prompt(pwd);
            continue;
        }
        *(line + (chars_read - 1)) = '\0';  // get rid of newline character
        parse(line, cmd_queue);
        while((current = dequeue(cmd_queue)) != NULL){

        // -------------- SETUP REDIRECTION -----------------
            if(current->input != NULL){ // Setup input redirection
                strcpy(buf, pwd);
                strcat(buf, current->input); // create full path
                if((in = open(buf, O_RDONLY, S_IRUSR)) == -1){
                    fprintf(stderr, "%s\n", strerror(errno));
                }
                save_in = dup(STDIN_FILENO);
                dup2(in, STDIN_FILENO);
            }
            if(current->output != NULL && current->append != NULL){ // can't have both
                printf("Redirection Error\n");
            }
            else if(current->output != NULL){ // Setup output redirection
                strcpy(buf, pwd);
                strcat(buf, current->output); // create full path
                if((out = open(buf, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1){
                    fprintf(stderr, "%s\n", strerror(errno));
                }
                save_out = dup(STDOUT_FILENO);
                dup2(out, STDOUT_FILENO);
            }
            else if(current->append != NULL){ // setup append output redirection
                strcpy(buf, pwd);
                strcat(buf, current->append); // create full path
                if((out = open(buf, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR)) == -1){
                    fprintf(stderr, "%s\n", strerror(errno));
                }
                save_out = dup(STDOUT_FILENO);
                dup2(out, STDOUT_FILENO);
            }
            // --------------- NO PIPING EXECUTION ------------
            if(current->pipe == NULL){
                if((builtin_index = is_builtin(current->cmd)) >= 0){
                    run_builtin(current, builtin_index);
                }
                else{
                    if((pid = fork()) < 0)
                        fprintf(stderr, "%s\n", strerror(errno));
                    if(pid == 0){ // child, constuct full path and exec cmd
                        if(buildpath(path_list, current)){
                            execv(current->cmd, current->argv);
                            return EXIT_FAILURE; // exec failed
                        }
                        else{
                            fprintf(stderr, "Error: %s could not be found in path\n", current->cmd);
                        }
                    }
                    else { // parent
                        if(!cmd_queue->background){
                            wait(&status);
                        }

                    } // parent
                } // executable
            } // No piping
            // -------------------- PIPING --------------------
            else{
                cmd = current; // current will remain head of the list
                int read = STDIN_FILENO;
                while(cmd->pipe != NULL){
                    // for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
                        // printf("%s ", cmd->argv[i]);
                    // puts("");
                    pipe(fd);
                    if((pid = fork()) == -1){
                        fprintf(stderr, "%s\n", strerror(errno));
                    }else if(pid == 0){ // child
                        close(fd[READ]);
                        if(read != STDIN_FILENO){
                            dup2(read, STDIN_FILENO); // use the existing read
                        }
                        if(fd[WRITE] != STDOUT_FILENO){
                            dup2(fd[WRITE], STDOUT_FILENO); // give write end to child
                        }
                        if((builtin_index = is_builtin(cmd->cmd)) >= 0)
                            run_builtin(cmd, builtin_index);
                        else{
                            if(buildpath(path_list, cmd)){
                                execv(cmd->cmd, cmd->argv);
                                return EXIT_FAILURE; // exec failed and returned
                            }
                            else{
                                fprintf(stderr, "Error: %s could not be found in path\n", cmd->cmd);
                            }
                        }
                    }
                    else{
                        close(fd[WRITE]);
                        read = fd[READ]; // save the read end for next cmd
                        cmd = cmd->pipe;
                    }
                } // piping

                // Set up last command, have to check for output redirect
                if((pid = fork()) == -1){
                    fprintf(stderr, "%s\n", strerror(errno));
                }else if(pid == 0){ // child
                    dup2(read, STDIN_FILENO);
                    if(cmd->output != NULL && cmd->append != NULL){ // can't have both
                        printf("Redirection Error\n");
                    }
                    else if(cmd->output != NULL){ // Setup output redirection
                        strcpy(buf, pwd);
                        strcat(buf, cmd->output); // create full path
                        if((out = open(buf, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1){
                            fprintf(stderr, "%s\n", strerror(errno));
                        }
                        save_out = dup(STDOUT_FILENO);
                        dup2(out, STDOUT_FILENO);
                    }
                    else if(cmd->append != NULL){ // setup append output redirection
                        strcpy(buf, pwd);
                        strcat(buf, cmd->append); // create full path
                        if((out = open(buf, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR)) == -1){
                            fprintf(stderr, "%s\n", strerror(errno));
                        }
                        save_out = dup(STDOUT_FILENO);
                        dup2(out, STDOUT_FILENO);
                    }
                    if((builtin_index = is_builtin(cmd->cmd)) >= 0)
                        run_builtin(cmd, builtin_index);
                    else{
                        if(buildpath(path_list, cmd)){
                            execv(cmd->cmd, cmd->argv);
                            return EXIT_FAILURE; // exec failed and returned
                        }
                        else{
                            fprintf(stderr, "Error: %s could not be found in path\n", cmd->cmd);
                        }
                    }

                }
                else{ // parent
                    if(!cmd_queue->background)
                        wait(&status);
                }

            }
            // ---------------- CLEAN UP ------------------
            if(in != STDIN_FILENO){ // Restore stdin
                dup2(save_in, STDIN_FILENO);
                close(in);
                in = 0;
            }
            if(out != STDOUT_FILENO){ // Restore stdout
                dup2(save_out, STDOUT_FILENO);
                close(out);
                out = 0;
            }
            if(append != STDOUT_FILENO){ // Restore stdout
                dup2(save_out, STDOUT_FILENO);
                close(append);
                append = 0;
            }
            clean_node(current); // clean up allocated mem in current cmd node
            current = NULL;
        }
    prompt(pwd);
    }
// ================ END INTERACTIVE LOOP =================

    return EXIT_SUCCESS;
}
