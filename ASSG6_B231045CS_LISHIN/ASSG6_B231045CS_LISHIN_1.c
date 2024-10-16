#include <stdio.h>
#include <string.h>

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

    /* To print the input matrix */

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}