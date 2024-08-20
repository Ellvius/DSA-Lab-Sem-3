#include<stdio.h>
#include <stdlib.h>

/* Insert a sequence of keys [n1, n2, ..., nk] into the AVL tree T. Perform necessary rotations to maintain AVL properties after each insertion. After all insertions, print the paranthesis representation of resulting AVL tree.*/
AVL_SeqInsert(T, [n1, n2, ..., nk]);

/* Delete all keys in the AVL tree T that are within the range [n1, n2] (inclusive). Perform necessary rotations to maintain AVL properties after each deletion. After performing all deletions, print the total number of nodes deleted and preorder
traversal of the tree T after all deletions. */
AVL_RangeDelete(T, n1, n2);

/* For a given key n, find its inorder successor in T. Print the path from the root to the inorder successor (including the successor itself). If n does not exist or has no successor, return the height of T.*/
AVL_SuccessorPath(T, n);

/*  For a given key n, print the sum of all keys in the subtree rooted at n and the parenthesis representation of the corresponding subtree rooted at n. If n is not present in T, print −1.*/
AVL_SubtreeSum(T, n);

/* Given a key n, find and print the closest key in T (the key with the minimum absolute difference from n). If there are multiple such keys present, print the smallest among them. If n is not found in T, or the closest key of n is not present (T has only one node and it is n), then print −1.
Note: closest key of n cannot be itself */
AVL_FindClosest(T, n);


int main(){
    char op;
    int n1, n2, n;
    
    while(1){
        scanf(" %c", &op);
        if(op == 'a'){
            AVL_SeqInsert(T, [n1, n2, ..., nk]);
        }
        else if(op == 'b'){
            scanf("%d", &n1);
            scanf("%d", &n2);
            AVL_RangeDelete(T, n1, n2);
        }
        else if(op == 'c'){
            scanf("%d", &n);
            AVL_SuccessorPath(T, n);
        }
        else if(op == 'd'){
            scanf("%d", &n);
            AVL_SubtreeSum(T, n);
        }
        else if(op == 'e'){
            scanf("%d", &n);
            AVL_FindClosest(T, n);
        }
        else if(op == 'g'){
            break;
        }
    }

    return 0;
}