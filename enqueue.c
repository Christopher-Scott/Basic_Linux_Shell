#include "c_shell.h"
// Add an element to the queue
int enqueue(queue * const the_queue, const cmd_node * const datum) {
    node * new_node = NULL;
    if((new_node = (node * ) malloc(sizeof(node))) == NULL)
        return 0; // alloc error
    else{
        if ((new_node->datum = (cmd_node *) malloc(sizeof(cmd_node))) == NULL)
            return 0; // alloc error
        memcpy(new_node->datum, datum, sizeof(cmd_node));
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
