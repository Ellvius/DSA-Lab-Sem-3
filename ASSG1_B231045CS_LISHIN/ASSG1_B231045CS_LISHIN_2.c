#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bst {
    int modelNumber;
    char modelName[50];
    int Price;
    struct bst *left, *right, *parent;
} node;

node *Create_Node(int model_number, char model_name[], int price) {
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->modelNumber = model_number;
    strcpy(newNode->modelName, model_name);
    newNode->Price = price;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

node *Add(node *T, node *x) {
    if (T == NULL) {
        return x;
    }

    node *temp = T;
    node *parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (x->modelNumber < temp->modelNumber) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    if (x->modelNumber < parent->modelNumber) {
        parent->left = x;
    } else {
        parent->right = x;
    }
    x->parent = parent;

    return T;
}

node *Search(node *T, int model_number) {
    if (T == NULL) {
        return NULL;
    }

    if (T->modelNumber == model_number) {
        return T;
    } else if (T->modelNumber > model_number) {
        return Search(T->left, model_number);
    } else {
        return Search(T->right, model_number);
    }
}

node *Delete(node *T, node *x) {
    if (T == NULL || x == NULL) {
        return T;
    }

    if (T->modelNumber > x->modelNumber) {
        T->left = Delete(T->left, x);
    } else if (T->modelNumber < x->modelNumber) {
        T->right = Delete(T->right, x);
    } else {
        //  No child
        if (T->left == NULL && T->right == NULL) {
            free(T);
            return NULL;
        }
        //  One child
        else if (T->left == NULL) {
            node *temp = T->right;
            if(T->parent != NULL){
                if(T->parent->left == T){
                    T->parent->left = temp;
                }
                else {
                    T->parent->right = temp;
                }
                temp->parent = T->parent;
            }
            free(T);
            return temp;
        } else if (T->right == NULL) {
            node *temp = T->left;
            if(T->parent != NULL){
                if(T->parent->left == T){
                    T->parent->left = temp;
                }
                else {
                    T->parent->right = temp;
                }
                temp->parent = T->parent;
            }
            free(T);
            return temp;
        }
        // Two children
        else {
            node *smallest = T->right;
            while (smallest->left != NULL) {
                smallest = smallest->left;
            }
            T->modelNumber = smallest->modelNumber;
            strcpy(T->modelName, smallest->modelName);
            T->Price = smallest->Price;
            T->right = Delete(T->right, smallest);
        }
    }
    return T;
}

void Inorder(node *T) {
    if (T == NULL) return;

    Inorder(T->left);
    printf("%d %s %d\n", T->modelNumber, T->modelName, T->Price);
    Inorder(T->right);
}

void Preorder(node *T) {
    if (T == NULL) return;

    printf("%d %s %d\n", T->modelNumber, T->modelName, T->Price);
    Preorder(T->left);
    Preorder(T->right);
}

void Postorder(node *T) {
    if (T == NULL) return;

    Postorder(T->left);
    Postorder(T->right);
    printf("%d %s %d\n", T->modelNumber, T->modelName, T->Price);
}

node *Modify(node *T, int model_number, int new_price) {
    node *targetNode = Search(T, model_number);
    if (targetNode == NULL) {
        return NULL;
    }
    targetNode->Price = new_price;
    return targetNode;
}

int main() {
    node *T = NULL;
    node *x = NULL;
    char op;
    int carModelNumber, carPrice;
    char carModelName[50];

    while (1) {
        scanf(" %c", &op);
        if (op == 'a') {
            scanf("%d %s %d", &carModelNumber, carModelName, &carPrice);
            x = Create_Node(carModelNumber, carModelName, carPrice);
            T = Add(T, x);
        } else if (op == 'd') {
            scanf("%d", &carModelNumber);
            x = Search(T, carModelNumber);
            if (x == NULL) {
                printf("-1\n");
            } else {
                printf("%d %s %d\n", x->modelNumber, x->modelName, x->Price);
                T = Delete(T, x);
            }
        } else if (op == 's') {
            scanf("%d", &carModelNumber);
            x = Search(T, carModelNumber);
            if (x == NULL) {
                printf("-1\n");
            } else {
                printf("%d %s %d\n", x->modelNumber, x->modelName, x->Price);
            }
        } else if (op == 'i') {
            Inorder(T);
        } else if (op == 'p') {
            Preorder(T);
        } else if (op == 't') {
            Postorder(T);
        } else if (op == 'm') {
            scanf("%d %d", &carModelNumber, &carPrice);
            x = Modify(T, carModelNumber, carPrice);
            if (x == NULL) {
                printf("-1\n");
            } else {
                printf("%d %s %d\n", x->modelNumber, x->modelName, x->Price);
            }
        } else if (op == 'e') {
            break;
        }
    }

    return 0;
}
