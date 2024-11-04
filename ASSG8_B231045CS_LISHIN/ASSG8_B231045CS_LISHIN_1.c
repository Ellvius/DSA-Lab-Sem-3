#include<stdio.h>
#include<string.h>

// compute the longest prefix suffix at each index
void computelps(char p[], int m, int lps[]){
    int l = 0;
    lps[0] = 0;
    for(int i = 1; i < m; i++){

        // in case the char does not match backtrack
        while(l > 0 && p[i]!=p[l]){
            l = lps[l-1];
        }
        // increase the length at each matching prefix
        if(p[i]==p[l]){
            l++;
        }
        lps[i] = l;
    }
}

void kmp(char t[], char p[]){
    int n = strlen(t);
    int m = strlen(p);
    int index = -1;
    int f = 0;

    // make the longest prefix suffix array
    int lps[m];
    computelps(p,m,lps);

    int j = 0;
    for(int i = 0; i < n; i++){

        // in case the char does not match backtrack
        while(j > 0 && p[j]!=t[i]){
            j = lps[j-1];
        }
        // if the char are matching increase the pattern counter
        if(p[j]==t[i]) j++;
        // when the pattern counter equals the pattern length the pattern is present in the text
        if(j == m) {
            index = i - j + 1; //  length of j is actually 1 more than m since j starts from 0
            f++;
            j = 0;
        }
    }

    printf("%d ", index);
    if(f>0) printf("%d ", f);
    printf("\n");
}

int main(){
    char t[1000000], p[100000];
    fgets(t, 1000000, stdin);
    fgets(p, 100000, stdin);

    kmp(t, p);
    return 0;
}