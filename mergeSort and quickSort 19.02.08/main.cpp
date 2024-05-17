#include<iostream>
using namespace std;



class quickSort {
public:
    int partition(int *a, int start, int end) {
        int pivot = a[end], i = start - 1;

        for (int j = start; j < end; j++) {
            if (a[j] < pivot)
                swap(a[++i], a[j]);
        }

        swap(a[++i], a[end]);
        return i;
    }

    void quickSort1(int *a, int start, int end) {
        if (start < end) {
            int p = partition(a, start, end);
            quickSort1(a, start, p - 1);
            quickSort1(a, p + 1, end);
        }
    }

};

class mergeSort {
public:
    void merge(int *a, int start, int middle, int end) {
        int n1 = middle - start + 1, n2 = end - middle;
        int L[n1], R[n2];

        for (int i = 0; i < n1; i++)
            L[i] = a[start + i];
        for (int i = 0; i < n1; i++)
            R[i] = a[middle + 1 + i];

        int i = 0, j = 0, k = start;
        while (i < n1 && j < n2) {
            a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
        }

        while (i < n1) {
            a[k++] = L[i++];
        }
        while (j < n2) {
            a[k++] = R[j++];
        }
    }

    void mergeSort1(int *a, int start, int end) {
        if (start < end) {
            int middle = start + (end - start) / 2;
            mergeSort1(a, start, middle);
            mergeSort1(a, middle + 1, end);
            merge(a, start, middle, end);
        }
    }
};

int main() {
    quickSort quicksort;
    mergeSort mergeSort;
    int n = 14;
    int a[] = {8,2,3,4,5,6,1,2,9,10,12,6,1,8};
//    mergeSort.mergeSort1(a,0,n-1);
    quicksort.quickSort1(a, 0, n-1);
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }


    return 0;
}