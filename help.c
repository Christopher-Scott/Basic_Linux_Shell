// display the manual for the shell
#include "c_shell.h"
#define READ 0
#define WRITE 1
#define BUFF_SIZE 1024

int help(void){
    // int fd[2], man;
    int status;
    pid_t pid;
    // if((man = open("manual.txt", O_RDONLY, S_IRUSR)) == -1){
        // fprintf(stderr, "%s\n", strerror(errno));
        // return EXIT_FAILURE;
    // }
    // pipe(fd);
    if((pid = fork()) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if(pid == 0){ // child
        // close(fd[WRITE]);
        // dup2(fd[READ], STDIN_FILENO);
        execlp("less", "less", "manual.txt", NULL);
        return EXIT_FAILURE;
    }
    else{ // parent
        // char buffer[BUFF_SIZE] = {'\0'};
        // ssize_t chars_read;
        // close(fd[READ]);
        // while((chars_read = read(man, buffer, BUFF_SIZE)) > 0){
        //     write(fd[WRITE], buffer, chars_read);
        // }
        // if(chars_read == -1){
        //     fprintf(stderr, "%s\n", strerror(errno));
        //     return EXIT_FAILURE;
        // }
        waitpid(pid, &status, 0);
    }
    return EXIT_SUCCESS;
}
