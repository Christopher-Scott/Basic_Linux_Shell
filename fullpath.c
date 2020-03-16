// concatenate the present working directory name with the target filename
// dest is a buffer string of size n, large enough to hold the concatenated string
#include "c_shell.h"
char *fullpath(char *dest, const char * pwd, const char *filename, size_t n){
    size_t i = 0;
    // copy pwd to dest
    for(; *(pwd + i) != '\0' && i < n; i++){
        *(dest + i) = *(pwd + i);
    }
    if(i < n)
        *(dest + i++) = '/'; // add a forward slash

    // copyt filename to dest
    for(size_t j = 0; *(filename + j) != '\0' && i < n; j++, i++){
        *(dest + i) = *(filename + j);
    }
    *(dest + i) = '\0';
    return dest;
}
