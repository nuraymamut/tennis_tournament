#include "struct.h"
#include "lista.h"
#include "stiva.h"
#include "coada.h"
#include "arbore.h"

void readFile(Country *t,FILE *file);
int nr_final(int n);
int media(Country t);
void switchVal(float *v,data *t,int n);
int max(data d);
void emptyS(data *a,data *b,stackNode **stackTop,FILE *F);
void addQ(data a,data b,queue **q);
void emptyQ(queue **q,FILE *F);
void addS(int loc1,int loc2,data a,data b,stackNode **aux);
void winner(stackNode *WINNER,stackNode *stackTop,int n,int p,data **v,FILE *F);
void readg(data1 *j,FILE *g);
int countN(nodeT* root,data1 x,data1 y);