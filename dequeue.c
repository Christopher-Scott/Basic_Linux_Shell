// dequeues the head element of the queue.  Returns the element and frees the
// memory
#include "c_shell.h"
cmd_node * dequeue(queue * const the_queue) {
    cmd_node *retval;
    if(the_queue->size == 0){
        return NULL;
    }
    node * temp = the_queue->head;
    the_queue->head = the_queue->head->next;
    the_queue->size--;
    retval = temp->datum;
    free(temp); // free the head queue node
    return retval;
}
