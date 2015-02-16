#include <stdio.h>

#define NUM     10
#define MAX     1024

void print_tree(int tree[], int n)
{
    int i;

    for (i = 0; i < n; i++) 
        printf("%d ", tree[i]);
    printf("\n");
}

void insert_tree(int tree[], int n, int root)
{
    int left, right;

    if (tree[root] == -1) {
        printf("put %d to node [%d]\n", n, root);
        tree[root] = n;
        return;
    }

    left = 2 * root + 1;
    right = 2 * root + 2;

    // go to left child
    if (n <= tree[root])
        insert_tree(tree, n, left);
    // go to right child
    else
        insert_tree(tree, n, right);
}

int main()
{
    int n[NUM] = {6, 5, 23, 81, 9, 6, 32, 75, 60, 1};
    //int n[NUM] = {7, 4, 2, 25, 3, 10};
    int tree[MAX];
    int i;

    // initialize binary search tree
    for (i = 0; i < MAX; i++)
        tree[i] = -1;

    for (i = 0; i < NUM; i++)
        insert_tree(tree, n[i], 0);
    print_tree(tree, MAX);
}
