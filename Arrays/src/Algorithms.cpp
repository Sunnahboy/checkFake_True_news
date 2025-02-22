#include <iostream>
#include <limits>
#include "header/Arrays.hpp"
using namespace std;


//Sorting Algorithms
// Helper function for Merge Sort
template <typename Type>
void Merge(Type*& arr, int LEFT, int MID, int RIGHT, int*& temp) {
    int L = MID - LEFT + 1;
    int R = RIGHT - MID;

    // Creating two temporary arrays for sorting and two for getting the index
    Type* leftArr = new Type[L];
    Type* rightArr = new Type[R];
    int* leftindex = new int[L];
    int* rightindex = new int[R];

    // Fill temporary arrays
    for (int i = 0; i < L; i++) {
        leftArr[i] = arr[i + LEFT];
        leftindex[i] = temp[i + LEFT];
    }
    for (int j = 0; j < R; j++) {
        rightArr[j] = arr[MID + 1 + j];
        rightindex[j] = temp[MID + 1 + j];
    }

    // Merge back into the main array
    int i = 0, j = 0, k = LEFT;
    while (i < L && j < R) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            temp[k]=leftindex[i];;
            i++;
        } else {
            arr[k] = rightArr[j];
            temp[k]=rightindex[j];
            j++;
        }
        k++;
    }
      // Copy remaining elements
    while (i < L) {
        arr[k] = leftArr[i];
        temp[k]=leftindex[i];
        i++;
        k++;
    }
    while (j < R) {
        arr[k] = rightArr[j];
        temp[k]=rightindex[j];
        j++;
        k++;
    }

    // Clean up temporary arrays
    delete[] leftArr;
    delete[] rightArr;
    delete[] leftindex;
    delete[] rightindex;
}
template<typename Type>
// Merge Sort Implementation
void ArraysAlgo::MergeSort(Type*& arr, int left, int right,int*& temp) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid, temp);
    MergeSort(arr, mid + 1, right, temp);
    Merge(arr, left, mid, right, temp);
}

// Bubble Sort Implementation
template <typename Type>
void ArraysAlgo::BubbleSort(Type*& arr, int left, int right, int*& temp) {
    
    if (left >= right) {
        // cout << "Skipping sorting since left >= right!" << endl;
        return;  // Avoid infinite recursion
    }

    // Directly perform sorting here
    for (int i = left; i < right; i++) {
        bool swapped = false;
        for (int j = left; j < right - (i - left); j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swap(temp[j], temp[j + 1]);  // Maintain index tracking
                swapped = true;
            }
        }
        if (!swapped) break;  // Stop early if no swaps
    }
}


template <typename Type>
void ArraysAlgo::InsertionSort(Type*& arr, int size, int* index) {
    // InsertionSort on the key array 'arr' using the 'index' array.
    for (int i = 1; i < size; i++) {
        int keyIndex = index[i];
        Type keyValue = arr[keyIndex];
        int j = i - 1;
        while (j >= 0 && arr[index[j]] > keyValue) {
            index[j + 1] = index[j];
            j--;
        }
        index[j + 1] = keyIndex;
    }
}


template <typename Type>
bool compare(Type a, Type b, int order) {
    if (order == 1) { // Descending order
        return a >= b;
    } else { // Ascending order
        return a <= b;
    }
}

// Swaps two elements in an array
template <typename Type>
void swapType(Type& a, Type& b) {
    Type temp = a;
    a = b;
    b = temp;
}

