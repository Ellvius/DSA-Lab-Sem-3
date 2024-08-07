#include<stdio.h>


typedef struct {
    int data[100];
    int top;
} Stack;

void push(Stack *s, int num){
    if(s->top == 99){
        printf("Stack overflow\n");
        return;
    } 
    s->data[++(s->top)] = num;
}

void pop(Stack *s){
    if(s->top == -1){
        printf("Stack underflow\n");
        return;
    }
    printf("%d\n", s->data[s->top]);
    s->top--;
}

void peek(Stack *s){
    if(s->top == -1){
        printf("Stack empty\n");
        return;
    }
    printf("%d\n", s->data[s->top]);
}

void display(Stack *s){
    if(s->top == -1){
        printf("Stack empty\n");
        return;
    }
    for(int i=0; i<=s->top; i++){
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main(){
    Stack stack;
    stack.top = -1;
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
            peek(&stack);
        }
        else if(i == 'd'){
            display(&stack);
        }
    } while( i!= 'e');

    return 0;
}