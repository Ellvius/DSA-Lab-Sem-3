#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAMELENGTH 100

typedef struct st {
    char first_name[NAMELENGTH];
    char rollno[10];
    int age;
} student;

typedef struct linkedList {
    student *st;
    struct linkedList *next;
} node;

int hash(student *a) {
    int sum = 0;
    int i = 0;
    while (a->first_name[i] != '\0') {
        sum += a->first_name[i];
        i++;
    }
    sum += a->age;
    return sum % 4;
}

node *createNode(student *stud) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->st = (student *)malloc(sizeof(student));  
    strcpy(newNode->st->first_name, stud->first_name);
    strcpy(newNode->st->rollno, stud->rollno);
    newNode->st->age = stud->age;
    newNode->next = NULL;
    return newNode;
}

void insert(node *hashTable[], student *s) {
    node *newNode = createNode(s);
    int hashIndex = hash(s);

    node *temp = hashTable[hashIndex];  
    while (temp != NULL) {
        if (strcmp(temp->st->rollno, s->rollno) == 0) {  
            return;  
        }
        temp = temp->next;
    }

    node *t = hashTable[hashIndex];
    node *prev = NULL;
    while (t != NULL && strcmp(t->st->first_name, s->first_name) < 0) {
        prev = t;
        t = t->next;
    }
    
    if (prev == NULL) {
        newNode->next = hashTable[hashIndex];  
        hashTable[hashIndex] = newNode;  
    } else {
        prev->next = newNode;  
        newNode->next = t;  
    }
}


void printHashTable(node *hashTable[]) {
    for (int i = 0; i < 4; i++) {
        node *temp = hashTable[i];
        while (temp != NULL) {
            printf("%s %s %d\n", temp->st->first_name, temp->st->rollno, temp->st->age);
            temp = temp->next;
        }
    }
}

void GroupIndexAndSplit(node *hashTable[], char name[]) {
    for (int index = 0; index < 4; index++) {
        node *temp = hashTable[index];
        while (temp != NULL) {
            printf("t3\n");
            if (strcmp(temp->st->first_name, name) == 0) {
                printf("%d\n", index);
                return;
            }
            temp = temp->next;
            printf("t2\n");
        }
    }
    printf("t1\n");
}

int main() {
    int n;
    scanf("%d", &n);
    
    node **hashTable = (node **)malloc(4 * sizeof(node *));
    for (int i = 0; i < 4; i++) {
        hashTable[i] = NULL;  
    }

    for (int i = 0; i < n; i++) {
        student *s = (student *)malloc(sizeof(student));  
        scanf("%s", s->first_name);
        scanf("%s", s->rollno);
        scanf("%d", &s->age);
        insert(hashTable, s);
    }

    printHashTable(hashTable);

    char name[NAMELENGTH];
    char op;
    while (1) {
        scanf(" %c", &op);
        if (op == 'a') {
            scanf("%s", name);
            GroupIndexAndSplit(hashTable, name);
        } else if (op == 'f') {
            break;
        }
    }

    return 0;
}
