#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 100
#define SIZE 1000

typedef struct patient_data {
    int id;
    int severity;
    char name[NAME_SIZE];
} patient;

void swap(patient *a, patient *b){
    patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(patient PQ[], int i, int *heapSize){
    int l =  2 * i + 1;
    int r = 2 * i + 2;
    int min = i;

    if(l < *heapSize && PQ[l].severity < PQ[i].severity) {
        min = l;
    }
    if(r < *heapSize && PQ[r].severity < PQ[min].severity){
        min = r;
    }

    if(min != i){
        swap(&PQ[i], &PQ[min]);
        heapify(PQ, min, heapSize);
    }
}

void buildMinHeap(patient PQ[], int i, int *heapSize){
    int parent = (i - 1)/2;
    if(i > 0 && PQ[i].severity < PQ[parent].severity ){
        swap(&PQ[i], &PQ[parent]);
        buildMinHeap(PQ, parent, heapSize);
    }
}

void AdmitPatient(patient PQ[], int Id, char Name[], int Severity, int *heapSize){
    for(int i = 0; i < *heapSize; i++){
        if(PQ[i].severity == Severity) return;
    }

    PQ[*heapSize].id = Id;
    PQ[*heapSize].severity = Severity;
    strcpy(PQ[*heapSize].name ,Name);

    (*heapSize)++;
    buildMinHeap(PQ, (*heapSize)-1, heapSize);

    for(int i = 0; i < *heapSize; i++){
        printf("%d ", PQ[i].id);
    }
    printf("\n");
}

void TreatPatient( patient PQ[], int *heapSize){
    if(*heapSize < 1){
        printf("-1\n");
        return;
    }

    printf("%d %s\n", PQ[0].id, PQ[0].name);
    swap(&PQ[0], &PQ[(*heapSize)-1]);
    (*heapSize)--;
    heapify(PQ, 0, heapSize);
}

void UpdateSeverity( patient PQ[], int *heapSize, int Id, int newSeverity){
    int index = -1;
    for(int i = 0; i < *heapSize; i++){
        if(PQ[i].id == Id){
            index = i;
        }
    }
    if(index == -1){
        printf("-1\n");
        return;
    }
    PQ[index].severity = newSeverity;
    if(newSeverity > PQ[index].severity){
        heapify(PQ, index, heapSize);
    }
    else{
        buildMinHeap(PQ, index, heapSize);
    }
    for(int i = 0; i < *heapSize; i++){
        printf("%d ", PQ[i].id);
    }
    printf("\n");
}

void QueryPatient(patient PQ[], int *heapSize, int searchId){
    for(int i = 0; i < *heapSize; i++){
        if(PQ[i].id == searchId){
            printf("%s %d\n", PQ[i].name, PQ[i].severity);
            return;
        }
    }
    printf("-1\n");
}

void FindMostSevere(patient PQ[], int *heapSize) {
    if (1 > *heapSize) {
        printf("-1\n");
        return;
    }
    
    for(int i = 0; i < *heapSize; i++){
        for(int j = i + 1; j < *heapSize; j++ ){
            if(PQ[j].severity < PQ[j-1].severity){
                swap(&PQ[j], &PQ[j-1]);
            }
        }
    }
    for(int k = 0; k < *heapSize && k < 3; k++ ){
        printf("%d %s %d\n", PQ[k].id, PQ[k].name, PQ[k].severity);
    }
}

int main(){
    patient PQ[SIZE];
    int heapSize = 0;
    int id, severity, newSeverity;
    char NAME[NAME_SIZE];
    char op;

    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            scanf("%d", &id);
            scanf("%d", &severity);
            scanf("%s", NAME);
            AdmitPatient(PQ, id, NAME, severity, &heapSize);
        }
        else if(op == 'b'){
            TreatPatient(PQ, &heapSize);
        }
        else if(op == 'c'){
            scanf("%d", &id);
            scanf("%d", &newSeverity);
            UpdateSeverity(PQ, &heapSize, id, newSeverity);
        }
        else if(op == 'd'){
            scanf("%d", &id);
            QueryPatient(PQ, &heapSize, id);
        }
        else if(op == 'e'){
            FindMostSevere(PQ, &heapSize);
        }
        else if(op == 'g'){
            break;
        }

    }

    return 0;
}