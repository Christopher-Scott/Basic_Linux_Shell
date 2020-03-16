// Add an element to the queue.  The user has responsibility to allocate
// memory for the datum
#include "c_shell.h"
int enqueue(queue * const the_queue, cmd_node * const datum) {
    node * new_node = NULL;
    if((new_node = (node * ) malloc(sizeof(node))) == NULL)
        return 0; // alloc error
    else{
        new_node->datum = datum; // copy the pointer
        new_node->next = NULL;
        if (the_queue->size == 0) { // queue is empty
            the_queue->head = new_node;
            the_queue->tail = new_node;
            the_queue->size++;
        } else {
            the_queue->tail->next = new_node;
            the_queue->tail = new_node;
            the_queue->size++;
        }
    }
    return 1;
}
