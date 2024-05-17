#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
/// TC: O(n+k) n and k size of inputarray nad outputarrray
//// SC:O(n+k) n and k taken space of inputarray and outputarray


class CountSort {
    vector <int> inputArray;
    vector <int> implementation() {
        int N = inputArray.size();
        int M = inputArray[0]; /// max element
        for (int i = 1; i < inputArray.size(); i++)
            if (inputArray[i] > M)
                M = inputArray[i];

        vector<int> countArray(M + 1, 0);

        for(int i = 0 ; i < N ; i ++)
            countArray[inputArray[i]]++;

        for(int i = 1 ; i <= M ; i++)
            countArray[i] += countArray[i-1];


        vector <int> outputArray(N);

        for(int i = N- 1 ;i>=0 ; i--){
            outputArray[countArray[inputArray[i]]-1]=inputArray[i];
            countArray[inputArray[i]]--;
        }

        return outputArray;


    }
//    4, 3, 7, 1, 5, 5, 3, 9
//    0  1   2  3  4  5  6  7  8  9
//    0  0   0  0  0  0  0  0  0  0
//    1  0   0 2  1  2   0  1  0 1
//           0  1  2  3  4  5  6  7
//    input  4, 3, 7, 1, 5, 5, 3, 9
//          0  1  2  3  4  5  6  7  8  9
//   count  1  1  1  3  4  6  6  7  7  8
//         0   1   2  3  4  5  6  7  8 9
//   outp  1    3   3  4   4  5   7  9
//   output 1 3 3 4 4 5 7 9
public:
    CountSort(const vector<int>& inputArray) : inputArray(inputArray) {}
    vector<int> sort() {
        return implementation();
    }
};
////TC:O(d * (n + k)), где d - количество разрядов, n - количество элементов в массиве, а k - диапазон значений элементов.
/// SP:O(n+k)
class RadixSort {
    // A utility function to get the maximum value in arr[]
    int getMax(int arr[], int n) {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }

    // A function to do counting sort of arr[] according to the digit represented by exp

    void countSort(int arr[], int n, int exp) {
      int count[10] = {0};
      int output[n];

      for(int i = 0 ; i <n ;i++)
          count[(arr[i]/exp)%10]++;

      for(int i = 1 ; i < 10 ; i++)
          count[i] +=count[i-1];

      for(int i =n-1 ; i>=0;i--){
          output[count[(arr[i]/exp)%10]-1] = arr[i];
          count[(arr[i]/exp)%10]--;
      }
      for(int i = 0 ; i < n ; i++)
          arr[i] = output[i];
    }

public:
    void radixsort(int arr[], int n) {
        // Find the maximum number to know the number of digits
        int m = getMax(arr, n);
        // Do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i where i is the current digit number
        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, n, exp);
    }
};
//986 329 217 543 765
//986
//exp = 1 986/1>0; exp*=10
//        countsort;
//output[5]
//int i
//count   0   1     2   3     4   5     6   7   8   9
//        0   0     0   0     0   0     0   0   0   0
//        0   0     0   1     0   1     0   1   1   1
////                      543       765      217 986  329;
//        0   0     0   1     1   2     2    3  4   5
//
//        0   1   2   3   4   5  6   7   8   9
//        543  765  217  986  329
//        0  1  2  3  4   5  6  7  8  9
//           217   329      543  765   986
//
//           217 329 543 765 986
//
//



int main() {
    vector<int> inputArray = { 4, 3, 12, 1, 5, 5, 3, 9 };
    CountSort countSort(inputArray);
    vector<int> outputArray = countSort.sort();

    for (int i = 0; i < inputArray.size(); i++)
        cout << outputArray[i] << " ";

    cout<<endl;

    int arr[] = { 543, 986, 217, 765, 329 };
    int n = sizeof(arr) / sizeof(arr[0]);

    RadixSort radixSort;

    radixSort.radixsort(arr, n);



    for(int i = 0 ; i <n ;i++)
        cout<<arr[i]<<" ";



    return 0;
}