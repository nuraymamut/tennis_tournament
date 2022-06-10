#include "stiva.h"
#include "struct.h"
#include "lista.h"
#include "coada.h"
#include "functii.h"
#include "arbore.h"


int main(int argc,char* argv[])
{
    FILE *file,*g,*F;
    node *head,*z,*temp;
    int n,i,k,l=0,*u;
    float *v;
    char c[10],num[10],pr[10];
    Country *t,*w;
    stackNode *WINNER=NULL,*stackTop=NULL;
    nodeT *root=NULL;

    g=fopen("cerinte.in","r");
    file=fopen("date.in","r");
    F=fopen("rezultate.out","w");

    u=(int*)malloc(sizeof(int)*5);

    for(i=0; i<5; i++)
        fscanf(g,"%d",&u[i]);


    z=(node*)malloc(sizeof(node));//creez nodul santinela
    head=z;
    z->next=z->prev=z;

    fscanf(file,"%d",&n);

    t=(Country*)malloc(sizeof(Country)*n);//aloc memorie prntru structurile Country

    for(i=0; i<n; i++) //citesc valorile din fisier
    {
        readFile(&t[i],file);
        create_list(z,t[i]);//creez lista cu santinela
    }

    fclose(file);

    if(u[1]==0)//verific cate cerinte trebuie facute
    {
        print(z,F);
        exit(1);
    }


    //2.
    int f=nr_final(n);//retin numarul final de tari

    v=(float*)malloc(sizeof(float)*n);//aloc memorie pentru un vector in care o sa se retina
    //media scorurilor jucatorilor din fiecare tara

    for(i=0; i<n; i++)
    {
        v[l]=media(t[i]);
        l++;
    }

    switchVal(v,t,n);//ordonez vectorul descrescator si in acelasi timp schimb si ordinea
    //lui t structurile

    for(i=f; i<n; i++) //cu vectorul t ordonat in functie de medii pornesc de la numarul final
                       //pana la numarul initial pentru a gasi tarile care trebuie sterse din lista
    {
        deleteNode(z,t[i].name);
    }

    print(z,F);

    n=f;

    temp=z->next;
    while(temp!=z)//adaug tarile in stiva
    {
        push(&stackTop,temp->val);
        temp=temp->next;
    }

    deleteList(&z);//se sterge lista

    if(u[2]==0) exit(1);


    //3.
    w=(data*)malloc(sizeof(data)*4);//aloc memorie pentru vectorul in care o sa retin ultimele 4
    //tari din turneu
    winner(WINNER,stackTop,n,1,&w,F);

    if(isEmpty(stackTop))//se stabileste stiva care nu este goala
    {
        deleteStack(&stackTop);//se sterge stiva daca nu este goala
        WINNER=NULL;
        free(WINNER);//se elibereaza memorie pentru stiva goala
    }
    else
    {
        deleteStack(&WINNER);
        stackTop=NULL;
        free(stackTop);
    }

    if(u[3]==0) exit(1);


    //4.
    for(i=0; i<4; i++)
        for(k=0; k<t[i].nr_players; k++)
            root=insert(root,w[i].players[k]);//creez un BST in care adaug jucatorii din ultimele 4 tari

    fprintf(F,"\n====== CLASAMENT ======\n");
    DRS(root,F);//afisez jucatorii in ordine descrescatoare in functie de scor

    if(u[4]==0) exit(1);


    //5.
    data1 j1,j2;

    //citesc valorile din fisier
    readg(&j1,g);
    readg(&j2,g);

    fclose(g);

    if(search(root,j1)!=NULL && search(root,j2)!=NULL)//verific daca cei doi jucatori se afla in arbore
    {
        if(j1.score<j2.score)//aflu care este scorul mai mare
            fprintf(F,"\n%d\n",countN(root,j1,j2));
        if(j1.score>j2.score)
            fprintf(F,"\n%d\n",countN(root,j2,j1));
    }
    else if(search(root,j1)==NULL)
        fprintf(F,"\n%s %s nu poate fi identificat\n",j1.last_name,j1.first_name);
    else fprintf(F,"\n%s %s nu poate fi identificat\n",j2.last_name,j2.first_name);


    deleteTree(root);//parcurg arborele in postordine si eliberez memoria fiecarui nod pe rand
    root=NULL;

    fclose(F);


}




