#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int findmin(int n, int visited[], int distance[]){
    int min = INT_MAX;
    int index = -1;
    for(int i = 0; i < n; i++){
        if(!visited[i] && (distance[i]<=min)){
            min = distance[i];
            index = i;
        }
    }
    return index;
}

int dijkstra(int n, int adj[n][n], int source){
    int distance[n], visited[n];
    for(int i = 0; i < n; i++){
        distance[i] = (i==source) ? 0 : INT_MAX;
        visited[i] = 0;
    }

    for(int i = 0; i < n - 1; i++){
        int currentvertex = findmin(n, visited, distance);
        if(currentvertex == -1) break;
        visited[currentvertex] = 1;

        for(int v = 0; v < n; v++){
            if(adj[currentvertex][v]!=0 && (!visited[v]) && distance[currentvertex]!=INT_MAX){
                int path = adj[currentvertex][v] + distance[currentvertex];
                if(distance[v] > path ){
                    distance[v] = path;
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(distance[i] == INT_MAX) printf("INF ");
        else printf("%d ", distance[i]);
    }
    printf("\n");
}


int main(){
    int n;
    scanf("%d", &n);
    int adj[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
    }
    getchar();

    char adjList[100];
	for(int i = 0; i < n; i++) {
        fgets(adjList, 100, stdin);  
        char *token = strtok(adjList, " ");
        int label = atoi(token) - 1;
        token = strtok(NULL, " ");
        while(token != NULL) {
            int num = atoi(token) - 1; 
            if(num >= 0) {
                adj[label][num] = 1;
            }
            token = strtok(NULL, " ");
        }
    }

    char weight[100];
    for(int i = 0; i < n; i++) {
        int j = 0;
        fgets(adjList, 100, stdin);  
        char *token = strtok(adjList, " ");
        int label = atoi(token) - 1;
        token = strtok(NULL, " ");
        while(token != NULL) {
            int num = atoi(token); 
            if(num >= 0) {
                while(adj[label][j]==0 && j < n){
                    j++;
                }
                adj[label][j] = num;
                j++;
            }
            token = strtok(NULL, " ");
        }
    }
    int source;
    scanf("%d", &source);

    dijkstra(n, adj, source - 1);
    
    return 0;
}