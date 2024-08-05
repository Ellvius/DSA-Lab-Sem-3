#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} node;

node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) {
        printf("Error allocating memory\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(node** top, int data) {
    node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

int pop(node** top) {
    if ((*top)== NULL) {
        printf("Stack underflow\n");
        return -1; 
    }
    node* temp = *top;
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    printf("%d\n", value);
}

int peek(node* top) {
    if ((top) == NULL) {
        printf("Empty stack\n");
        return -1; 
    }
    printf("%d\n", top->data);
}

void display(node *top){
    if(top == NULL){
        printf("Stack empty\n");
        return;
    }
    node *temp = top;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    node* stack = NULL;

    int num;

    char i;
    do {
        scanf("%c", &i);
        if(i == 'a'){
            scanf("%d", &num);
            push(&stack, num);
        }
        else if(i == 'b'){
            pop(&stack);
        }
        else if(i == 'c'){
            peek(stack);
        }
        else if(i == 'd'){
            display(stack);
        }
    } while( i!= 'e');

    return 0;
}
