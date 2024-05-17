#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class InsertionSort {
    //1)Insertion Sort class in C++
    // TC : O(n) , O(n^2)
    // SP : O(1)
public:
    void sort(int arr[] , int n){
        int j , i , key ;
        for(int i = 1 ; i <n ;i++){
            key = arr[i];
            j = i -1;
            while(j>=0 && arr[j]>key){
                arr[j+1]=arr[j];
                j-=1;
            }
            arr[j+1] = key ;
        }
    }
};
class ShellSort {
    //Shell sort class
    // TC :O(nlogn) , O(n log n^2)
    // SC : O(1)
public:
    void sort(int arr[],int n){
        for(int gap = n/2 ; gap > 0 ; gap /=2){
            for(int i = gap ; i<n ; i++){
                int temp = arr[i];
                int j = i ;
                while(j>=gap && arr[j-gap]>temp){
                    arr[j] = arr[j - gap];
                    j-=gap;
                }
                arr[j] = temp;
            }
        }
    }
};
class BucketSort {
    // Bucket Sort algorithm using Insertion Sort
    // TC:  O(n+k)(k - количество корзины ) , O(n^2)
    // SC: O(n)
    void insertionSort(vector <int>& bucket){
        int i , j , key ;
        for(int i = 1 ; i <bucket.size();i++){
            key = bucket[i];
            j = i - 1;
            while(j>=0 && bucket[j]>key){
                bucket[j+1]=bucket[j];
                j -=1;
            }
            bucket[j+1]=key;
        }
    }


public:
    void bucketSort(int arr[],int n ,int num_buckets){
        // Create buckets
        vector<vector<int>> buckets(num_buckets);

        // Distribute elments into buckets
        for (int i = 0; i < n; ++i) {
            int bi = min(num_buckets - 1, arr[i] * num_buckets / (100 + 1)); // Calculate bucket index
            buckets[bi].push_back(arr[i]);
        }

        // Sort individual buckets
        for (int i = 0; i < num_buckets; ++i) {
            insertionSort(buckets[i]);
        }

        // Concatenate sorted buckets back into array
        int index = 0;
        for (int i = 0; i < num_buckets; ++i) {
            for (int j = 0; j < buckets[i].size(); ++j) {
                arr[index++] = buckets[i][j];
            }
        }
    }

};
int main() {
    InsertionSort sorter;
    BucketSort sort1;
    ShellSort sort;
    int arr[] = { 9,3,5,8,10,12,19,99,100,1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int num_buckets;
    cout << "Enter the number of buckets: ";
    cin >> num_buckets;

    sorter.sort(arr,n);
    sort.sort(arr,n);
    sort1.bucketSort(arr,n,num_buckets);




    cout << "Array after sorting:"<<endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}