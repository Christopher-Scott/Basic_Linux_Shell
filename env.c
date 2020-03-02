// Print the value of the specified environment variables
// or the list of environment variables
#include "c_shell.h"

int env(char *var){
    extern char **environ;
    char *env_var;
    if(var != NULL){ // print environment variable 
        if((env_var = getenv(var)) != NULL){
            printf("%s\n", env_var);
        }
        else{
            fprintf(stderr, "Error: Environment variable %s not found", var);
            return EXIT_FAILURE;
        }
    }
    else{ // print all the environment variables
        for(int i = 0; environ[i] != NULL; i++){
            printf("%s\n", environ[i]);
        }
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
