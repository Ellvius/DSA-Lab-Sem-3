#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct graphnode {
    int vertex;
    struct graphnode *next;
} node;

typedef struct graphds {
	int num;
	node **adjList;
} Graph;

node *createnode(int n){
	node *newNode = (node *)malloc(sizeof(node));
	newNode->vertex = n;
	newNode->next = NULL;
	return newNode;
}

Graph *creategraph(int n){
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->num = n;
	graph->adjList = malloc(n * sizeof(node *));
	for(int i = 0; i < n; i++){
		graph->adjList[i] = NULL;
	}
	return graph;
}

Graph* transposeGraph(Graph *graph) {
    int n = graph->num;
    Graph *transpose = creategraph(n);  
    for (int u = 0; u < n; u++) {
        node *temp = graph->adjList[u];
        while (temp) {
            int v = temp->vertex;
            node *newNode = createnode(u);
            newNode->next = transpose->adjList[v];
            transpose->adjList[v] = newNode;  // Add the reverse edge to the transpose
            temp = temp->next;
        }
    }
    return transpose;
}

int dfsDAG(Graph *graph, int v, int visited[], int rec[]){
    visited[v] = 1;
    rec[v] = 1;  

    node *temp = graph->adjList[v];
    while(temp){
        int u = temp->vertex;
        if(!visited[u]){
            if(!dfsDAG(graph, u, visited, rec)){
                printf("%d cycle", u);
                return 0; 
            }
        }
        else if(rec[u]){
            return 0; 
        }
        temp = temp->next;
    }
    rec[v] = 0; 
    return 1;  
}

void isDAG(int n, Graph *graph){
    int visited[n];
    int rec[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
        rec[i] = 0;
    }
    
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            if(!dfsDAG(graph, i, visited, rec)){
                printf("-1\n"); 
                return;
            }
        }
    }
    printf("1\n"); 
} 

void dfs(Graph *graph, int v, int visited[], int stack[], int *index){
    visited[v] = 1;

    node *temp = graph->adjList[v];
    while(temp){
        int u = temp->vertex;
        if(!visited[u]){
            dfs(graph, u, visited, stack, index);
        }
        temp = temp->next;
    }
    stack[(*index)++]=v;
}

void dfs2(Graph *graph, int v, int visited[]){
    visited[v] = 1;

    node *temp = graph->adjList[v];
    while(temp){
        int u = temp->vertex;
        if(!visited[u]){
            dfs2(graph, u, visited);
        }
        temp = temp->next;
    }
}

void countStronglyConnectedComponents(int n, Graph *graph){
    int visited[n];
    int stack[n];
    int index = 0;
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            dfs(graph, i, visited, stack, &index);
        }
    }

    Graph *transgraph = transposeGraph(graph);

    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    int count = 0;
    while(index > 0){
        int v = stack[--index];
        if(!visited[v]){
            dfs2(transgraph, v, visited);  
            count++;
        }
    }
    printf("%d\n", count);  
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	getchar();

	Graph *graph = creategraph(n);

	char input[100];
	for(int i = 0; i < n; i++) {
        fgets(input, 100, stdin);  
        char *token = strtok(input, " ");
        token = strtok(NULL, " ");
        while(token != NULL) {
            int num = atoi(token) - 1; 
            if(num >= 0) {
                node *newNode = createnode(num);  
                newNode->next = graph->adjList[i];
                graph->adjList[i] = newNode;
            }
            token = strtok(NULL, " ");
        }
    }

	char op;
	while(1){
		scanf(" %c", &op);

		if(op == 'a') {
			isDAG(n, graph);  
		}
		else if (op == 'b') {
			countStronglyConnectedComponents(n, graph); 
		}
		else if (op == 'x') {
			break;  
		}
	}

	return 0;
}