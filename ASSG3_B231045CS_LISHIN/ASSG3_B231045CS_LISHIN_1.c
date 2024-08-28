#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

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

    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}


void printHashTable(node *hashTable[]) {
    for (int i = 0; i < 4; i++) {
        node *temp = hashTable[i];
        while (temp != NULL) {
            printf("%s %s %d  ", temp->st->first_name, temp->st->rollno, temp->st->age);
            temp = temp->next;
        }
        printf("\n");
    }
}

void GroupIndexAndSplit(node *hashTable[], char name[]) {
    for (int index = 0; index < 4; index++) {
        node *temp = hashTable[index];
        while (temp != NULL) {
            if (strcmp(temp->st->first_name, name) == 0) {
                printf("%d\n", index);
                return;
            }
            temp = temp->next;
        }
    }
}

void GroupCountAndList(node *hashTable[], int k) {
    node *temp = hashTable[k];
    int count = 0;
    char a[100][NAMELENGTH];  
    int i = 0;

    while (temp != NULL) {
        strcpy(a[i], temp->st->first_name);  
        count++;
        i++;
        temp = temp->next;
    }

    for (int j = 0; j < count - 1; j++) {
        for (int l = j + 1; l < count; l++) {
            if (strcmp(a[j], a[l]) > 0) {
                char tempName[NAMELENGTH];
                strcpy(tempName, a[j]);
                strcpy(a[j], a[l]);
                strcpy(a[l], tempName);
            }
        }
    }
    printf("%d ", count);

    for (int j = 0; j < count; j++) {
        printf("%s ", a[j]);
    }
    printf("\n");
}

void GroupListByBranch(node *hashTable[], int k, char branch[]){
    node* temp = hashTable[k];
    int count= 0;

    while(temp!=NULL){
        if(toupper(temp->st->rollno[7]) == toupper(branch[0]) && toupper(temp->st->rollno[8]) == toupper(branch[1])){
            count++;
            printf("%s ", temp->st->first_name);
        }
        temp = temp->next;
    }
    if(count == 0) printf("-1");
    printf("\n");
}

void StudentDetails(node *hashTable[], char roll[]) {
    for (int i = 0; i < 4; i++) {
        node *temp = hashTable[i];
        while (temp != NULL) {
            if (strcmp(temp->st->rollno, roll) == 0) {
                printf("%s %d %c%c\n", temp->st->first_name, temp->st->age, temp->st->rollno[7], temp->st->rollno[8]);
                return;
            }
            temp = temp->next;
        }
    }
    printf("-1\n");
}

int main() {
    int n, k;
    char branch[3], roll[10];
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
        } 
        else if (op == 'b') {
            scanf("%d", &k);
            GroupCountAndList(hashTable, k);
        } 
        else if (op == 'c') {
            scanf("%d", &k);
            scanf("%s", branch);
            GroupListByBranch(hashTable, k, branch);
        } 
        else if (op == 'd') {
            scanf("%s", roll);
            StudentDetails(hashTable, roll);
        } 
        else if (op == 'f') {
            break;
        }
    }

    return 0;
}
