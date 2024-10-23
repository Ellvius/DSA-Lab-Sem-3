#include<stdio.h>
#include<stdlib.h>

typedef struct task_list {
    int id;
    int ur;
} task;

void swap(task *a, task *b){
    task temp = *a;
    *a = *b;
    *b = temp;
}

void heapifydown(task h[], int i, int *size){
    int l = 2*i + 1;
    int r = 2*i + 2;
    int sm = i;

    if(l<*size && h[l].ur < h[sm].ur){
        sm = l;
    }
    if(r < *size && h[r].ur < h[sm].ur){
        sm = r;
    }

    if(sm!=i){
        swap(&h[sm], &h[i]);
        heapifydown(h,sm,size);
    }
}

void heapifyup(task h[], int i, int *size){
    int par = (i-1)/2;

    if(i>=0 &&  h[par].ur >h[i].ur){
        swap(&h[par], &h[i]);
        heapifyup(h, par, size);
    }
}

void Addtask(task h[], int id, int urg, int *size){
    h[*size].id = id;
    h[*size].ur = urg;

    (*size)++;

    heapifyup(h,(*size)-1,size);
}

void Updateurgency(task h[], int id, int newur, int *size){
    int sid = -1;
    for(int i = 0; i < *size; i++){
        if(h[i].id == id){
            sid = i;
            break;
        }
    }
    if(sid == -1){
        printf("-1\n");
        return;
    }
    printf("%d\n", h[sid].id);
    int old_ur = h[sid].ur ;
    h[sid].ur = newur;

    if(newur < old_ur){
        heapifyup(h, sid,size);
    }
    else {
        heapifydown(h, sid, size);
    }
}

void DeleteUrgency(task h[], int *size){
    printf("%d\n", h[0].id);

    swap(&h[0], &h[*size - 1]);
    (*size)--;

    heapifydown(h, 0, size);
}

void display(task h[], int size){
    if(size == 0){
        printf("-1\n");
        return;
    }
    for(int i = 0; i < size; i++){
        printf("%d ", h[i].id);
    }
    printf("\n");
}

void kth(task h[], int k, int size){
    int s = (1 << (k-1))-1;  
    int e = (1 << (k))-2;

    int min = s;
    for(int i = s ; i <=e; i++){
        if(h[i].ur<h[min].ur){
            min = i;
        }
    }
    printf("%d\n", h[min].id);
}

int main(){
    int id;
    int ur; 
    task h[1000];
    int size = 0;

    char op;
    while(1){
        scanf(" %c", &op);
        if(op=='i'){
            scanf("%d %d", &id, &ur);
            Addtask(h,id,ur, &size);
        }
        else if(op == 'u'){
            scanf("%d %d", &id, &ur);
            Updateurgency(h,id,ur, &size);
        }
        else if(op == 'e'){
            DeleteUrgency(h, &size);
        }
        else if(op == 'd'){
            display(h, size);
        }
        else if(op == 'p'){
            scanf("%d", &id);
            kth(h,id, size);
        }
        else if (op == 'q'){
            break;
        }
    }

    return 0;
}