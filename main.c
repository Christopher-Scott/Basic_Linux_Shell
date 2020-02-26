// Main Shell loop
#include "c_shell.h"

int main(int argc, char **argv){
    queue *cmd_queue = init_queue();
    cmd_node *current, *cmd;
    char *prompt = ">";
    char *line = NULL;
    size_t n = 0;
    ssize_t chars_read = 0;

    if(argc > 2){
        fprintf(stderr, "%s\n", "Usage: myshell or myshell <batch file>");
        return EXIT_FAILURE;
    }
    else if(argc == 2){
        fprintf(stdout, "%s\n", "Running in batch mode");
        return EXIT_SUCCESS;
    }
    printf("%s", prompt);
    while((chars_read = getline(&line, &n, stdin)) != 0){
        parse(line, cmd_queue);
        while((current = dequeue(cmd_queue)) != NULL){
            if(current->input != NULL){
                printf("Setting input redirect to: %s\n", current->input);
            }
            if(current->output != NULL && current->append != NULL){
                printf("Redirection Error\n");
            }
            else if(current->output != NULL){
                printf("Setting output redirect to: %s\n", current->output);
            }
            else if(current->append != NULL){
                printf("Setting append redirect to: %s\n", current->append);
            }
            if(current->pipe == NULL){
                for(int i = 0; current->argv[i] != NULL; i++) //print arg array
                    printf("%s ", current->argv[i]);
                puts("");
                if(cmd_queue->background){
                    printf("Running in the background\n");
                }
            }
            else{
                cmd = current;
                while(cmd != NULL){
                    for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
                        printf("%s ", cmd->argv[i]);
                    puts("");
                    // printf("Piping to: \n");
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
