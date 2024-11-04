#include<string.h>
#include<stdio.h>

void badCharTable(char p[], int m, int badChar[]){
    for(int i = 0; i < 256; i++){
        badChar[i] = -1;
    }

    for(int i = 0; i < m; i++){
        badChar[(int)p[i]] = i;
    }
}

void boyerMoore(char t[], char p[]){
    int n = strlen(t);
    int m = strlen(p);

    int badcharTable[256];
    badCharTable(p, m, badcharTable);

    int s = 0;
    int index = -1;
    
    while(s<=n-m){
        int j = m-1;

        for(; j >= 0 && p[j]==t[s+j]; j--){
        }
        // if the pattern is found 
        int shift;
        if(j < 0){
            shift = (s+m < n) ? m-badcharTable[(int)t[s+m]]:1;
            index = s;
            printf("%d\n", index);
            return;
        }
        else {
            shift = (j-badcharTable[(int)t[s+j]] > 1) ? j-badcharTable[(int)t[s+j]]: 1;
        }
        s+=shift;
    }
    printf("%d\n", index);
}

int main(){
    char t[1000000], p[100000];
    fgets(t, 1000000, stdin);
    fgets(p, 100000, stdin);

    boyerMoore(t, p);

    return 0;
}