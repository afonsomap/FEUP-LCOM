#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUESIZE 64

#include <lcom/lcf.h>


struct queue_imp;
typedef struct queue_imp Queue;

Queue* createQueue();
int queueSize(Queue *queue);
bool push(Queue* queue, uint8_t element);
uint8_t pop(Queue* queue);
uint8_t front(Queue* queue);
uint8_t back(Queue* queue);
bool isEmpty(Queue* queue);
bool isFull(Queue* queue);
void destroyQueue(Queue* queue);

#endif
