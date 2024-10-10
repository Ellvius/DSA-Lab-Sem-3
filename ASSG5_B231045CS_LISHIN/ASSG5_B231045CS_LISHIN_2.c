#include<stdio.h>

int bfsBipartite(int i, int n, int G[n][n], int visited[]){
    int q[n], front = 0, rear=0;
    visited[i]=1;
    q[rear++]=i;

    while(front < rear){
        int s = q[front++];

        for(int j = 0; j < n; j++){
            if(visited[j]==0 && G[s][j]){
                visited[j]=(visited[s]==1)?2:1;
                q[rear++]=j;
            }
            else if(G[s][j]){
                if(visited[j]==visited[s]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int bfsCycle(int i, int n, int G[n][n], int visited[]){
    int q[n], front = 0, rear=0;
    visited[i]=1;
    q[rear++]=i;

    while(front < rear){
        int s = q[front++];

        for(int j = 0; j < n; j++){
            if(visited[j]==0 && G[s][j]){
                visited[j]=1;
                q[rear++]=j;
            }
            else if(G[s][j]){
                return 1;
            }
        }
    }
    return 0;
}

void isBipartite(int n, int G[n][n]){
    int visited[n];
    for(int j = 0; j< n; j++){
        visited[j]=0;
    }

    for(int i = 0; i < n; i++){
        if(visited[i]==0){
            if(!bfsBipartite(i, n, G, visited)){
                printf("-1\n");
                return;
            }
        }
    }
    printf("1\n");
}

void hasCycle(int n, int G[n][n]){
    int visited[n];
    for(int j = 0; j< n; j++){
        visited[j]=0;
    }

    for(int i = 0; i < n; i++){
        if(visited[i]==0){
            if(bfsCycle(i, n, G, visited)){
                printf("1\n");
                return;
            }
        }
    }
    printf("-1\n");
}

void isTree(int n, int G[n][n]){
    int visited[n];
    for(int j = 0; j< n; j++){
        visited[j]=0;
    }

    for(int i = 0; i < n; i++){
        if(visited[i]==0){
            if(bfsCycle(i, n, G, visited)){
                printf("-1\n");
                return;
            }
        }
    }
    
    for(int i = 0; i < n; i++){
        if(!visited[i]) printf("1\n");
        else printf("-1\n");
    }
}

int main(){
    int n;
    scanf("%d", &n);
    
    int G[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n ; j++){
            scanf("%d", &G[i][j]);
        }
    }

    char op;    
    while(1){
        scanf("%c", &op);

        if(op == 'a'){
            isBipartite(n, G);
        }
        else if (op == 'b'){
            hasCycle(n, G);
        }
        else if (op == 'c'){
            isTree(n, G);
        }
        else if (op == 'x'){
            break;
        }
    }
    return 0;
}