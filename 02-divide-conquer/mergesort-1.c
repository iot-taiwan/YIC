/*
 * Divide and conquer: in-place mergesort for ARM mbed
 *
 * Copyright (C) 2015 Mokoversity Inc.
 *
 * ARM mbed for Young, http://www.mokoversity.com/yic
 *
 * Licensed under MIT
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void print_result(int A[], int lo, int hi)
{
    int i;

    printf("[%d, %d]: ", lo, hi);
    for (i = lo; i <= hi; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void merge_sort(int A[], int lo, int hi)
{
    int mid = 0;
    int tmp, i;
    
    if (lo == hi)
        return;

    // merge
    if (lo + 1 ==  hi) {
        tmp = A[hi];

        // swap
        if (tmp < A[lo]) {
            A[hi] = A[lo];
            A[lo] = tmp;
        }
    // divide
    } else {
        mid = (lo + hi) / 2;

        print_result(A, lo, mid);
        merge_sort(A, lo, mid);

        print_result(A, mid + 1, hi);
        merge_sort(A, mid + 1, hi);

#if 1
        // merge
        mid++;
        while (lo < hi && mid <= hi) {
            if (A[lo] > A[mid]) {
                tmp = A[mid];

                for (i = mid; i > lo; i--)
                    A[i] = A[i-1];

                A[lo] = tmp;

                mid++;
            } else {
                lo++;
            }
        }
#endif
    }
}

int main()
{
    //int A[8] = {27, 10, 12, 20, 25, 13, 15, 22};
    int A[MAX];
    int i;
         
#if 1
    for (i = 0; i < MAX; i++) {
        // random number 1 to MAX0
        A[i] = (rand() % 100) +1;
    }
#endif

    merge_sort(A, 0, MAX - 1);

    printf("----------------------------\n");
    print_result(A, 0, MAX - 1);
}
