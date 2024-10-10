#include<stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void dfsCompNum(int i, int n, int G[n][n], int visited[]){
    visited[i] = 1;
    for(int j = 0; j < n; j++){
        if((G[i][j]==1) && (!visited[j])){
            dfsCompNum(j,n,G,visited);
        }
    }
}

int dfsCompSize(int i, int n, int G[n][n], int visited[]){
    int count = 1;
    visited[i] = 1;
    for(int j = 0; j < n; j++){
        if((G[i][j]==1) && (!visited[j])){
            count+=dfsCompSize(j,n,G,visited);
        }
    }
    return count;
}

void dfsBridge(int i, int n, int disc[], int lowest[], int par[], int G[n][n], int *t, int *bridge){
    disc[i]=lowest[i]=++(*t);

    for(int j=0; j < n; j++){
        if(G[i][j]){
            if(disc[j]==-1){
                par[j]=i;
                dfsBridge(j, n, disc, lowest, par, G, t, bridge);
                lowest[i]=(lowest[i]<lowest[j])? lowest[i] : lowest[j];

                if(disc[i] < lowest[j]) (*bridge)++;
            }
            else if (j != par[i]) {
                lowest[i] = (lowest[i]< disc[j])? lowest[i] : disc[j];
            }
        }
    }
}

void dfsArtPoint(int i, int par, int n, int disc[], int low[], int artpoint[], int G[n][n], int *t){
    disc[i]= low[i] = ++(*t);
    int adj = 0;

    for(int j = 0; j < n; j++){
        if(G[i][j]){
            if(j == par) continue;

            if(disc[j]==-1){
                dfsArtPoint(j, i, n, disc, low, artpoint, G, t);
                low[i] = (low[i]<low[j])? low[i]:low[j];

                if(low[j]>=disc[i] && par != -1){
                    artpoint[i]=1;
                }
                adj++;
            }
            else {
                low[i] = (low[i]<disc[j])?low[i]:disc[j];
            }  
        }
        
    }
    if(adj > 1 && par == -1){
        artpoint[i]=1;
    }
}

void noOfConnectedComponents(int n, int G[n][n]){
    int count = 0;
    int visited[n];

    for(int i = 0; i < n; i++){
        visited[i]=0;
    }

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            dfsCompNum(i, n, G, visited);
            count++;
        }
    }

    printf("%d\n", count);
}

void sizeOfComponents(int n, int G[n][n]){
    int visited[n];
    int components[n];

    for(int i = 0; i < n; i++){
        visited[i]=0;
        components[i]=0;
    }

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            components[i]=dfsCompSize(i, n, G, visited);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-i-1; j++){
            if(components[j]>components[j+1]){
                swap(&components[j], &components[j+1]);
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(components[i]!=0){
            printf("%d ", components[i]);
        }
    }
    printf("\n");
}

void noOfBridges(int n, int G[n][n]){
    int t=0;
    int bridge = 0;
    int discovery[n];
    int lowestdisc[n];
    int parent[n];

    for(int i =  0; i < n; i++){
        discovery[i]= -1;
        lowestdisc[i]=-1;
        parent[i]=-1;
    }

    for(int i = 0; i < n; i++){
        if(discovery[i]==-1){
            dfsBridge(i, n, discovery, lowestdisc, parent, G, &t, &bridge);
        }
    }

    printf("%d\n", bridge);
}

void noOfArticulationPoints(int n, int G[n][n]){
    int t = 0;
    int discovery[n];
    int low[n];
    int artpoint[n];

    for(int i = 0; i < n; i++){
        discovery[i]=-1;
        low[i]=-1;
        artpoint[i]=0;
    }

    for(int i = 0; i < n; i++){
        if(discovery[i]==-1){
            dfsArtPoint(i, -1, n, discovery, low, artpoint, G, &t);
        }
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        if(artpoint[i]) count++;
    }

    printf("%d\n", count);
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
            noOfConnectedComponents(n, G);
        }
        else if (op == 'b'){
            sizeOfComponents(n, G);
        }
        else if (op == 'c'){
            noOfBridges(n, G);
        }
        else if (op == 'd'){
            noOfArticulationPoints(n, G);
        }
        else if (op == 'x'){
            break;
        }
    }
    return 0;
}