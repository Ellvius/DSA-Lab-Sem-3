#include <stdio.h>
#include <limits.h>

void Floyd_Warshall(int n, int adjList[n][n]){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if (adjList[i][k] != INT_MAX && adjList[k][j] != INT_MAX) {
                    if (adjList[i][j] > adjList[i][k] + adjList[k][j]) {
                        adjList[i][j] = adjList[i][k] + adjList[k][j];
                    }
                }
            }
        }
    }
}

int main(){
    int n, num;
    scanf("%d", &n);

    int adjMatrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &num);
            if(num == -1) num = INT_MAX;
            adjMatrix[i][j] = num;
        }
    }

    Floyd_Warshall(n, adjMatrix);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}