void swapInt(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function for QuickSort
template <typename Type>
int Partition(Type*& arr, int*& temp, int low, int high, int order) {
    Type pivot = arr[high];  // Choose pivot (last element)
    int pivotIndex = temp[high];

    int i = low - 1; 

    for (int j = low; j < high; j++) {
        // Compare elements based on order
        if (compare(arr[j], pivot, order)) {
            i++;
            swapType(arr[i], arr[j]);  // Swap elements
            swapInt(temp[i], temp[j]); // Swap corresponding indices
        }
    }
    
    // Place pivot in correct position
    swapType(arr[i + 1], arr[high]);
    swapInt(temp[i + 1], temp[high]);
    
    return i + 1;  // Return pivot index
}

// Recursive QuickSort function
template <typename Type>
void QuickSortRecursion(Type*& arr, int*& temp, int left, int right, int order) {
    if (left < right) {
        int pivotIndex = Partition(arr, temp, left, right, order);
        QuickSortRecursion(arr, temp, left, pivotIndex - 1, order);
        QuickSortRecursion(arr, temp, pivotIndex + 1, right, order);
        
    }
}

// QuickSort wrapper function
template <typename Type>
void ArraysAlgo::QuickSort(Type*& arr, int length, int*& temp, int order) {
    if (length <= 1) return; // No need to sort if array has 0 or 1 element
    QuickSortRecursion(arr, temp, 0, length - 1, order); // Call recursive QuickSort
}





//Searching Algorithms

void ArraysAlgo::BinarySearch(string** arr, int index, string field, int size) {
    int left = 0, right = size - 1;
    int* temp = new int[size]; // Store matched indices
    int count = 0;
    bool found = false;

    // Standard binary search loop
    while (left <= right) {
        int mid = (right + left) / 2;
        
        if (arr[mid][index] == field) {
            temp[count++] = mid;
            found = true;

            // Check for duplicates in the left portion of the array
            int l = mid - 1;
            while (l >= left && arr[l][index] == field) {
                temp[count++] = l--;
            }
            //check for the duplicates in the right portion of the array
            int r = mid + 1;
            while (r <= right && arr[r][index] == field) {
                temp[count++] = r++; 
            }

            break; // Exit once all matches are collected
        }
        else if (arr[mid][index] < field) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        for (int i = 0; i < size; i++) {
            if (arr[i][index].find(field) != string::npos) {
                temp[count++] = i;
            }
        }
    }

    if (count == 0) {
        cout << "No Match Found!" << endl;
        delete[] temp;
        return;
    }

    for (int j = 0; j < count; j++) {
        int row = temp[j];
        cout << " Row Number: " << row << endl;
        cout << "Title: " << arr[row][0] << endl;
        cout << "Text: " << arr[row][1] << endl;
        cout << "Subject: " << arr[row][2] << endl;
        cout << "Year: " << arr[row][3] << endl;
        cout << "Month: " << arr[row][4] << endl;
        cout << "Day: " << arr[row][5] << endl;
        cout << string(166, '=') << endl;
    }
    cout << "Total Rows -> " << count << endl;
    delete[] temp;
}




// there should one linear search for the value and one for the keywords or two for loops
void ArraysAlgo::LinearSearch(string** arr, int indx, string value, int size){
    
    int* temp=new int[size];
    int count=0;
    int matchExists=0;
    int Total=0;
    for (int i=0; i< size; i++){
        if(arr[i][indx]==value){
            temp[matchExists]=i;
            matchExists++;
            Total++;
        }
        else if (matchExists==0 && arr[i][indx].find(value) != string::npos){
            temp[count]=i;
            count++;
            Total++;
        }
    }
    if( matchExists > 0 ) {
        count = matchExists;
    }

    if(count==0){
        cout << "No Match Found!"<<endl;
        return;
    }   
    for (int j=0; j< count; j++){
        int index=temp[j];
        cout << " Row Number: " <<index<<endl;
        cout << "Title: " <<arr[index][0]<<endl; 
        cout << "Text: " <<arr[index][1]<<endl<<endl; 
        cout << "Subject: " <<arr[index][2]<<endl; 
        cout <<"Year: "<< arr[index][3]<<endl; 
        cout <<"Month: "<< arr[index][4]<<endl; 
        cout <<"Day: "<< arr[index][5]<<endl; 
        cout << string(166,'=');
        cout <<endl;
    }
    cout << "Total Rows -> "<< Total << endl;
    delete[] temp;
}


