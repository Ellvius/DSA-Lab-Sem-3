#include<stdio.h>

void floydWarshall(int n, int g[n][n]){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(g[i][k]!=9999 && g[k][j]!=9999 && g[i][k]+g[k][j] < g[i][j]){
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int adjmatrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adjmatrix[i][j]);
        }
    }

    floydWarshall(n, adjmatrix);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", adjmatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}