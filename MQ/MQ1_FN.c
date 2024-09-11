/* Convert the given preorder and inorder traversal to binary tree. Find the leafsum and perform postorder traversal */

#include<stdio.h>
#include<stdlib.h>

typedef struct bt{
    int val;
    struct bt *left, *right;
} node;

node *create(int n){
    node *newNode = (node *)malloc(sizeof(node));

    newNode->val = n;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

node *createTree(int in[], int pre[],int start , int end, int *index){
    
    if(start > end) return NULL;

    node *newNode = create(pre[*index]);
    (*index)++;
    if(start == end) return newNode;

    int pos;
    
    for(int i = start; i <=end; i++){
        if(newNode->val == in[i]){
            pos = i;
            break;
        }
    }
    newNode->left = createTree(in,pre,start,pos-1,index);
    newNode->right = createTree(in, pre, pos+1, end, index);

    return newNode;
}

void leafsum(node *root, int *sum){
    if(root == NULL){
        return ;
    }
    leafsum(root->left, sum);
    if(root->left == NULL && root->right == NULL){
        (*sum) += root->val;
    }
    leafsum(root->right, sum);
}

void postoder(node *root){
    if(root == NULL){
        return;
    }
    postoder(root->left);
    postoder(root->right);
    printf("%d ", root->val);
}

int main(){
    int n;
    scanf("%d", &n);
    int pre[n], in[n];
    int index = 0;
    int sum = 0;

    for(int i = 0; i < n; i++){
        scanf("%d", &pre[i]);
    }

    for(int i = 0; i < n; i++){
        scanf("%d", &in[i]);
    }

    node *head = createTree(in, pre, 0, n-1, &index);

    char op;
    while(1){
        scanf(" %c", &op);
        if(op == 'p'){
            postoder(head);
            printf("\n");
        }
        else if( op == 's'){
            leafsum(head, &sum);
            printf("%d\n", sum);
        }
        else if(op == 'e'){
            break;
        }
    }
    return 0;
}