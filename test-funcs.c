#include "c_shell.h"
#include <assert.h>

int main(){
    // Test create_argv
    char **argv = NULL;
    char *toks[]  = {"echo", "Hi", "I", "am", "a", "long", "command", NULL};
    // printf("argv at: %p\n", argv); // should be null
    int n = create_argv(&argv, toks);
    // printf("%d toks copied to argv at: %p\n", n, argv);
    assert(n == 7);
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

    // Test fullpath
    char buffer[256];
    char *pwd = "/home";
    char *filename = "test.txt";
    fullpath(buffer, pwd, filename, 256);
    assert(strcmp(buffer, "/home/test.txt") == 0);

    puts("'fullpath' pass");

    // Test parse
    char cmd_string[100] = "echo Hello, World | grep [A-Z] | cat > output.txt & ls -l | grep m";
    queue *cmd_queue = init_queue();
    n = parse(cmd_string, cmd_queue);
    assert(n == 5);
    print_queue(cmd_queue);
    return 0;
}
