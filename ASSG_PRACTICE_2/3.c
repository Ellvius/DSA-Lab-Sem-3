#include<stdio.h>
#include<stdlib.h>

/* Declaration of binary search tree */
typedef struct tree {
	struct tree *right, *left;
	int data;
} bst;

/* Creation of new nodes*/
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
	
	// Find the correct position to insert the new node
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
	
	if(par->data > num)
		par->left = newNode;
	else
		par->right = newNode;
		
	return root;	
}


/* Function to print the subtrees in preorder traversal in parenthesis notation */
void preorderPar(bst *root){
	printf("(");
	if(root != NULL){
		printf("%d", root->data);
		preorderPar(root->left);
		preorderPar(root->right);
	}
	printf(")");
}

/* Find the subtree rooted at the given key value */
void subtree(bst *root, int key){
	// Find the key node
	bst *temp = root;
	
	while(temp != NULL && temp->data != key){
		if(temp->data > key)
			temp = temp->left;
		else 
			temp = temp->right;
	}
	
	// In case the key is not present in the tree
	if(temp == NULL){
		printf("%d not present\n", key);
		return; 
	}
	
	// Print the subtree in preorder traversal
	preorderPar(temp);
}


/* function to print the tree in order traversal */
void inorder(bst *root){
	if(root!=NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
	
}

int main(){
	//declarations
	bst *root = NULL;
	char op;
	int value, k;
	
	while(1){
		scanf(" %c", &op);
		if(op == 'i'){
			scanf("%d", &value);
			root = insertNode(root, value);
		}
		else if(op == 'p'){
			inorder(root);
			printf("\n");
		} 
		else if(op == 't'){
			scanf("%d", &k);
			subtree(root, k);
			printf("\n");
		}
		else if(op == 'e')
			break;
	} 
	
	return 0;
	
}
