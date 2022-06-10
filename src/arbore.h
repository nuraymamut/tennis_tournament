#ifndef ARBORE_H_
#define ARBORE_H_
#include "struct.h"

typedef struct N{
                    data1 val;
                    struct N *left,*right;
                }nodeT;

nodeT *newNode(data1 val);
nodeT *insert(nodeT *node,data1 key);
void DRS(nodeT *root,FILE *F);
nodeT *search(nodeT *root,data1 key);
void deleteTree(nodeT *root);
#endif