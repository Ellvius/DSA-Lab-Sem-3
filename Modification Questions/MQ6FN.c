#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void floydWarshall(int n, int g[n][n]){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(g[i][k]!=9999 && g[k][j]!=9999 && g[i][k]+g[k][j]<g[i][j]){
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int adjlist[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adjlist[i][j] = 9999;
        }
    }

    getchar();
    for(int i = 0; i < n; i++){
        char input[100];
        fgets(input, 100, stdin);
        char *token =  strtok(input, " ");
        token = strtok(NULL, " ");
        while(token!=NULL){
            int num = atoi(token)-1;
            adjlist[i][num] = 1;
            token = strtok(NULL, " ");
        }
    }

    for(int i = 0; i < n; i++){
        char input[100];
        fgets(input, 100, stdin);
        char *token = strtok(input, " ");
        token = strtok(NULL, " ");
        int j = 0;
        while(token!=NULL){
            int num = atoi(token);
            while(j < n && adjlist[i][j]==9999) j++;
            adjlist[i][j] = num;
            token = strtok(NULL, " ");
            j++;
        }
    }

    int source;
    scanf("%d", &source);

    for(int i = 0; i < n; i++){
        adjlist[i][i] = 0;
    }
    floydWarshall(n, adjlist);

    for(int i = 0; i < n; i++){
        printf("%d ", adjlist[source-1][i]);
    }
    printf("\n");
    return 0;
}