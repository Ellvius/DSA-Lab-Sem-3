/* Minimum Spanning Tree of a connected, simple undirected graph G using Prim's Algorithm */ 
#include <stdio.h>
#include <limits.h>

int min(int n, int mst[], int w[]){
    int min = INT_MAX;
    int index = -1;

    for(int i = 0; i < n; i++){
        if(!mst[i] && w[i]<min){
            min = w[i];
            index = i;
        }
    }
    return index;
}

int Sequence(int n, int g[n][n], int start){
    int mst[n], w[n], par[n];
    for(int i = 0; i < n; i++){
        mst[i] = 0;
        w[i] = INT_MAX;
        par[n]= -1;
    }
    w[start] = 0;

    for(int i = 0; i < n; i++){
        int cur = min(n, mst, w);
        if(cur == -1) break;
        mst[cur] = 1;

        if(cur!=start){
            printf("%d %d (%d) ", par[cur], cur, w[cur]);
        }

        for(int v = 0; v < n; v++){
            if(g[cur][v]!=0 && !mst[v]){
                if(w[v] > g[cur][v]){
                    w[v] = g[cur][v];
                    par[v] = cur;
                }
            }
        }
    }
    printf("\n");

    int total = 0;
    for(int i = 0; i < n; i++){
        total+=w[i];
    }
    return total;
}

void TotalWeight(int n, int g[n][n], int weight){
    printf("%d\n", weight);
}

int main(){
    int n;
    scanf("%d", &n);
    int adjMatrix[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&adjMatrix[i][j]);
        }
    }
    int weight  = 0;
    char op;
    while(1){
        scanf("%c",&op);
        if(op == 's'){
            int v;
            scanf("%d", &v);
            weight = Sequence(n, adjMatrix, v);
        }
        else if (op == 'b'){
            TotalWeight(n, adjMatrix, weight);
        }
        else if (op == 'e'){
            break;
        }
    }
    return 0;
}