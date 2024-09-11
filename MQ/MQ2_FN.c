#include<stdio.h>
#include<stdlib.h>

typedef struct avl{
    int val;
    int height;
    struct avl *left, *right;
} node;

node *createnode(int n){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    newnode->val = n;
    return newnode;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(node *root){
    return (root == NULL) ? 0 : root->height;
}

int isbalance(node *root){
    if(root == NULL) return 1;

    int leftheight = (root->left) ? root->left->height : 0;
    int rightheight = (root->right) ? root->right->height : 0;

    int balfact = leftheight - rightheight;
    return (-1 <= balfact && balfact <= 1);
}

node *rightrotate(node *root){
    node *x = root->left;
    node *y = x->right;
    root->left = y;
    x->right = root;

    root->height = 1 + max(height(root->left), height(root->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

node *leftrotate(node *root){
    node *x = root->right;
    node *y = x->left;
    root->right = y;
    x->left = root;

    root->height = 1 + max(height(root->left), height(root->right));
    x->height = 1 + max(height(x->left), height(x->right));
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

void post(node *root){
    if(root == NULL) return;
    post(root->left);
    post(root->right);
    printf("%d ", root->val);
}

void odd(node *root, int k, int level, int *sum, int *n, int *flag){
    if(root == NULL) return;
    if(level == k){
        *flag = 1;
        if(root->val % 2 == 1){
            *sum += root->val;
            (*n)++;
        }
    }
    odd(root->left, k, level + 1, sum, n, flag);
    odd(root->right, k, level + 1, sum, n, flag);
}

int main(){
    node *V = NULL;
    int num, k, sum = 0, n = 0, flag = 0;
    char op;

    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &num);
            V = insert(V, num);
        }
        else if(op == 'a'){
            scanf("%d", &k);
            odd(V, k, 0, &sum, &n, &flag);
            if(flag == 0){
                printf("-1.0\n");
            }
            else if(n == 0){
                printf("0.0\n");
            }
            else {
                printf("%.1f\n", (float)sum / n);
            }
            sum = 0;
            n = 0;
            flag = 0;
        }
        else if(op == 'p'){
            post(V);
            printf("\n");
        }
        else if(op == 'e'){
            break;
        }
    }
    return 0;
}
