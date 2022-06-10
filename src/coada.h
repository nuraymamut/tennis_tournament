#ifndef COADA_H_
#define COADA_H_
#include "struct.h"

typedef struct elem_q{
                         data1 val;
                         struct elem_q *next;
                     }Node;

typedef struct Q{
                     Node *front,*rear;
                }queue;

queue* create_queue();
void enQueue(queue *q,data1 v);
int isEmptyQ(queue *q);
data1 deQueue(queue *q);
void deleteQueue(queue *q);
#endif