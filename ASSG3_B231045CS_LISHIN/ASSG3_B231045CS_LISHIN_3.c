#include<stdio.h>
#include<stdlib.h>

#define DELETED -1

int LinearProbing(int hashTable[],int a[], int n, int m){
    int c = 0;

    for(int i = 0; i < m; i++){
        int hashIndex = a[i] % n;

        while(hashTable[hashIndex]!=DELETED) {
            hashIndex = (hashIndex + 1) % n;
            c++;
        }
        hashTable[hashIndex] = a[i];
        printf("%d ", hashIndex);
    }
    return c;
}

int QuadraticProbing(int hashTable[],int a[], int n, int m){
    int c = 0;
    for(int i = 0; i < m; i++){
        int probe = 1;
        int hashIndex = a[i] % n;
        int index = hashIndex;
        while(hashTable[hashIndex]!=DELETED) {
            hashIndex = (index + (probe*probe)) % n;  // each time the index is same so don't update the hashIndex
            c++;
            probe++;
        }
        hashTable[hashIndex] = a[i];
        printf("%d ", hashIndex);
    }
    return c;
}

int largestPrime(int n){
    for(int i = n-1; i >= 2; i--){
        int flag = 0;
        for(int j = 2; j*j<=i; j++){
            if(i%j == 0) flag = 1;
        }
        if(flag == 0) return i;
    }
    return 1;
}

int DoubleHashing(int hashTable[], int a[], int n, int m){
    int c = 0;
    int p = largestPrime(n);
    
    for(int i = 0; i < m; i++){
        int hashIndex = a[i] % n;
        int probe = 1;
        int h1 = hashIndex;
        int h2 = p - (a[i] % p);

        while(hashTable[hashIndex]!=DELETED){
            hashIndex = (h1 + (probe * h2)) % n;
            probe++;
            c++;
        }
        hashTable[hashIndex] = a[i];
        printf("%d ", hashIndex);
    }
    return c;
}

int main(){
    int n,m;
    scanf("%d %d", &n, &m);

    int *hashTable = (int *)malloc(n*sizeof(int));
    
    int *arr = (int *)malloc(m*sizeof(int));
    for(int i = 0; i< m; i++){
        scanf("%d", &arr[i]);
    }

    int collision = 0;
    char op;
    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            for(int i=0; i<n; i++){
                hashTable[i] = DELETED;
            }
            collision = LinearProbing(hashTable, arr, n, m);
            printf("\n");
            printf("%d\n", collision);
        }
        else if(op == 'b'){
            for(int i=0; i<n; i++){
                hashTable[i] = DELETED;
            }
            collision = QuadraticProbing(hashTable, arr, n, m);
            printf("\n");
            printf("%d\n", collision);
        }
        else if(op == 'c'){
            for(int i=0; i<n; i++){
                hashTable[i] = DELETED;
            }
            collision = DoubleHashing(hashTable, arr, n, m);
            printf("\n");
            printf("%d\n", collision);
        }
        else if(op == 'd'){
            break;
        }
    }

    free(hashTable);
    free(arr);
    return 0;
}