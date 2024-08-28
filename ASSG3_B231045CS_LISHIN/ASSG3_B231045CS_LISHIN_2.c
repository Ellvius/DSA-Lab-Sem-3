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

    node *temp = hashTable[hashIndex];      // search whether the key is there. Print -1 if it is there
    while(temp!= NULL){
        if(temp->key == key)  {
            printf("-1\n");
            return;
        }
        temp = temp->next;
    }

    node* t = hashTable[hashIndex];
    node *prev = NULL;
    while(t!=NULL && t->key < key){
        prev = t;
        t = t->next;
    }
    if(prev == NULL){
        hashTable[hashIndex] = newNode;
        return;
    }
    newNode->next = t;
    prev->next = newNode;
}

void search(node *hashTable[], int searchKey, int n){
    int hashIndex = searchKey % n;
    int position = 1; 
    int flag = 0;
    node * temp = hashTable[hashIndex];
    while(temp!=NULL){
        if(temp->key == searchKey){
            flag = 1;
            break;
        }
        position++;
        temp = temp->next;
    }

    if(flag == 1){
        printf("%d %d\n", hashIndex, position);
    }
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
        else if(op == 'b'){
            scanf("%d", &key);
            search(hashTable, key, n);
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
    free(hashTable);

    return 0;
}