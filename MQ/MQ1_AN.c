/* Convert given preorder and inorder traversal to a binary tree. Check whether the given nodes are cousins. Perform postorder traversal. */


#include<stdio.h>
#include<stdlib.h>

typedef struct bt {
    int val;
    struct bt *left, *right;
} node;

node *create(int n){
    node *newNode = (node *)malloc(sizeof(node));

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = n;
    return newNode;
}


node *createTree(int in[], int pre[], int st, int en, int *pos){
    int index;

    if(st > en) return NULL;

    node *newNode = create(pre[*pos]);
    (*pos)++;
    if(st == en) return newNode;

    for(int i = st; i <= en; i++){
        if(in[i] == newNode->val){
            index = i;
            break;
        }
    }

    newNode->left = createTree(in, pre, st, index -1, pos);
    newNode->right = createTree(in, pre, index + 1, en, pos);

    return newNode;
}

int height(node *root, int a, int level){
    if(root == NULL) return -1;
    if(root->val == a) return level;

    int left = height(root->left, a, level + 1);
    if(left!=-1) return left;
    return height(root->right, a, level + 1);
}

node *parent(node *root, int a){
    if(root==NULL || (root->left == NULL && root->right == NULL)) return NULL;
    
    if((root->left && root->left->val == a) || (root->right && root->right->val == a)){
        return root;
    }

    node *left = parent(root->left, a);
    if(left!=NULL) return left;
    return parent(root->right, a);
}


void cousins(node *root, int a, int b){
    if(root->val == a || root->val == b){
        printf("no\n");
        return;
    }

    int bh = height(root, b, 0);
    int ah = height(root, a, 0);
    node *ap = parent(root, a);
    node *bp = parent(root, b);

    if(ah == bh){
        if(ap == bp){
            printf("no\n");\
            return;
        }
        else {
            printf("yes\n");
            return;
        }
    }
    else {
        printf("no\n");
        return;
    }
}

void postorder(node *root){
    if(root == NULL) return ;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int main(){
    int n;
    scanf("%d", &n);
    int in[n], pre[n];
    int pos = 0;
    int a,b;

    for(int i = 0; i < n; i++){
        scanf("%d", &pre[i]);
    }
    
    for(int i = 0; i < n; i++){
        scanf("%d", &in[i]);
    }

    node *head = createTree(in, pre, 0, n-1, &pos);

    char op;
    while(1){
        scanf(" %c", &op);
        if(op == 'p'){
            postorder(head);
            printf("\n");
        }
        else if(op == 'c'){
            scanf("%d %d", &a, &b);
            cousins(head, a, b);
        }
        else if(op == 'e'){
            break;
        }
    }
    return 0;
}