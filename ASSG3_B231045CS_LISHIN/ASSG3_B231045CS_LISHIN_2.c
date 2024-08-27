#include<stdio.h>
#include<stdlib.h>

typedef struct linkedList{
    int key;
    struct linkedList *next;
} node;

node *createNode(int n){
    node *newNode = (node *)malloc(sizeof(node));
    newNode->key = n;
    newNode->next = NULL;
    return newNode;
}

void insert(node *hashTable[], int key, int n){
    node *newNode = createNode(key);
    int hashIndex = key % n;

    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}


int main(){
    int n, key;
    scanf("%d", &n);
    node **hashTable = (node **)malloc(n * sizeof(node *));
    for(int i = 0; i < n; i++){
        hashTable[i] = NULL;
    }

    char op;
    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            scanf("%d", &key);
            insert(hashTable, key, n);
        }
        else if(op == 'f'){
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(hashTable[i] != NULL){
            node *temp = hashTable[i];
            while(temp!=NULL){
                printf("%d ", temp->key);
                temp = temp->next;
            }
            printf("\n");
        }
    }

    return 0;
}