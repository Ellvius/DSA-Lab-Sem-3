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
node *leftRotate(node *root, int *leftrot){
    node *x = root->right;
    node *y = x->left;
    root->right = y;
    x->left = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    (*leftrot)++;
    return x;
}

node *rightRotate(node *root, int *rightrot){
    node *x = root->left;
    node *y = x->right;
    root->left = y;
    x->right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    (*rightrot)++;
    return x;
}

/* Function to insert a new node and balance it at the same time */
node *AVL_insert(node *T,int n, int *lr, int *rr){

    // Incase the tree is empty
    if(T == NULL){
        return createNode(n);
    }

    // Find the correct subtree to insert
    if(n < T->data){
        T->left= AVL_insert(T->left, n, lr, rr);
        
        if(!isBalance(T)){  
            if(n < T->left->data){              // LL
                return rightRotate(T,rr);      
            }
            else {                              // LR
                T->left = leftRotate(T->left, lr);
                return rightRotate(T, rr);
            }
        }
    }
    else {
        T->right = AVL_insert(T->right, n, lr , rr);

        if(!isBalance(T)){
            if(n > T->right->data){             // RR
                return leftRotate(T, lr);
            }
            else {                              // RL
                T->right = rightRotate(T->right, rr);
                return leftRotate(T, lr);
            }
        }
    }

    // update height of each node
    T->height = max(height(T->left), height(T->right)) + 1;  
    return T;
}

/* function to check whether the value is there in the tree or not */
node *isPresent(node *T, int n){
    if(T == NULL){
        return T;
    }
    if(T->data == n){
        return T;
    }
    else if(n < T->data){
        return isPresent(T->left, n);
    } 
    else {
        return isPresent(T->right, n);
    }
}

void AVL_find(node *T,int n){
    if(isPresent(T,n)!= NULL){
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

void AVL_rotations(node *T, int lr, int rr){
    printf("%d %d\n", lr, rr);
}

// node AVL_delete(node *T,int n);

/* Function to print the balance factor of a given node  */
void AVL_balanceFactor(node *T,int n){
    node *tnode = isPresent(T,n);
    if(tnode == NULL){
        printf("-1\n");
        return;
    }
    int balanceFactor = height(tnode->left) - height(tnode->right);
    printf("%d\n", balanceFactor);
}


int main(){
    node *T = NULL;
    
    int leftRotation = 0, rightRotation = 0;
    char op;
    int num;
    
    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &num);
            T= AVL_insert(T,num, &leftRotation, &rightRotation);
        }
        else if(op == 'f'){
            scanf("%d", &num);
            AVL_find(T,num);
        }
        else if(op == 'p'){
            AVL_postorder(T);
            printf("\n");
        }
        else if(op == 's'){
            AVL_rotations(T, leftRotation, rightRotation);
        }
        // else if(op == 'd'){
        //     scanf("%d", &num);
        //     AVL_delete(T,num);
        // }
        else if(op == 'b'){
            scanf("%d", &num);
            AVL_balanceFactor(T,num);
        }
        else if(op == 'e'){
            break;
        }
    }

    return 0;
}