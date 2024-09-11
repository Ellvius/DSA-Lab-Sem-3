/* Hash Table implementation with rehashing when the table is filled 75 percent(the size is doubled). The conflicts are resolved by quadratic probing. */

#include<stdio.h>
#include<stdlib.h>

void HashInsert(int hashTable[], int num, int k){
    int hashIndex = num % k;
    int probe = 0;
    int index = hashIndex;
    while(hashTable[hashIndex]!=-1){
        hashIndex = (index + (probe*probe)) % k;
        probe++;
    }
    hashTable[hashIndex] = num;
}

int *Rehash(int hashTable[], int *k, int num[], int size){
    int l = *k;
    *k = 2 * l;

    int *newTable = (int *)malloc((*k)*sizeof(int));
    for(int i = 0; i < (*k); i++){
        newTable[i] = -1;
    }

    for(int i = 0; i < size; i++){
        HashInsert(newTable, num[i], *k);
    }

    return newTable;
}

void DisplayTable(int hashTable[], int k){
    if(k == 0){
        printf("-1\n");
        return;
    }
    for(int i = 0; i < k; i++){
        printf("%d ", hashTable[i]);
    }
    printf("\n");
}

int main(){
    int k;
    scanf("%d", &k);

    int* hashtable = (int *)malloc(k * sizeof(int));
    for(int i = 0; i < k ; i++){
        hashtable[i] = -1;
    }
    int arr[1000];

    int index = 0;
    char op;
    while(1){
        scanf(" %c", &op);
        if(op == 'i'){
            scanf("%d", &arr[index]);
            HashInsert(hashtable, arr[index], k);
            index++;
            if(index*100 > 75*k){
                hashtable = Rehash(hashtable, &k, arr, index);
            }
        }
        else if( op == 'd'){
            DisplayTable(hashtable, k);
        }
        else if(op == 'e'){
            break;
        }
    }
    free(hashtable);
    return 0;
}