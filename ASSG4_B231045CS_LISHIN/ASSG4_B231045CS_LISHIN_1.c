#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int h[], int i, int *heapSize){
    int l =  2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if(l < *heapSize && h[l] > h[i]) {
        largest = l;
    }
    if(r < *heapSize && h[r] > h[largest]){
        largest = r;
    }

    if(largest != i){
        swap(&h[i], &h[largest]);
        heapify(h, largest, heapSize);
    }
}

void buildMaxHeap(int h[], int i, int *heapSize){
    if(i > 0 && h[i]>h[(i-1)/2]){
        swap(&h[i], &h[(i-1)/2]);
        buildMaxHeap(h, (i-1)/2, heapSize);
    }
}

void InsertKey(int h[], int n, int *heapSize){
    for(int i = 0; i < *heapSize; i++){
        if(h[i] == n) return;
    }
    h[*heapSize] = n;
    (*heapSize)++;
    buildMaxHeap(h, (*heapSize)-1, heapSize);
}

int FindMax( int h[], int *heapSize){
    if(*heapSize < 1) return -1;
    return h[0];
}

void ExtractMax( int h[], int *heapSize){
    if(*heapSize < 1){
        printf("-1\n");
        return;
    }

    printf("%d ", h[0]);
    swap(&h[0], &h[(*heapSize)-1]);
    (*heapSize)--;
    heapify(h, 0, heapSize);

    for(int i = 0; i < *heapSize; i++){
        printf("%d ", h[i]);
    }
    printf("\n");
}

void KthLargest(int h[], int *heapSize, int k) {
    if (k > *heapSize) {
        printf("-1\n");
        return;
    }

    for(int i = 0; i < *heapSize; i++){
        for(int j = i + 1; j < *heapSize; j++ ){
            if(h[j] > h[j-1]){
                swap(&h[j], &h[j-1]);
            }
        }
    }

    printf("%d\n", h[k-1]);
}

void DeleteKey(int h[], int *heapSize, int n){
    if(*heapSize<1){
        printf("-1\n");
        return;
    }
    if(*heapSize == 1){
        if(h[0] == n){
            printf("0\n");
            return;
        }
    }
    int index = -1;
    for(int i = 0; i < *heapSize; i++){
        if(h[i] == n){
            index = i;
        }
    }

    if(index == -1){
        printf("-1\n");
        return;
    }
    swap(&h[index], &h[(*heapSize)-1]);
    (*heapSize)--;
    heapify(h, index, heapSize);

    for(int i = 0; i < *heapSize; i++){
        printf("%d ", h[i]);
    }
    printf("\n");
}

void ReplaceKey(int h[], int *heapSize, int num, int num1){
    int index = -1;
    for(int i = 0; i < *heapSize; i++){
        if(h[i] == num){
            index = i;
        }
    }
    if(index == -1){
        int dif = 0;
        if(num > num1){
            dif = num - num1;
        }
        else if (num1 > num){
            dif = num1 - num;
        }
        printf("%d\n", dif);
        return;
    }
    h[index] = num1;
    if(num > num1){
        heapify(h, index, heapSize);
    }
    else{
        buildMaxHeap(h, index, heapSize);
    }
    for(int i = 0; i < *heapSize; i++){
        printf("%d ", h[i]);
    }
    printf("\n");
}


int main(){
    int heap[SIZE];
    int heapSize = 0;
    int max, num, k, num1;
    char op;

    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            scanf("%d", &num);
            InsertKey(heap, num, &heapSize);
        }
        else if(op == 'b'){
            max = FindMax(heap, &heapSize);
            printf("%d\n", max);
        }
        else if(op == 'c'){
            ExtractMax(heap, &heapSize);
        }
        else if(op == 'd'){
            scanf("%d", &k);
            KthLargest(heap, &heapSize, k);
        }
        else if(op == 'e'){
            scanf("%d", &num);
            DeleteKey(heap, &heapSize, num);
        }
        else if(op == 'f'){
            scanf("%d", &num);
            scanf("%d", &num1);
            ReplaceKey(heap, &heapSize, num, num1);
        }
        else if(op == 'g'){
            break;
        }

    }
        

    return 0;
}