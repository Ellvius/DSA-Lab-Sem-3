#include <stdio.h>
#include <stdlib.h>

/* structure declaration */
typedef struct avl_node {
    int key;
    int value;
    int height;
    struct avl_node *left, *right;
} node;


/* Function to create an avl node with a given value */
node *createNode(int k, int v){
    // allocating memory for a new node
    node *newNode = (node *)malloc(sizeof(node));

    // initialising parameters
    newNode->key = k;
    newNode->value = v;
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

/* Inserts a key-value pair into the ordered map K */
node *Insert(node *K,int k, int val){

    // Incase the tree is empty
    if(K == NULL){
        return createNode(k, val);
    }

    // Find the correct subtree to insert
    if(k < K->key){
        K->left= Insert(K->left, k, val);
        
        if(!isBalance(K)){  
            if(k < K->left->key){              // LL
                return rightRotate(K);      
            }
            else {                              // LR
                K->left = leftRotate(K->left);
                return rightRotate(K);
            }
        }
    }
    else {
        K->right = Insert(K->right, k, val);

        if(!isBalance(K)){
            if(k > K->right->key){             // RR
                return leftRotate(K);
            }
            else {                              // RL
                K->right = rightRotate(K->right);
                return leftRotate(K);
            }
        }
    }

    // update height of each node
    K->height = max(height(K->left), height(K->right)) + 1;  
    return K;
}


/*  Check whether the ordered map is empty or not K. */
void Empty(node *K){
    if(K == NULL){
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}


/* function to check whether the value is there in the tree or not */
// node *isPresent(node *T, int n){
//     if(T == NULL){
//         return T;
//     }
//     if(T->key == n){
//         return T;
//     }
//     else if(n < T->key){
//         return isPresent(T->left, n);
//     } 
//     else {
//         return isPresent(T->right, n);
//     }
// }

// /* Function to print the path of the node if it is present in the tree */
// void Find(node *T,int n){
//     if(isPresent(T,n)!= NULL){
//         if(T->data == n ){
//             printf("%d\n", n);
//             return;
//         }
//         else if(n < T->data){
//             printf("%d ", T->data);
//             Find(T->left, n);
//         }
//         else {
//             printf("%d ", T->data);
//             Find(T->right, n);
//         }
//     }
//     else {
//         printf("-1\n");
//     }
    
// }

/* Display all the keys in the ordered map K in descending order. */
void DisplayElements(node *K){
    if(K==NULL) return;
    DisplayElements(K->right);
    printf("%d ", K->key);
    DisplayElements(K->left);
}


int main(){
    node *K = NULL;
    char op;
    int key= 0 , value = 0;
    
    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &key);
            scanf("%d", &value);
            K= Insert(K,key, value);
        }
        // else if(op == 'u'){
        //     scanf("%d", &key);
        //     UpperBound(K, key);
        // }
        // else if(op == 'f'){
        //     scanf("%d", &key);
        //     Find(K,key);
        // }
        // else if(op == 's'){
        //     Size(K)
        // }
        else if(op == 'e'){
            Empty(K);
        }
        else if(op == 'd'){
            if(K==NULL){
                printf("-1\n");
            }
            else{
                DisplayElements(K);
                printf("\n");
            }
        }
        else if(op == 't'){
            break;
        }
    }

    return 0;
}