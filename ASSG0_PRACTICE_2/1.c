#include<stdio.h>
#include<stdlib.h>

// Declaration of binary search tree
typedef struct tree {
	struct tree *right, *left;
	int data;
} bst;

// Creation of new nodes
bst *createNode(bst *root, int num){
	bst *newnode = (bst *)malloc(sizeof(bst));
	
	newnode->right = NULL;
	newnode->left = NULL;
	newnode->data = num;
	
	return newnode;
}

// insertion of new node into its appropriate position in binary tree
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

// function to find the inorder successor
void successor(bst *root, int key){
	bst *temp = root;
	bst *parent = NULL;
	
	while(temp != NULL && temp->data != key){
		//In case the node does not have a right subtree we have tgo track its parent
		if(temp->data > key){
			parent = temp;
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	
	// In case the node is not present in the tree
	if(temp == NULL){
		printf("%d not present\n", key);
		return;
	}
	
	// If the node has a right subtree
	if(temp->right != NULL){
		//find the minimum node in the right subtree
		bst *min = temp->right;
		while(min->left != NULL)
			min = min->left;
			
		printf("%d\n", min->data);
	}
	
	// If the node doesn't have a right subtree 
	else {
		// If the node is the last node 
		if(parent == NULL)
			printf("No successor\n");
		else
			printf("%d\n", parent->data);
	}
}

// function to print the tree in order traversal
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
		else if(op == 's'){
			scanf("%d", &k);
			successor(root, k);
		}
		else if(op == 'e')
			break;
	} 
	
	return 0;
	
}
