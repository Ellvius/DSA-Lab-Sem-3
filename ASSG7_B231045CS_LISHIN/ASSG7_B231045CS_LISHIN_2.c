/* Minimum Spanning Tree (MST) of a connected, simple undirected graph G using Kruskal’s algorithm */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Edge {
    int s, d, w;
} edge;

int findPar(int par[], int u){
    if(par[u] == u) return u;
    return par[u] = findPar(par, par[u]);
}

void unionbysize(int u, int v, int par[], int size[]){
    int pu = findPar(par, u);
    int pv = findPar(par, v);

    if(pu == pv) return ;

    if(size[pu] < size[pv]){
        par[pu] = pv;
        size[pv]+=size[pu];
    }
    else {
        par[pv] = pu;
        size[pu]+=size[pv];
    }
}

void Kruskal(int n, int count, edge EdgeList[]){
    int par[n], size[n];
    for(int i = 0; i < n; i++){
        par[i] = i;
        size[i] = 1;
    }

    int totalWeight = 0;

    for(int i = 0; i < count; i++){
        int u = EdgeList[i].s;
        int v = EdgeList[i].d;
        int weight = EdgeList[i].w;
        int pu = findPar(par, u);
        int pv = findPar(par, v);

        if(pu != pv){
            unionbysize(u, v, par, size);
            totalWeight += weight;
        }
    }

    printf("%d\n", totalWeight);
}

void swap(edge *a, edge *b){
    edge temp = *a;
    *a = *b;
    *b = temp;
}

void Sort(edge EdgeList[], int count){
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (EdgeList[j].w > EdgeList[j + 1].w) {
                swap(&EdgeList[j], &EdgeList[j+1]);
            }
        }
    }
}

void EdgeArray(int n, int g[n][n], edge EdgeList[], int *count){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(g[i][j]!=0){
                EdgeList[*count].s = i;
                EdgeList[*count].d = j;
                EdgeList[*count].w = g[i][j];
                (*count)++;
            }
        }
    }
    Sort(EdgeList, *count);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();

    int adjList[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adjList[i][j] = 0;
        }
    }

    char input[100];
	for(int i = 0; i < n; i++) {
        fgets(input, 100, stdin);  
        char *token = strtok(input, " ");
        token = strtok(NULL, " ");
        while(token != NULL) {
            int num = atoi(token) ; 
            if(num >= 0) {
                adjList[i][num] = 1;
            }
            token = strtok(NULL, " ");
        }
    }

    char weight[100];
    for(int i = 0; i < n; i++) {
        int j = 0;
        fgets(weight, 100, stdin);  
        char *token = strtok(weight," ");
        token = strtok(NULL," ");
        while(token != NULL) {
            int num = atoi(token); 
            if(num >= 0) {
                while(adjList[i][j]==0 && j < n){
                    j++;
                }
                adjList[i][j] = num;
                j++;
            }
            token = strtok(NULL, " ");
        }
    }
    
    int edgecount = 0;
    edge EdgeList[n*(n-1)/2];

    EdgeArray(n, adjList, EdgeList, &edgecount);

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%d ", adjList[i][j]);
    //     }
    //     printf("\n");
    // }

    Kruskal(n, edgecount, EdgeList);

    return 0;
}
