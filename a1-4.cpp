#include <iostream>
#include<bits/stdc++.h> 

using namespace std;


int medianSmallList(int arr[], int n) {
    sort(arr, arr+n);
    return arr[n/2];
}


int* medianList (int arr[], int n){
    int size3;
    int* median = new int[(n+4)/5]; //since int gives the largest integer equal or less than a value, no. of groups will always bounded by (n+4)/5

    for (size3 =0; size3<(n+4)/5; size3++) {
        if (size3<n/5){
            median[size3]= medianSmallList(arr+size3*5,5);
        }
        else {
            median[size3]=medianSmallList(arr+size3*5, n%5);
        }
        //cout <<"This is list of medians:";
        //cout <<median[size3]<< " ";

    }
    //cout << endl;
    return median;
}

int medianOfMedians(int arr[], int n) {
    if (n <= 5) {
        return medianSmallList(arr, n);
    }
    int* median = medianList(arr, n);
    return medianOfMedians(median, ((n + 4) / 5));
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int r, int x) {
    int i;
    for (i = l; i < r; i++) 
        if (arr[i] == x) 
            break;
    swap(&arr[i], &arr[r]);  // Move pivot to end

    i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);  // Move pivot to its final place
    return i;
}

int kth(int arr[], int l, int r, int k) {
    if (k >= 0 && k <= r - l) {
        int medianOfmedian = medianOfMedians(arr + l, r - l + 1);

        int p = partition(arr, l, r, medianOfmedian);

        if (p - l == k) {
            return arr[p];
        } else if (p - l > k) {
            return kth(arr, l, p - 1, k);
        } else {
            return kth(arr, p + 1, r, k - (p - l + 1));
        }
    }
    return -1;  // Invalid k
}


// Function to find the median
double findMedian(int arr1[], int size1, int arr2[], int size2) {

    int n= size1+size2; //total array size
    int arr3[n];
    int i=0, j=0, k=0;

    while (i<size1) {
        arr3[k++]= arr1[i++];
    }
    while (j<size2) {
        arr3[k++]= arr2[j++];
    }
    if (n%2==1) {
        return kth(arr3, 0, n-1, n/2);
    }
    else {
        //since we need to take average
        int firstMedian = kth(arr3, 0, n - 1, n / 2);       // Find the first median
        int secondMedian = kth(arr3, 0, n - 1, (n / 2) - 1);  // Find the second median
        return (firstMedian + secondMedian) / 2.0;          // Return their average
    }

    
// Your code here

}


int main() {
    // You can use cout statements, but ensure that you submit after commenting them out, as the autograder will otherwise mistake it for your actual output
    // Everything else in the main function remains unchanged
    
    int size1;
    //cout << "Enter the size of the array1: ";
    cin >> size1;

    int arr[size1];
    //cout << "Enter " << size1 << " elements:" << endl;
    for (int i = 0; i < size1; ++i) {
        cin >> arr[i];
    }

   // //cout << "The array elements are: ";
    //for (int i = 0; i < size1; ++i) {
       // cout << arr[i] << " ";
   // }
    //cout << endl;

    int size2;
    //cout << "Enter the size of the array2: ";
    cin >> size2;

    int arr1[size2];
    //cout << "Enter " << size2 << " elements:" << endl;
    for (int i = 0; i < size2; ++i) {
        cin >> arr1[i];
    }

   // cout << "The array elements are: ";
    //for (int i = 0; i < size2; ++i) {
     //   cout << arr1[i] << " ";
  //  }
    //cout << endl;

    if (size1+size2==0) {
        cout << "Empty Array";
        return 0
            }
    
    cout << "Median = " << findMedian(arr, size1, arr1, size2) << endl; // do not comment this out
    
    return 0;
}

