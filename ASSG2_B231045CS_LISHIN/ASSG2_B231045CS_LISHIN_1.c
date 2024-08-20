#include <stdio.h>
#include <stdlib.h>

/* structure declaration */
typedef struct avl_node {
    int data;
    int height;
    struct avl_node *left, *right;
} node;


/* Function to create an avl node with a given value */
node *createNode(int num){
    // allocating memory for a new node
    node *newNode = (node *)malloc(sizeof(node));

    // initialising parameters
    newNode->data = num;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

/* Max function */
int max(int a, int b){
    if(a>b) return a;
    return b;
}

/* find height of a node */
int height(node *root){
    if(root == NULL) return 0;
    return root->height;
}

/* Function to find the imbalance of a node in a tree */
int isBalance(node *root){
    if (root == NULL) return 1; // NULL tree is balanced
    int leftHeight = (root->left != NULL) ? root->left->height : 0;
    int rightHeight = (root->right != NULL) ? root->right->height : 0;
    int balanceFactor = leftHeight - rightHeight;
    return (balanceFactor >= -1 && balanceFactor <= 1);
}


/* Left rotate and right rotate functions for nodes */
node *leftRotate(node *root){
    node *x = root->right;
    node *y = x->left;
    root->right = y;
    x->left = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

node *rightRotate(node *root){
    node *x = root->left;
    node *y = x->right;
    root->left = y;
    x->right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

/* Function to insert a new node and balance it at the same time */
node *AVL_insert(node *T,int n){

    // Incase the tree is empty
    if(T == NULL){
        return createNode(n);
    }

    // Find the correct subtree to insert
    if(n < T->data){
        T->left= AVL_insert(T->left, n);
        
        if(!isBalance(T)){  
            if(n < T->left->data){              // LL
                return rightRotate(T);      
            }
            else {                              // LR
                T->left = leftRotate(T->left);
                return rightRotate(T);
            }
        }
    }
    else {
        T->right = AVL_insert(T->right, n);

        if(!isBalance(T)){
            if(n > T->right->data){             // RR
                return leftRotate(T);
            }
            else {                              // RL
                T->right = rightRotate(T->right);
                return leftRotate(T);
            }
        }
    }

    // update height of each node
    T->height = max(height(T->left), height(T->right)) + 1;  
    return T;
}

/* function to check whether the value is there in the tree or not */
int isPresent(node *T, int n){
    if(T == NULL){
        return 0;
    }
    if(T->data == n){
        return 1;
    }
    else if(n < T->data){
        return isPresent(T->left, n);
    } 
    else {
        return isPresent(T->right, n);
    }
}

void AVL_find(node *T,int n){
    if(isPresent(T,n)){
        if(T->data == n ){
            printf("%d\n", n);
            return;
        }
        else if(n < T->data){
            printf("%d ", T->data);
            AVL_find(T->left, n);
        }
        else {
            printf("%d ", T->data);
            AVL_find(T->right, n);
        }
    }
    else {
        printf("-1\n");
    }
    
}

void AVL_postorder(node *T){
    if(T==NULL) return;
    AVL_postorder(T->left);
    AVL_postorder(T->right);
    printf("%d ", T->data);
}

// node AVL_rotations(node *T);

// node AVL_delete(node *T,int n);

// node AVL_balanceFactor(node *T,int n);

int main(){
    node *T = NULL;
    
    char op;
    int num;
    
    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &num);
            T= AVL_insert(T,num);
        }
        else if(op == 'f'){
            scanf("%d", &num);
            AVL_find(T,num);
        }
        else if(op == 'p'){
            AVL_postorder(T);
            printf("\n");
        }
        // else if(op == 's'){
        //     AVL_rotations(T);
        // }
        // else if(op == 'd'){
        //     scanf("%d", &num);
        //     AVL_delete(T,num);
        // }
        // else if(op == 'b'){
        //     scanf("%d", &num);
        //     AVL_balanceFactor(T,num);
        // }
        else if(op == 'e'){
            break;
        }
    }

    return 0;
}