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
        newNode->next = hashTable[hashIndex];  
        hashTable[hashIndex] = newNode;
    }
    else {
        prev->next = newNode;
        newNode->next = t;
    }
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
    else {
        printf("-1\n");
    }
}

int delete(node *hashTable[], int searchKey, int n){
    int hashIndex = searchKey % n;
    int position = 1;
    
    node *temp = hashTable[hashIndex];
    node *prev = NULL;


    while(temp!=NULL){
        if(temp->key> searchKey){
            printf("-1\n");
            return 0;
        }
        if(temp->key == searchKey){
            break;
        }
        position++;
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        printf("-1\n");
        return 0;
    }

    if(prev == NULL){
        hashTable[hashIndex] = hashTable[hashIndex]->next;
        return 1;
    }
    else {
        prev->next = temp->next;
        free(temp);
    }
    printf("%d %d\n", hashIndex, position);
    return 1;
}

void update(node *hashTable[], int oldKey, int newKey, int n){
    int hashIndex = oldKey % n;
    node *temp = hashTable[hashIndex];
    
    while(temp!=NULL){
        if(temp->key == newKey){
            printf("-1\n");
            return;
        }
        temp= temp->next;
    }

    int flag = delete(hashTable, oldKey, n);
    if(flag == 1){
        insert(hashTable, newKey, n);
    }
}

void printElementsInChain(node *hashTable[], int index, int n){
    node *temp = hashTable[index];
    while(temp!=NULL){
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}


int main(){
    int n, key, newKey;
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
        else if(op == 'c'){
            scanf("%d", &key);
            delete(hashTable, key, n);
        }
        else if(op == 'd'){
            scanf("%d", &key);
            scanf("%d", &newKey);
            update(hashTable, key, newKey, n);
        }
        else if(op == 'e'){
            scanf("%d", &key);
            printElementsInChain(hashTable, key, n);
        }
        else if(op == 'f'){
            break;
        }
    }
    
    free(hashTable);

    return 0;
}