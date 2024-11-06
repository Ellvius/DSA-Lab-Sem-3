#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void dfs(int u, int n, int g[n][n], int vis[]){
    vis[u] = 1;

    for(int v = 0; v < n; v++){
        if(g[u][v] && !vis[v]){
            dfs(v, n, g, vis);
        }
    }
}

void nc(int n, int g[n][n]){
    int vis[n];
    for(int i = 0; i < n; i++){
        vis[i] = 0;
    }
    int count = 0;
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            dfs(i, n, g, vis);
            count++;
        }
    }
    printf("%d\n", count);
}

int main(){
    int n, e;
    scanf("%d%d", &n, &e);
    int red[n][n], green[n][n], blue[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            red[i][j] = 0;
            green[i][j] = 0;
            blue[i][j] = 0;
        }
    }
    getchar();

    for(int i = 0; i < n; i++){
        char input[100];
        fgets(input, 100, stdin);
        char *token = strtok(input, " ");
        token = strtok(NULL, " ");
        while(token!=NULL){
            char *color = token;
            token = strtok(NULL, " ");
            int num = atoi(token) - 1;
            if(strcmp(color, "R")==0){
                red[i][num] = 1;
            }
            else if(strcmp(color, "G")==0){
                green[i][num] = 1;
            }
            else if(strcmp(color, "B")==0){
                blue[i][num] = 1;
            }
            token = strtok(NULL, " ");
        }
    }
    nc(n, red);
    nc(n, green);
    nc(n, blue);
    return 0;
}