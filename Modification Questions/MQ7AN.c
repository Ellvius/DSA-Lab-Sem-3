#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Edgestruct {
    int u,v,w;
} edge;

void swap(edge *a, edge *b){
    edge temp = *a;
    *a = *b;
    *b = temp;
}

int find(int par[], int i){
    if(par[i] == i) return i;
    return par[i] = find(par, par[i]);
}

void unionset(int u, int v, int size[], int par[]){
    if(u == v) return ;
    if(size[u]>size[v]){
        par[v] = u;
        size[u]+=size[v];
    }
    else {
        par[u] = v;
        size[v]+=size[u];
    }
}

void kruskal(int n, int count, edge list[]){
    int size[n], par[n];
    for(int i = 0; i < n; i++){
        size[i] = 1;
        par[i] = i;
    }
    int min = 99999;
    int total= 0;
    for(int i = 0; i < count; i+=2){
        int u = find(par, list[i].u);
        int v = find(par, list[i].v);
        int wt = list[i].w;

        if(u!=v){
            unionset(u, v, size, par);
            total+=wt;
        }
        else {
            if(wt<min){
                total+=wt;
                min = wt;
            }
        }
    }
    printf("%d\n", total);
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();

    edge edgelist[n*n];
    int count = 0;
    char input[100];
    for(int i = 0; i < n; i++){
        fgets(input, 100, stdin);
        char *token = strtok(input," ");
        token = strtok(NULL, " ") ;
        while(token!= NULL){
            int num = atoi(token);
            edgelist[count].u = i;
            edgelist[count].v = num;
            count++;
            token = strtok(NULL, " ");
        }
    }
    int j = 0;
    for(int i = 0; i < n; i++){
        fgets(input, 100, stdin);
        char *token = strtok(input, " ");
        token = strtok(NULL," ");
        while(token!=NULL){
            int num = atoi(token);
            edgelist[j++].w = num;
            token = strtok(NULL," ");
        }
    }

    for(int i = 0 ; i < count-1; i++){
        for(int j = 0; j < count-i-1; j++){
            if(edgelist[j].w  > edgelist[j+1].w){
                swap(&edgelist[j], &edgelist[j+1]);
            }
        }
    }

    kruskal(n, count, edgelist);
    return 0;
}