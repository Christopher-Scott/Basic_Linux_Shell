// concatenate the present working directory name with the target filename
#include "c_shell.h"
char *fullpath(char *dest, const char * pwd, const char *filename, size_t n){
    size_t i = 0;
    for(; *(pwd + i) != '\0' && i < n; i++){
        *(dest + i) = *(pwd + i);
    }
    if(i < n){
        *(dest + i++) = '/';
    }
    for(size_t j = 0; *(filename + j) != '\0' && i < n; j++, i++){
        *(dest + i) = *(filename + j);
    }
    *(dest + i) = '\0';
    return dest;
}
