
/* Aadhar allocation system the aadhar numbers are stored by folding method and the hash table is rehashed when it is 60 percent full(The size is doubled ). The conflicts are resolved by quadratic probing */

#include <stdio.h>
#include <stdlib.h>

int hash(long long int n, int k) {
    int n1 = n / 100000000;
    int n3 = n % 10000;
    int n2 = (n % 100000000) / 10000;
    int sum = n1 + n2 + n3;
    return sum % k;
}

void insert(long long int h[], int k, long long int n) {
    int hi = hash(n, k);
    int p = 0;
    int thi = hi;
    while (h[hi] != -1) {
        hi = (thi + (p * p)) % k;
        p++;
    }
    h[hi] = n;
}

long long int *rehash(long long int h[], int *k, long long int num[], int size) {
    int old_k = *k;
    *k = (*k) * 2;
    long long int *newt = (long long int *)malloc((*k) * sizeof(long long int));
    
    for (int i = 0; i < (*k); i++) {
        newt[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        insert(newt, *k, num[i]);
    }

    free(h);
    return newt;
}

void display(long long int h[], int k) {
    for (int i = 0; i < k; i++) {
        printf("%lld ", h[i]);
    }
    printf("\n");
}

int main() {
    int k;
    scanf("%d", &k);
    long long int num[1000]; 
    long long int *ht = (long long int *)malloc(k * sizeof(long long int));

    for (int i = 0; i < k; i++) {
        ht[i] = -1;
    }

    int index = 0;
    char op;
    
    while (1) {
        scanf(" %c", &op);
        if (op == 'i') {
            scanf("%lld", &num[index]);
            insert(ht, k, num[index]); 
            index++;
            if (index*10 > (6 * k)) {
                ht = rehash(ht, &k, num, index);
            }
        } else if (op == 'd') {
            display(ht, k); 
        }
        else if(op == 'e'){
            break;
        }
    }
    
    free(ht);
    return 0;
}
