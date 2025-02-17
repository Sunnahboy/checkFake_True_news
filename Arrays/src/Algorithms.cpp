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
void ArraysAlgo::BubbleSort() {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (articles[j].publicationYear > articles[j + 1].publicationYear) {
                swap(articles[j], articles[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // If no swaps, array is sorted
    }
}


// void ArraysAlgo::InsertionSort(string** arr, int size) {
//     int* index = new int[size];
//     for (int i = 0; i < size; i++) {
//         index[i] = i; // Initialize index array
//     }

//     for (int i = 1; i < size; i++) {
//         int key = index[i];  // Store the current index
//         int year = stoi(arr[key][3]); // Extract date components once
//         int month = stoi(arr[key][4]);
//         int day = stoi(arr[key][5]);
        
//         int j = i - 1;
        
//         // Compare using year, then month, then day (change to ascending order)
//         while (j >= 0) {
//             int prevYear = stoi(arr[index[j]][3]);
//             int prevMonth = stoi(arr[index[j]][4]);
//             int prevDay = stoi(arr[index[j]][5]);
            
//             // Sort earliest to latest
//             if (prevYear > year || 
//                 (prevYear == year && prevMonth > month) ||
//                 (prevYear == year && prevMonth == month && prevDay > day)) {
//                 index[j + 1] = index[j]; // Shift index to the right
//                 j--;
//             } else {
//                 break; // Correct position found
//             }
//         }
//         index[j + 1] = key; // Insert key at correct position
//     }

//     // Rearrange the array in place using the sorted index array
//     string** sortedArr = new string*[size];
//     for (int i = 0; i < size; i++) {
//         sortedArr[i] = new string[6];
//         sortedArr[i] = arr[index[i]];  // Place sorted elements into the new array
//     }

//     // Copy the sorted values back into the original array
//     for (int i = 0; i < size; i++) {
//         arr[i] = sortedArr[i];
//     }

//     // Clean up memory
//     delete[] sortedArr;
//     delete[] index; // Clean up index array
// }


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



int compare(int a, int b, int order) { //helper to choose decending or ascending order
    if(order == 1){                    // if 1 its descending else its descending
        return a>=b;
    }
    else if(order == 0){
        return a<=b;
    }
    return -1;
}

void swap(int *a, int *b) { //helper function to swap arrays. 
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int*& arr, int low, int high, int order){ //function to partiton and sort the array via a chosen pivot. 
                                             // rearranges the elements according to the pivot

    int pivot = arr[high];

    int i = low -1; 

    for (int j = low; j < high; j++) {
        // if the current element is smaller than or equal to the pivot
        if (compare(arr[j], pivot, order)) {
            // increment index if smaller
            i++;
            
            // swap current element with element at index i
            swap(&arr[i], &arr[j]);
        }
    }
    
    // place pivot in  correct position
    swap(&arr[i + 1], &arr[high]);
    
    // return the index of the pivot
    return i + 1;

} 

void QuickSortRecursion(int*& arr, int left, int right, int order){ // the recursive function 
    
      // base case if statement to check if the array has more than 1 element
    if (left < right) {
        // part the array and get the index of the pivot element
        int pivotIndex = Partition(arr, left, right, order);
        
        // recusrive call to the left
        QuickSortRecursion(arr, left, pivotIndex - 1, order);
        
        // recusrive call to the right 
        QuickSortRecursion(arr, pivotIndex + 1, right, order);
    }


}

void ArraysAlgo::QuickSort(int*& arr, int length, int order){ // Wrapper function, used to initiate QuickSort

    if (length <= 1){ //this is to check if the array is empty or with 1 element.
                      // to ensure that when the array gets small enough no resources are used to sort again. 
        return;
    }
    

    QuickSortRecursion(arr, 0, length-1, order); //this calls the recursive function to sort initially, the entire array is chosen first to last element

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
    cout << "Total Rows -> "<< Total;
    delete[] temp;
}


