#include "functii.h"

void readFile(Country *t,FILE *file)
{
    char c[20],num[20],pr[20];
    int k;

    fscanf(file,"%d",&t->nr_players);

    t->players=(Player*)malloc(sizeof(Player)*(t->nr_players));//aloc memorie  
                                                            //pentru fiecare jucator
    fscanf(file,"%s",c);//citesc initial numele tarilor intr-o variabila alocata static
    t->name=(char*)malloc(sizeof(strlen(c)+1));
    strcpy(t->name,c);

    t->global_score=0;//initializez scorul global pentru fiecare tara cu 0

    for(k=0;k<t->nr_players;k++)
        {
            fscanf(file,"%s",num);
            t->players[k].last_name=(char*)malloc(sizeof(strlen(num)+1));
            strcpy(t->players[k].last_name,num);

            fscanf(file,"%s",pr);
            t->players[k].first_name=(char*)malloc(sizeof(strlen(pr)+1));
            strcpy(t->players[k].first_name,pr);

            fscanf(file,"%d",&t->players[k].score);

        }

}

int nr_final(int n)
{
    int x=1,aux,j=0;
    double i=0;

    aux=n;
    while(aux!=1)
         {
            if(aux%2!=0) j++;//verific daca n e putere a lui 2
            aux=aux/2;
         }

    while(x<n)
          x=x*2;

    if(j!=0) return x/2;
       else return x;//daca e x o sa fie egal cu n
}

int media(Country t)
{
    int i;
    float media=0;
    for(i=0;i<t.nr_players;i++)
        media=media+t.players[i].score;

    media=media/t.nr_players;

    return media;

}

void switchVal(float *v,data *t,int n)
{
    int i,k;
    float aux;
    data aux2;

    for(i=0;i<n-1;i++)
       for(k=i+1;k<n;k++)
           if(v[i]<v[k])
           {
               aux=v[i];
               v[i]=v[k];
               v[k]=aux;

               aux2=t[i];
               t[i]=t[k];
               t[k]=aux2;
           }  

}

int max(data d)
{
    int i,max=0;

    for(i=0;i<d.nr_players;i++)
        if(d.players[i].score>max) max=d.players[i].score;

    return max;
}

void emptyS(data *a,data *b,stackNode **stackTop,FILE *F)
{
    *a=pop(stackTop);
    *b=pop(&(*stackTop)->next);
    *stackTop=(*stackTop)->next->next;

    fprintf(F,"%s %d ----",a->name,a->global_score);
    fprintf(F," %s %d\n",b->name,b->global_score);

}

void addQ(data a,data b,queue **q)
{
    int k,l;

    for(k=0;k<a.nr_players;k++)//adaug jucatorii care urmeaza sa se confrunte 2 cate 2 in coada
        for(l=0;l<b.nr_players;l++)
            {
                enQueue(*q,a.players[k]);
                enQueue(*q,b.players[l]);
            }
}

void emptyQ(queue **q,FILE *F)
{
    
    data1 o,o1;
   
    o=deQueue(*q);
    o1=deQueue(*q);

    fprintf(F,"%s %s %d vs ",o.last_name,o.first_name,o.score);
    fprintf(F,"%s %s %d\n",o1.last_name,o1.first_name,o1.score);

                
}

void addS(int loc1,int loc2,data a,data b,stackNode **aux)
{

    if(loc1>loc2)  push(*&aux,a);  
    if(loc2>loc1)  push(*&aux,b);
    if(loc1==loc2)
      {
        if(max(a)>max(b)) push(*&aux,a);
        if(max(a)<max(b)) push(*&aux,b);
        if(max(a)==max(b)) push(*&aux,a);
      } 

}

void winner(stackNode *WINNER,stackNode *stackTop,int n,int p,data **v,FILE *F)
{

    data a,b,s;
    int loc1,loc2,i,k,l;
    stackNode *aux;


    if(n!=1)
       {

            fprintf(F,"\n====== ETAPA %d ======\n\n",p);
            for(i=0;i<n/2;i++)
               {
                    loc1=0;//la fiecare etapa se initializez scorurile locale cu 0
                    loc2=0;

                    emptyS(&a,&b,&stackTop,F);//scot 2 tari din stiva

                    queue *q=create_queue();
                    addQ(a,b,&q);
                
                    for(k=0;k<a.nr_players;k++)
                        for(l=0;l<b.nr_players;l++)
                        {
                            emptyQ(&q,F);//scot jucatorii 2 cate 2 din coada si afisez meciul

                            if(a.players[k].score>b.players[l].score)
                                {
                                    loc1=loc1+3;
                                    a.players[k].score=a.players[k].score+5;
                                }

                            if(a.players[k].score<b.players[l].score)
                                {
                                    loc2=loc2+3;
                                    b.players[l].score=b.players[l].score+5;
                                }

                            if(a.players[k].score==b.players[l].score)
                                {
                                    loc2=loc2+1;
                                    b.players[l].score=b.players[l].score+2;

                                    loc1=loc1+1;
                                    a.players[k].score=a.players[k].score+2;
                                }

                        }


                    fprintf(F,"\n");

                    a.global_score=loc1+a.global_score;
                    b.global_score=loc2+b.global_score;

                    addS(loc1,loc2,a,b,&aux);//adaug tara castigatoare intr-o stiva auxiliara
                    
                    deleteQueue(q);
                    q=NULL;
                
                }
            

            fprintf(F,"=== WINNER ===\n");
            for(i=0;i<n/2;i++)
               {
                    s=pop(&aux);//golesc stiva auxiliara pentru a afisa tarile castigatoare
                    fprintf(F,"%s --- %d\n",s.name,s.global_score);

                    if(n/2==4) (*v)[i]=s;//cand raman 4 tari in competitie se retin in v

                    aux=aux->next;
                    push(&WINNER,s);//adaug tarile una cate una in stiva WINNER
                    
               }
             
    

            winner(stackTop,WINNER,n/2,p+1,*&v,F);//stackTop si WINNER se inverseaza
                                                //numarul de tari se injumatateste
                                                //p se incrementeaza pentru a se afisa
                                                //numarul etapei curente
        
            
        }
     
     
}

void readg(data1 *j,FILE *g)
{
    char num[20];

    fscanf(g,"%s",num);
    j->last_name=(char*)malloc(sizeof(strlen(num)+1));
    strcpy(j->last_name,num);
    fscanf(g,"%s",num);
    j->first_name=(char*)malloc(sizeof(strlen(num)+1));
    strcpy(j->first_name,num);
    fscanf(g,"%d",&j->score);
  
}

int countN(nodeT* root,data1 x,data1 y)
{

    if(!root) return 0;

    if(x.score<root->val.score && y.score>root->val.score)
      return 1+countN(root->left,x,y)+countN(root->right,x,y);
    
    if(x.score<root->val.score)
      return countN(root->left,x,y);

    if(y.score>root->val.score)
      return countN(root->right,x,y);


}