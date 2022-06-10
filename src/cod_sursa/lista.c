#include "lista.h"

void create_list(node *head,data val)
{

    node *newnode=(node*)malloc(sizeof(node));

    newnode->val=val;

    node *last=head->prev;

    newnode->next=head;
    head->prev=newnode;
    newnode->prev=last;
    last->next=newnode;

}

void print(node *z,FILE *F)
{
    node *temp=z;

    temp=temp->next;
    while(temp!=z)
         {
             fprintf(F,"%s\n",temp->val.name);
             temp=temp->next;
         }

}

void deleteNode(node *z,char *val)
{
    node *headcopy=z->next;

    while(headcopy!=z)
         {
             if(strcmp(headcopy->val.name,val)==0)
               {
                   headcopy->prev->next=headcopy->next;
                   headcopy->next->prev=headcopy->prev;
                   free(headcopy);
                   return;
               }
               else headcopy=headcopy->next;
         }
         
}

void deleteList(node **head)
{
    node *headcopy=(*head)->next,*aux;
    while(*head!=headcopy)
          {
             aux=headcopy;
             headcopy=headcopy->next;
             free(aux);
          }
    free(*head);
    *head=NULL;      
}
