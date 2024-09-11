#include<stdio.h>
#include<stdlib.h>

typedef struct avl {
    int val;
    int height;
    struct avl *left, *right;
} node;

node *createnode(int n){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->val = n;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

int max(int a, int b){
    if( a > b) return a;
    return b;
}

int height(node *root){
    if(root==NULL) return 0;
    return root->height;
}

int isbalance(node *root){
    if(root == NULL) return 1;
    int lh = (root->left!=NULL) ? root->left->height : 0;
    int rh = (root->right!=NULL) ? root->right->height : 0;

    int bf = lh - rh;
    return (bf <=1 && bf >= -1);
}

node *rightrotate(node *root){
    node *x = root->left;
    node *y = x->right;
    root->left = y;
    x->right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

node *leftrotate(node *root){
    node *x = root->right;
    node *y = x->left;
    root->right = y;
    x->left = root;

    root->height =  max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

node *insert(node *root, int n){
    if(root == NULL) return createnode(n);

    if(n < root->val){
        root->left = insert(root->left, n);

        if(!isbalance(root)){
            if(n < root->left->val){
                return rightrotate(root);
            }
            else {
                root->left = leftrotate(root->left);
                return rightrotate(root);
            }
        }
    }
    else {
        root->right = insert(root->right, n);

        if(!isbalance(root)){
            if(n > root->right->val){
                return leftrotate(root);
            }
            else {
                root->right = rightrotate(root->right);
                return leftrotate(root);
            }
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    return root;
}

void in(node *root, int *max, int *smax){
    if(root == NULL){
        return;
    }
    in(root->left, max, smax);
    
    if(root->left == NULL && root->right == NULL){
        if(root->val > *max){
            *smax = *max;
            *max = root->val;
        } else if(root->val > *smax && root->val < *max){
            *smax = root->val;
        }
    }

    in(root->right, max, smax);
}


void secmax(node *root){
    if(root == NULL) {
        printf("-1\n");
        return;
    }
    int smax = -1;
    int max = root->val;
    in(root, &max, &smax);
    printf("%d\n", smax);
}

void post(node *root){
    if(root == NULL) return;
    post(root->left);
    post(root->right);
    printf("%d ", root->val);
}


int main(){
    node *root = NULL;
    char op;
    int n;

    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &n);
            root = insert(root, n);
        }
        else if(op == 'p'){
            post(root);
            printf("\n");
        }
        else if ( op == 's'){
            secmax(root);
        }
        else if(op == 'e'){
            break;
        }
    }

    return 0;
}