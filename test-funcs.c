#include "c_shell.h"
#include <assert.h>

int main(){
    // Test create_argv
    char **argv = NULL;
    char *toks[3]  = {"echo", "blahblah", NULL};
    // printf("argv at: %p\n", argv); // should be null
    int n = create_argv(&argv, toks);
    // printf("%d toks copied to argv at: %p\n", n, argv);
    assert(n == 2);
    for(int i = 0; *(argv + i) != NULL; i++){
        assert(strcmp(argv[i], toks[i]) == 0);
    }
    puts("'create_argv' pass");

    // Test is_builtin
    assert(is_builtin("cd") == CD);
    assert(is_builtin("dir") == B_DIR);
    assert(is_builtin("environ") == ENV);
    assert(is_builtin("clr") == CLR);
    assert(is_builtin("echo") == ECHO);
    assert(is_builtin("help") == HELP);
    assert(is_builtin("pause") == PAUSE);
    assert(is_builtin("exit") == EXIT);

    puts("'is_builtin' pass");

    // Test buildpath
    // char *path[] = {"/bin/", "/usr/bin/", NULL};
    // cmd_node cmd;
    // cmd->cmd = "ls";
    // assert(strcmp("/bin/ls", ) == 0)

    // Test parse
    char cmd_string[100] = "echo Hello, World < test.txt | grep [A-Z] | cat > output.txt & echo sup | grep | cat";
    queue *cmd_queue = init_queue();
    n = parse(cmd_string, cmd_queue);
    assert(n == 6);
    print_queue(cmd_queue);
    return 0;
}
