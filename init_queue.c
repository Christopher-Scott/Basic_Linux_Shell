// allocates space for the queue and initializes the struct members
#include "c_shell.h"

queue * init_queue(void){
    queue * the_queue;
    if((the_queue = (queue *) malloc(sizeof(queue))) == NULL)
        return the_queue;
    the_queue->size = 0;
    the_queue->head = NULL;
    the_queue->tail = NULL;
    return the_queue;
}
