# 學習 Divide and Conquer

##

## Merge Sort

將欲排序的陣列，divide 成二個部份：


```
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

        // merge
    }
}
```

分別解決這二個部份後，最後再將結果合併回一個部份。合併的方式，可分為 in place merge 與 non in place merge。

以下是一個 in place merge 的演算法：

```
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
```

## 參考資源

[1]: http://en.wikipedia.org/wiki/Divide_and_conquer_algorithms

[2]: http://en.wikipedia.org/wiki/Merge_sort