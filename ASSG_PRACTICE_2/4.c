#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Declaration of binary search tree */
typedef struct tree {
	struct tree *right, *left;
	int data;
} bst;

/* Creation of new nodes */
bst *createNode(bst *root, int num){
	bst *newnode = (bst *)malloc(sizeof(bst));
	
	newnode->right = NULL;
	newnode->left = NULL;
	newnode->data = num;
	
	return newnode;
}

/* insertion of new node into its appropriate position in binary tree */
bst *insertNode(bst *root, int num){
	bst *newNode = createNode(root, num);
	
	// In case the bst is empty
	if(root == NULL){
		root = newNode;
		return root;
	}
	
	// Find the parent of the correct position to insert the new node
	bst *temp = root;
	bst *par = NULL;
	while (temp != NULL){
		if(temp->data > num){
			par = temp;		
			temp = temp->left;
		}
		else {
			par = temp; 		
			temp = temp->right;
		}
	}
	
	// insert the node to its required position
	if(par->data > num)
		par->left = newNode;
	else
		par->right = newNode;
		
	return root;	
}

/* Function to convert the given string in parenthesis form to bst */
void tree(char s[]){
	
} 


/* function to print the tree in preorder traversal */
void preorder(bst *root){
	if(root!=NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
	
}

int main(){
	// declarations
	bst *root = NULL;
	char bst[100];
	
	// take parenthesis input of bst
	scanf(" %[^n\]", bst);
	
	// skim through the string and insert numbers to the root
	tree(bst);
	
	//print the converted tree in preorder traversal
	preorder(root);
	return 0;
}
