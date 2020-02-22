#include "c_shell.h"
// dequeues the head element of the queue.  Returns the element
cmd_node * dequeue(queue * const the_queue) {
    if(the_queue->size == 0){
        return NULL;
    }
    node * temp = the_queue->head;
    the_queue->head = the_queue->head->next;
    the_queue->size--;
    return temp->datum;
}
