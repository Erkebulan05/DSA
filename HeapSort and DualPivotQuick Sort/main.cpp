#include <iostream>
using namespace std;

class HeapSort {
public:
    void sort(int arr[],int N){
        heapSort(arr,N);
    }
private:
    void heapify(int arr[],int N , int i){
        int largest = i;
        int l = 2*i +1;
        int r = 2*i + 2 ;

        if(l < N && arr[l]>arr[largest])
            largest = l;
        if(r< N && arr[r]>arr[largest])
            largest = r;
        if(largest != i){
            swap(arr[i],arr[largest]);
            heapify(arr , N,largest);
        }
    }
    void heapSort(int arr[],int N){
        for(int i =N/2 - 1;i>=0 ; i--)
            heapify(arr,N,i);

        for(int i = N-1;i>=0;i--){
            swap(arr[0],arr[i]);
            heapify(arr,i,0);

        }

    }
};

class DualPivotQuickSort {
public:
    void sort(int* arr, int size) {
        dualPivotQuickSort(arr, 0, size - 1);
    }

private:
    void dualPivotQuickSort(int* arr, int start, int end) {
        if (start < end) {
            int lp = arr[start];
            int rp = arr[end];
            if (lp > rp) {
                swap(lp, rp);
            }

            int i = start + 1;
            int lt = start + 1;
            int gt = end - 1;
            int eq = i;

////            <lp|    | lp< &&< rp |  |rp<
//                         5,6,7,9,1,8
//                         1 ,5 , 6 ,7 , 8 ,9

            while (i <= gt) {
                if (arr[i] < lp) {
                    swap(arr[i], arr[lt]);
                    lt++;
                    i++;
                } else if (arr[i] > rp) {
                    swap(arr[i], arr[gt]);
                    gt--;
                } else {
                    i++;
                }
            }

            swap(arr[start], arr[lt - 1]);
            swap(arr[end], arr[gt + 1]);

            dualPivotQuickSort(arr, start, lt - 2);
            if (lp != rp) {
                dualPivotQuickSort(arr, lt, gt);
            }
            dualPivotQuickSort(arr, gt + 2, end);
        }
    }

//    void swap(int& a, int& b) {
//        int temp = a;
//        a = b;
//        b = temp;
//    }
};

int main() {
    HeapSort heapSort;
    int arr[] = { 4,3,2,6,5,1 };

    int N = sizeof(arr) / sizeof(arr[0]);


    heapSort.sort(arr, N);


    cout << "Sorted array is \n";
    for(int i = 0;i<N;i++) {
        cout<<arr[i]<<" ";
    }


//    int arr[] = {24, 8, 42, 75, 29, 77, 38, 57};
//    int size = sizeof(arr) / sizeof(arr[0]);
//
//    DualPivotQuickSort sorter;
//    sorter.sort(arr, size);
//
//    cout << "Sorted array: ";
//    for (int i = 0; i < size; ++i) {
//        cout << arr[i] << " ";
//    }


    return 0;
}