#include "c_shell.h"

// Iteratively prints the elements in the queue to stdout
void print_queue(queue *const the_queue){
    node * where = the_queue->head;
    int i = 0;
    while(where->next != NULL){
        printf("%d: %p {%s}\n", i, where, where->datum->cmd);
        where = where->next;
        i++;
    }
    printf("%d: %p {%s}\n", i, where, where->datum->cmd);
}
