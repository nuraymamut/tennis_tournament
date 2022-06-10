#ifndef STIVA_H_
#define STIVA_H_
#include "struct.h"

typedef struct elem_s{
                        data val;
                        struct elem_s *next;
                     }stackNode;

void push(stackNode**top,data v);
int isEmpty(stackNode *top);
data pop(stackNode **top);
void deleteStack(stackNode**top);
#endif