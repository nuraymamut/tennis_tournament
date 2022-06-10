#include "arbore.h"

nodeT *newNode(data1 val)
{
    nodeT* node=(nodeT*)malloc(sizeof(nodeT));
    node->val=val;
    node->left=node->right=NULL;
    return node;
}

nodeT *insert(nodeT *node,data1 key)
{
     if(node==NULL) return newNode(key);

     if(key.score<node->val.score) node->left=insert(node->left,key);
     if(key.score>node->val.score) node->right=insert(node->right,key);
     if(key.score==node->val.score)
        {
              
            if(strcmp(key.last_name,node->val.last_name)<0)

                node->val=key;//daca numele jucatorului pe care il adaug
                             // e mai mic decat numele stocat in nod
                             // nodul stocheaza jucatorul in locul celui initial

            if(strcmp(key.last_name,node->val.last_name)==0)
               if(strcmp(key.first_name,node->val.first_name)<0)
                  node->val=key;
                
        }

     return node;
}

void DRS(nodeT *root,FILE *F)
{
    if(root){
               DRS(root->right,F);
               fprintf(F,"%s %s %d\n",root->val.last_name,root->val.first_name,root->val.score);
               DRS(root->left,F);
            }
}

nodeT *search(nodeT *root,data1 key)
{
    if(root==NULL||strcmp(root->val.last_name,key.last_name)==0) return root;
    if(root->val.score<key.score) return search(root->right,key);
    
    return search(root->left,key);
}

void deleteTree(nodeT *root)
{
    if(root==NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}