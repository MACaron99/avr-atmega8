#include <stdint.h>
#include "queue.h"



void queue_init( Queue *q )
{
    q -> head = 0;
    q -> tail = 0;
    q -> size = 0;
}


int8_t queue_is_empty( Queue *q )
{
    return q -> size == 0;
}


int8_t queue_is_full( Queue *q )
{
    return q -> size == QUEUE_SIZE;
}


int8_t queue_enqueue( Queue *q, uint8_t byte )
{
    if ( queue_is_full(q) )
    {
        return 0;
    }
    q -> data[q -> tail] = byte;
    q -> tail = ( q -> tail + 1 ) % QUEUE_SIZE;
    q -> size++;
    return 1;
}


int8_t queue_dequeue( Queue *q, uint8_t *byte )
{
    if ( queue_is_empty(q) )
    {
        return 0;
    }
    *byte = q -> data[q -> head];
    q -> head = (q -> head + 1) % QUEUE_SIZE;
    q -> size--;
    return 1;
}
