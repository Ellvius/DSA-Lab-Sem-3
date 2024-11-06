#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int min(int n, int vis[], int dis[]){
    int min  = 9999;
    int index = -1;
    for(int i = 0; i < n; i++){
        if(!vis[i] && dis[i]<=min){
            min = dis[i];
            index = i;
        }
    }
    return index;
}

void djikstra(int source, int n, int g[n][n]){
    int vis[n], dis[n], path[n];
    for(int i = 0; i < n; i++){
        vis[i] = 0;
        dis[i] = 9999;
        path[i] = -1;
    }
    dis[source] = 0;

    for(int i = 0; i < n; i++){
        int cur = min(n, vis, dis);
        if(cur == -1 ) break;
        vis[cur] = 1;

        for(int v = 0; v < n; v++){
            if(g[cur][v]!=0 && !vis[v] && dis[cur]!=9999){
                int path = g[cur][v]+dis[cur];
                if(dis[v]>path) dis[v] = path;
            }
        }
    }

    for(int i = 0 ; i < n; i++){
        printf("%d ", dis[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    int adjlist[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adjlist[i][j] = 0;
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
            while(j < n && adjlist[i][j]==0) j++;
            adjlist[i][j] = num;
            token = strtok(NULL, " ");
            j++;
        }
    }

    int source;
    scanf("%d", &source);

    djikstra(source-1, n, adjlist);
    return 0;
}