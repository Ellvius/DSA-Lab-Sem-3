#include<stdio.h>
#include<stdlib.h>

// Linked List Declaration
typedef struct ll {
	int num;
	struct ll* next;
}node ;

// Insertion
node *insert(node *head, int val){
	// create node 
	node *newNode = malloc(sizeof(node));
	newNode->num = val;
	newNode->next = NULL;
	
	// Non - Empty list 
	if(head != NULL){
		// inserting new node to the head of the ll
		newNode->next = head;
	}
	
	// updating the head pointer
	head = newNode;
	return head;
}

// Deletion
node *delete(node *head, int val) {
	// Head case
	if(head->num == val){
		head = head->next;
	}
	else {
		//search the node preceding the required node
		node *temp= head;
		while(temp->next->num != val){
			temp = temp->next;
		}
		
		// update the preceding node
		temp->next = temp->next->next;
		
	}	
	return head;
}

// Display 
void display(node *head){
	if(head == NULL){
		printf("The list is empty");
	} else {
		node *temp = head;
		while(temp != NULL){
			printf("%d ", temp->num);
			temp = temp->next;
		}
	}
	printf("\n");
}


int main(){
	// Variable declaration
	node *Head = NULL;
	char op;
	int val;
	
	// Runner code
	printf("Functions: \n1.Insert - i \n2.Delete - x \n3.Display - d \n4. Exit - e\n");
	do {
		scanf("%c", &op);
		if(op == 'i'){
			printf("Enter value: ");
			scanf("%d", &val);
			Head = insert(Head, val);
		} else if(op == 'x') {
			printf("Enter the value to be deleted: ");
			scanf("%d", &val);
			Head = delete(Head, val);
		} else if(op == 'd') {
			display(Head);
		} 
	} while(op != 'e');
	
	return 0;
}

