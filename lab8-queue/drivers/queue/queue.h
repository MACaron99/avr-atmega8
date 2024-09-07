
#ifndef QUEUE_H
#define QUEUE_H



#define QUEUE_SIZE 16


typedef struct
{
    uint8_t data[QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}
Queue;


void queue_init(Queue *q);
int8_t queue_is_empty(Queue *q);
int8_t queue_is_full(Queue *q);
int8_t queue_enqueue(Queue *q, uint8_t byte);
int8_t queue_dequeue(Queue *q, uint8_t *byte);

#endif // QUEUE_H
