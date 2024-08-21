#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Struct declaration for AVL tree nodes */
typedef struct avl_node {
    int key;
    int height;
    struct avl_node *left, *right;
} node;

/* Function to create an AVL node with a given value */
node *createNode(int k) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->key = k;
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

node *AVL_SeqInsert(node *T,int n){

    // Incase the tree is empty
    if(T == NULL){
        return createNode(n);
    }

    // Find the correct subtree to insert
    if(n < T->key){
        T->left= AVL_SeqInsert(T->left, n);
        
        if(!isBalance(T)){  
            if(n < T->left->key){              // LL
                return rightRotate(T);      
            }
            else {                              // LR
                T->left = leftRotate(T->left);
                return rightRotate(T);
            }
        }
    }
    else {
        T->right = AVL_SeqInsert(T->right, n );

        if(!isBalance(T)){
            if(n > T->right->key){             // RR
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

/* Function to print the subtrees in preorder traversal in parenthesis notation */
void preorderPar(node *root){
	printf("( ");
	if(root != NULL){
		printf("%d ", root->key);
		preorderPar(root->left);
		preorderPar(root->right);
	}
	printf(") ");
}

/* Function to parse an integer from the string */
int num(char s[], int* index) {
    int n = 0;
    while (isdigit(s[*index])) {
        n = 10 * n + (s[*index] - '0');
        (*index)++;
    }
    (*index)++;
    return n;

}

/* Function to construct the tree from the parenthesis representation */
node *parenthesisToTree(char s[], int *index) {
    if (s[*index] == '\n' || s[*index] == ')' || s[*index] == '\0') {
        return NULL;
    }

    if (s[*index] == ' ') {
        (*index)++;
    }

    if(s[*index] == ')'){
        return NULL;
    }
    // parse the number and create node
    int number = num(s, index);
    node *newNode = createNode(number);

    // If there are more elements, look for children
    if (s[*index] == '(') {
        (*index)++;
        newNode->left = parenthesisToTree(s, index);
        if (s[*index] == ')') {
            (*index)+=2;  // Move past the closing parenthesis
        }

        if (s[*index] == '(') {
            (*index)++;
            newNode->right = parenthesisToTree(s, index);
            if (s[*index] == ')') {
                (*index)+=2;  // Move past the closing parenthesis
            }
        }
    }
   newNode->height = max(height(newNode->left), height(newNode->right)) + 1;  

    return newNode;
}

// /* function to delete the node in an avl tree */
// node *delete(node *T,int n, int *count){

//     if(T == NULL) {
//         return T;
//     }
//     if( n < T->key){
//         T->left = delete(T->left, n, count);
//     }
//     else if(n > T->key){
//         T->right = delete(T->right, n, count);
//     }
//    // we reach the node
//     else {
//         if (T->left == NULL && T->right == NULL) { // Case 1: The node has no childrenII
//             node *temp = T;
//             T = NULL;  
//             free(temp);  
//             count++;
//         }
//         else if (T->left == NULL) {             // Case 2: The node has only a right child
//             node *temp = T;
//             T = T->right;  
//             free(temp);  
//             count++;
//         }
//         else if (T->right == NULL) {            // Case 2: The node has only a left child
//             node *temp = T;
//             T = T->left;  
//             free(temp);  
//             count++;
//         }
//         else {                                      // case 3 : The node has both children
//             node *temp = T->right;
//             while(temp->left != NULL){
//                 temp = temp->left;
//             }
//             T->key = temp->key;
//             T->right = delete(T->right, n, count);
//         }
    
//     }
// }

// int AVL_RangeDelete(node *root, int n1, int n2){
//     int count = 0;
//     for(int i =n1; i<=n2; i++){
//         delete(root, i, &count);
//     }
//     return count;
// }

/* Preorder traversal of the tree */
void preorder(node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Main function */
int main() {
    char op, sp;
    char parenthesis[1000];
    node *T = NULL;
    int index = 0;
    int n1, n2, n;
    int i = 0;
    int count = 0;

    fgets(parenthesis, 1000, stdin);
    T = parenthesisToTree(parenthesis, &index);

    // Print the tree using preorder traversal
    preorder(T);
    printf("\n");
    while(1){
        scanf(" %c", &op);
        if (op == 'a') {
            while(1){
                scanf("%c", &sp);
                if(sp == '\n') break;
                scanf("%d", &n);
                T = AVL_SeqInsert(T, n);
            }
            preorderPar(T);
            printf("\n");
        }
        // else if(op == 'b'){
        //     scanf("%d", &n1);
        //     scanf("%d", &n2);
        //     count = AVL_RangeDelete(T, n1, n2);
        //     if(count == 0){
        //         printf("-1\n");
        //     }
        //     else {
        //         printf("%d ", count);
        //     }
        //     preorder(T);
        //     printf("\n");
        // }
        // else if(op == 'c'){
        //     scanf("%d", &n);
        //     AVL_SuccessorPath(T, n);
        // }
        // else if(op == 'd'){
        //     scanf("%d", &n);
        //     AVL_SubtreeSum(T, n);
        // }
        // else if(op == 'e'){
        //     scanf("%d", &n);
        //     AVL_FindClosest(T, n);
        // }
        else if(op == 'g'){
            break;
        }
    }

    return 0;
}

