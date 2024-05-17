#include <iostream>

using namespace std;
class Min_Max_element {
public:
    int findMin(int *a, int start, int end) {
        int min_ind = start;
        for (int i = start + 1; i < end; i++) {
            if (a[min_ind] > a[i]) {
                min_ind = i;
            }
        }
        return min_ind;
    }

    int findMax(int *a, int start, int end) {
        int max_ind = start;
        for (int i = start + 1; i < end; i++) {
            if (a[max_ind] < a[i]) {
                max_ind = i;
            }
        }
        return max_ind;
    }
};

class doubleSort : public Min_Max_element{
public:
    void double_selection_sort(int *a, int n) {
        int minind = 0, maxind = 0;
        for (int i = 0; i < n / 2; i++) {
            minind = findMin(a, i, n - i);
            swap(a[i], a[minind]);
            maxind = findMax(a, i, n - i);
            swap(a[n - 1 - i], a[maxind]);
        }
    }
};

class selectionSort : public Min_Max_element {
public:
    void selection_sort(int *a, int n) {
        for (int i = 0; i < n - 1; i++) {
            swap(a[i], a[findMin(a, i, n)]);
        }
    }
};



class bubbleSort {
public:
    void bubble_sort(int *a, int n) {
        bool isSwapped;
        for (int i = 0; i < n - 1; i++) {
            isSwapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    isSwapped = true;
                }
            }
            if (!isSwapped)
                break;
        }
    }
};

int main() {
    int arr[] = {5, 2, 7, 1, 3,12,9,10,18,2,3,4,5,10};
    int n = sizeof(arr) / sizeof(arr[0]);

    doubleSort doubleSort;
    bubbleSort bubbleSort;
    selectionSort selectionSort;



//    bubbleSort.bubble_sort(arr,n); // work
    doubleSort.double_selection_sort(arr,n); // work
//    selectionSort.selection_sort(arr,n); /// work
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
