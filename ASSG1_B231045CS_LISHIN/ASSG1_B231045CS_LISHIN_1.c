#include<stdio.h>
#include<stdlib.h>

/*     DECLARATIONS    */
typedef struct bt {
    int data;
    struct bt *left, *right;
} tree;

typedef struct linkedlist {
    tree *tnode;
    struct linkedlist *next;
} node;

typedef struct queue {
    node * front, *rear;
} Q;


/*     QUEUE     */
node* createQNode(tree *newtnode) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->tnode = newtnode;
    newNode->next = NULL;
    return newNode;
}

Q* createQueue() {
    Q* q = (Q*)malloc(sizeof(Q));
    if (!q) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Q* q, tree *tnode) {
    node* newNode = createQNode(tnode);
    if (!newNode) return;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

tree* dequeue(Q* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }

    node* temp = q->front;
    tree* data = temp->tnode;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int isEmpty(Q* q) {
    return q->front == NULL;
}

int length(Q *q){
    int length = 0;

    node *temp = q->front;
    while(temp!= NULL){
        length++;
        temp = temp->next;
    }

    return length;
}

int max(int a, int b){
    if(a>b) return a;
    return b;
}

/* LINKED LIST */
node *createLLnode(tree *newtnode){
    node *newNode = (node *)malloc(sizeof(node));
    if(!newNode){
        printf("Error allocating memory\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->tnode = newtnode;
    return newNode;
}

node *inserthead(node *head, tree *trnode){
    node *newNode = createLLnode(trnode);
    if(!newNode) return NULL;

    newNode->next = head;
    head = newNode;
    return head;
}

node *inserttail(node *head, tree *trnode){
    node *newNode = createLLnode(trnode);
    if(!newNode) return NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    node *temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

void printLinkedList(node *head){
    if(head == NULL) return;

    node *temp = head;
    while(temp != NULL){
        printf("%d ", temp->tnode->data);
        temp = temp->next;
    }

}

void printMaxLinkedList(node *head){
    if (head == NULL) return;

    int max = -1;
    node *temp = head;
    while (temp != NULL) {
        if (temp->tnode->data > max) {
            max = temp->tnode->data;
        }
        temp = temp->next;
    }
    printf("%d ", max);
}


/*   BINARY TREE     */
tree *createTNode(int num){
   tree *tnode = (tree *)malloc(sizeof(tree));
   if(tnode == NULL){
        printf("Memory allocation failed\n");
        return NULL;
   }

   tnode->data = num;
   tnode->left = NULL;
   tnode->right = NULL;

   return tnode;
}

tree *CreateTree(int in[], int pre[], int start, int end, int *pos){
    int index;

    // base case
    if(start>end) return NULL;

    // create and insert the node in to the binary tree
    tree *newNode = createTNode(pre[*pos]);
    (*pos)++;
    if(start == end) return newNode;

    // find the position of root element in inorder traversal
    for(int i = start; i<=end; i++){
        if(in[i] == newNode->data){
            index = i;
            break;
        } 
    }

    // call subsequently for left and right subtree
    newNode->left = CreateTree(in, pre, start, index-1, pos );
    newNode->right = CreateTree(in, pre, index+1, end, pos );

    return newNode;
}

void PostOrder(tree *T){
    if(T!= NULL){
        PostOrder(T->left);
        PostOrder(T->right);
        printf("%d ", T->data);
    }
}



/* ZIG ZAG TRAVERSAL */
void ZIG_ZAG(tree *T){
   if(T == NULL) return;

   int levelsize, level=0;
   Q *q = createQueue();
   enqueue(q, T);

   node *treelist = NULL;

   while (!isEmpty(q)){
        levelsize = length(q);
        while(levelsize>0){
            tree *current = dequeue(q);
            if(level%2 == 0){
                treelist = inserthead(treelist, current);            
            } else {
                treelist = inserttail(treelist, current);
            }

            if(current->left != NULL) enqueue(q,current->left);

            if(current->right != NULL) enqueue(q, current->right);
            levelsize--;
        }
        level++;
        printLinkedList(treelist);
        treelist = NULL;
    }
        
    free(q);
}



/*  MAX NODE AT EACH LEVEL */
void LevelMax(tree *T){
    if(T == NULL) return;

   int levelsize = 0;
   Q *q = createQueue();
   enqueue(q, T);

   node *treelist = NULL;

   while (!isEmpty(q)){
        levelsize = length(q);
        while(levelsize>0){
            tree *current = dequeue(q);
            treelist = inserthead(treelist, current);

            if(current->left != NULL) enqueue(q,current->left);

            if(current->right != NULL) enqueue(q, current->right);
            levelsize--;
        }
        printMaxLinkedList(treelist);
        treelist = NULL;
    }
        
    free(q);
}



/* DIAMETER OF THE BINARY TREE */
int height(tree *T){
    if(T == NULL) return 0;
    return 1 + max( height(T->left), height(T->right));
}

int maxDiameter(tree *T){
    if(T==NULL) return 0;

    int lheight = height(T->left);
    int rheight = height(T->right);
    int diameter = lheight + rheight + 1;

    int ldiameter = maxDiameter(T->left);
    int rdiameter = maxDiameter(T->right);

    return max(diameter, max(ldiameter, rdiameter));
}

void Diameter(tree *T){
    int diameter = maxDiameter(T);
    printf("%d\n", diameter);
}



/*  RIGHT LEAF SUM  */
void RightLeafSum(tree *T){
    if(T == NULL) return;

    int levelsize = 0, sum = 0;
    Q *q = createQueue();
    enqueue(q, T);

    while (!isEmpty(q)){
        levelsize = length(q);
        while(levelsize>0){
            tree *current = dequeue(q);

            if(current->left != NULL){
                enqueue(q,current->left);
            } 

            if(current->right != NULL) {
                if(current->right->right == NULL && current->right->left == NULL){
                    sum = sum + current->right->data;
                }
                enqueue(q, current->right);
            }
            levelsize--;
        }
    }
    printf("%d\n", sum) ;
    free(q);
}



int main(){
    // number of nodes
    int n; 
    scanf("%d", &n);
    if(n>1000000 || n<1){
        printf("Enter values in range [1, 10^6]\n");
        return 0;
    }

    // declarations
    int inorder[n], preorder[n], pos;
    char op;
    tree *T;
    pos = 0;

    // reading values
    for(int i=0; i<n; i++){
        scanf("%d", &inorder[i]);
        if(inorder[i]>1000000 || inorder[i]<1){
            printf("Enter values in range [1, 10^6]\n");
            break;
        }
    }
 
    for(int i=0; i<n; i++){
        scanf("%d", &preorder[i]);
        if(preorder[i]>1000000 || preorder[i]<1){
            printf("Enter values in range [1, 10^6]\n");
            break;
        }
    }

    // create a binary tree with the given inorder and preorder traversal
    T = CreateTree(inorder, preorder, 0, n-1, &pos);

    // Repeated read character and perform the tasks
    while (1){
        scanf(" %c", &op);

        if(op == 'p'){
            PostOrder(T);
            printf("\n");
        }
        else if(op == 'z'){
            ZIG_ZAG(T);
            printf("\n");
        }
        else if(op == 'm'){
            LevelMax(T);
            printf("\n");
        }
        else if(op == 'd'){
            Diameter(T);
        }
        else if(op == 's'){
            RightLeafSum(T);
        }
        else if(op == 'e'){
            break;
        }
    }    

    return 0;
}