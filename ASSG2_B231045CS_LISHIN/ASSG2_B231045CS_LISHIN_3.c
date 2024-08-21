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

    return newNode;
}

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
    char parenthesis[1000];
    node *T = NULL;
    int index = 0;

    fgets(parenthesis, 1000, stdin);
    T = parenthesisToTree(parenthesis, &index);

    // Print the tree using preorder traversal
    preorder(T);

    return 0;
}

