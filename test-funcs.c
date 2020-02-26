#include "c_shell.h"

int main(){
    // Test create_argv
    char **argv = NULL;
    char *toks[3]  = {"echo", "blahblah", NULL};
    printf("argv at: %p\n", argv); // should be null
    int n = create_argv(&argv, toks);
    printf("%d toks copied to argv at: %p\n", n, argv);
    while(*argv != NULL){
        printf("%s ", *argv++);
    }
    puts("");

    // Test parse
    char cmd_string[100] = "echo Hello, World < test.txt | grep [A-Z] | cat > output.txt & echo sup | grep | cat";
    queue *cmd_queue = init_queue();
    n = parse(cmd_string, cmd_queue);
    printf("parse returned: %d\n", n);
    print_queue(cmd_queue);
    // cmd_node *cmd, *head;
    // while((head = dequeue(cmd_queue)) != NULL){ // iterate queue
    //     cmd = head;
    //     while(cmd != NULL){ // iterate cmd list
    //         puts("");
    //         for(int i = 0; cmd->argv[i] != NULL; i++) //print arg array
    //             printf("%s ", cmd->argv[i]);
    //         printf("\ninput: %s \noutput: %s \nappend: %s\npipe: %p\n",
    //             cmd->input, cmd->output, cmd->append, cmd->pipe);
    //         cmd = cmd->pipe;
    //     }
    // }
    return 0;
}
