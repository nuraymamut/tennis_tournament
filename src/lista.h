#ifndef LISTA_H_
#define LISTA_H_
#include "struct.h"

typedef struct elem{
                       data val;
                       struct elem *next, *prev;
                   }node;

void create_list(node *head,data val);
void print(node *z,FILE *F);
void deleteNode(node *z,char *val);
void deleteList(node **head);
#endif