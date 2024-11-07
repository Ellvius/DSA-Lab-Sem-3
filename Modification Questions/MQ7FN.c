#include<stdio.h>

int min(int n, int vis[], int dist[]){
    int min = 9999;
    int index = -1;
    for(int i = 0; i < n; i++){
        if(!vis[i] && dist[i]<=min){
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void prims(int n, int g[n][n], int source, int budget){
    int vis[n], dist[n];
    for(int i = 0; i < n; i++){
        vis[i] = 0;
        dist[i] = 9999;
    }

    dist[source]=0;
    int total = 0;
    for(int i = 0 ; i < n; i++){
        int cur = min(n, vis, dist);
        if(cur == -1) break;
        vis[cur]= 1;
        total+=dist[cur];
        
        for(int v = 0; v < n; v++){
            if(g[cur][v]!=0 && !vis[v]){
                if(dist[v]> g[cur][v]){
                    dist[v] = g[cur][v];
                }
            }
        }
    }
    printf("%d ", total);
    if(total>budget) printf("yes\n");
    else printf("no\n");
}

int main(){
    int n, budget, source;
    scanf("%d%d%d", &n,&budget,&source);

    int matrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    char op;
    while (1)
    {
        scanf("%c", &op);
        if(op == 'c'){
            prims(n, matrix, source, budget);
        }
        else if (op == 'e'){
            break;
        }
    }
    
    return 0;
}