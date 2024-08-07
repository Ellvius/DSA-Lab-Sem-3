#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int items[100];
    int front;
    int rear;
} Queue;


int isFull(Queue *q) {
    return (q->rear + 1) % 100 == q->front;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full.");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % 100;
    q->items[q->rear] = value;
}

void dequeue(Queue *q) {
    if (q->front == -1) {
        printf("Empty queue\n");
        return;  
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1; 
    } else {
        q->front = (q->front + 1) % 100;
    }
    printf("%d\n", value);
    return;
}

void front(Queue *q) {
    if (q->front == -1) {
        printf("Empty queue\n");
        return;  
    }
    printf("%d\n", q->items[q->front]);
    return ;
}

void rear(Queue *q) {
    if (q->front == -1) {
        printf("Empty queue\n");
        return;  
    }
    printf("%d\n", q->items[q->rear]);
    return ;
}

void display(Queue *q) {
    if (q->front == -1) {
        printf("Empty queue\n");
        return;
    }
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % 100;
    }
    printf("\n");
}

int main() {
    Queue *q;
    q->front = -1;
    q->rear = -1;

    int num;

    char i;
    do {
        scanf("%c", &i);
        if(i == 'a'){
            scanf("%d", &num);
            enqueue(q, num);
        }
        else if(i == 'b'){
            dequeue(q);
        }
        else if(i == 'c'){
            display(q);
        }
        else if(i == 'd'){
            front(q);
        } else if( i == 'e'){
            rear(q);
        }
    } while( i!= 'x');

    return 0;
}
