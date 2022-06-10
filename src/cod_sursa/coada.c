#include "coada.h"

queue* create_queue()
{
    queue *q;
    q=(queue*)malloc(sizeof(queue));

    q->front=q->rear=NULL;

    return q;
}

void enQueue(queue *q,data1 v)
{
    Node* newnode=(Node*)malloc(sizeof(Node));
    newnode->val=v;
    newnode->next=NULL;

    if(q->rear==NULL)
       q->rear=newnode;
      else{
             q->rear->next=newnode;
             q->rear=newnode;
          }

    if(q->front==NULL)
       q->front=q->rear;
}

int isEmptyQ(queue *q)
{
    return (q->front==NULL);
}

data1 deQueue(queue *q)
{
    Node* aux;
    data1 d;

    if(isEmptyQ(q)) exit(1);

    aux=q->front;
    d=aux->val;
    q->front=q->front->next;
    free(aux);
    return d;
}

void deleteQueue(queue *q)
{
    Node *aux;
    while(!isEmptyQ(q))
         {
             aux=q->front;
             q->front=q->front->next;
             free(aux);
         }
    free(q);     
}