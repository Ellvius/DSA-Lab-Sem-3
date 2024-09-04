#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 1000

typedef struct job_data {
    int JID;
    int priority;
} job;

void swap(job *a, job *b){
    job temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(job Que[], int i, int *heapSize){
    int l =  2 * i + 1;
    int r = 2 * i + 2;
    int min = i;

    if(l < *heapSize && Que[l].priority < Que[i].priority) {
        min = l;
    }
    if(r < *heapSize && Que[r].priority < Que[min].priority){
        min = r;
    }

    if(min != i){
        swap(&Que[i], &Que[min]);
        heapify(Que, min, heapSize);
    }
}

void buildMinHeap(job Que[], int i, int *heapSize){
    int parent = (i - 1)/2;
    if(i > 0 && Que[i].priority < Que[parent].priority ){
        swap(&Que[i], &Que[parent]);
        buildMinHeap(Que, parent, heapSize);
    }
}

void Add(job Que[], int *heapSize, int JobId, int Priority){
    for(int i = 0; i < *heapSize; i++){
        if(Que[i].JID == JobId) return;
    }

    Que[*heapSize].JID = JobId;
    Que[*heapSize].priority = Priority;

    (*heapSize)++;
    buildMinHeap(Que, (*heapSize)-1, heapSize);
}

void Schedule(job Que[], int *heapSize){
    if(*heapSize < 1){
        printf("-1\n");
        return;
    }

    printf("%d\n", Que[0].JID);
    swap(&Que[0], &Que[(*heapSize)-1]);
    (*heapSize)--;
    heapify(Que, 0, heapSize);
}

void NextJob(job Que[], int *heapSize){
    if(*heapSize < 1){
        printf("-1\n");
        return;
    }
    printf("%d\n", Que[0].JID);
}

void ReplacePriority(job Que[], int *heapSize, int JobId, int newPriority){
    int index = -1;
    for(int i = 0; i < *heapSize; i++){
        if(Que[i].JID == JobId){
            index = i;
        }
    }
    if(index == -1){
        printf("-1\n");
        return;
    }
    Que[index].priority = newPriority;
    if(newPriority > Que[index].priority){
        heapify(Que, index, heapSize);
    }
    else{
        buildMinHeap(Que, index, heapSize);
    }
}

void Display(job Que[], int *heapSize){
    if(*heapSize<1){
        printf("-1\n");
        return;
    }
    for(int i = 0; i < *heapSize; i++){
        printf("%d %d\n", Que[i].JID, Que[i].priority);
    }
}

int main(){
    job Que[SIZE];
    int heapSize = 0;
    int jobId, Priority;
    char op;

    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            scanf("%d %d", &jobId, &Priority);
            Add(Que, &heapSize, jobId, Priority);
        }
        else if(op == 'b'){
            Schedule(Que, &heapSize);
        }
        else if(op == 'c'){
            NextJob(Que, &heapSize);
        }
        else if(op == 'd'){
            scanf("%d %d", &jobId, &Priority);
            ReplacePriority(Que, &heapSize, jobId, Priority);
        }
        else if(op == 'e'){
            Display(Que, &heapSize);
        }
        else if(op == 'g'){
            break;
        }
    }
    return 0;
}