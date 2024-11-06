#include<stdio.h>

void addRoad(int n, int g[n][n], int u, int v){
    if(g[u][v]==0) {
        g[u][v] = 1;
        g[v][u] = 1;
    }
    else printf("-1\n");
}

void displayRoad(int n, int g[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}

int dfs(int i, int par, int vis[], int n, int g[n][n], int d){
    if(i == d){
        return 1;
    }

    vis[i] = 1;
    int count = 0;

    for(int v = 0; v < n; v++){
        if(g[i][v] && !vis[v] && par!=v){
            count+=dfs(v, i, vis, n, g, d);
        }
    }
    vis[i] = 0;
    return count;
}

void uniquePath(int n, int g[n][n], int u, int v){
    int visited[n], path[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
        path[i] = 0;
    }
    int count = dfs(u, -1, visited, n, g, v);
    if(count==1){
        printf("yes\n");
    }
    else {
        printf("no\n");
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int roads[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            roads[i][j] = 0;
        }
    }

    char op;
    while(1){
        scanf("%c", &op);
        if(op == 'a'){
            int u, v;
            scanf("%d%d", &u,&v);
            addRoad(n, roads, u-1, v-1);
        }
        else if(op == 'b'){
            displayRoad(n, roads);
        }
        else if(op == 'c'){
            int u, v;
            scanf("%d%d", &u, &v);
            uniquePath(n, roads, u-1, v-1);
        }
        else if (op == 'g'){
            break;
        }
    }

    return 0;
}