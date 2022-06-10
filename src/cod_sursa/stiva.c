#include "stiva.h"

void push(stackNode**top,data v)
{
    stackNode *newnode=(stackNode*)malloc(sizeof(stackNode));

    newnode->val=v;
    newnode->next=*top;
    *top=newnode;

}

int isEmpty(stackNode *top)
{
    return top==NULL;
}

data pop(stackNode **top)
{
    if(isEmpty(*top)) exit(1);

    stackNode *temp=*top;
    data aux=temp->val;

    free(temp);
    return aux;
}

void deleteStack(stackNode**top)
{
     stackNode *temp;
     while(!isEmpty(*top))
     {
         temp=*top;
         *top=(*top)->next;
         free(temp);
     }
}
