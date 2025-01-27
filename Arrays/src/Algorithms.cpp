#include "Arrays.hpp"
//bubble sort algorithm by akira
//merge sort ahorithm by ahemed
void Merge(int * arr, int LEFT, int MID, int RIGHT){
    
    int L=MID-LEFT +1;
    int R=RIGHT-MID;
    
    //creating two temporary arrays for sorting the data divided
    int * leftArr=new int[L];
    int * rightArr=new int[R];
    
    //fill the temporary arrays with values for each recursion
    for(int i=0; i<L; i++){
        leftArr[i]=arr[i+LEFT];
    }
    for(int j=0; j<L; j++){
        rightArr[j]=arr[MID+1+j];
    }

    //create three integers to parse each array left and right and the sorted one
    int j=0, i=0, k=LEFT;
    //k value set to LEFT to avoid overwriting elements from the right array to the left array and update the positions
    
    while(i<L && j<R){
        if(leftArr[i]<=rightArr[j]){
            arr[k]=leftArr[i];
            i++;
        }
        else
        {
            arr[k]=rightArr[j];
            j++;    
        }
        k++;
    }

    // add remaining elements to the array
    //remaining elements could be either on the right or the left of the array so have to account for both and create a while loop for both
    while(i<L){
        arr[k]=leftArr[i];
        i++;
        k++;
    }
    while(j < R){
        arr[k]=rightArr[j];
        j++;
        k++;
    }

    //now we delete both temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}

void ArraysAlgo::MergeSort(int* arr, int left, int right){
    if(left==right)return;
    int mid=(left+right)/2;
    MergeSort(arr, left, mid);
    MergeSort(arr,mid+1, right);
    Merge(arr, left, mid, right);
}




// Function to perform Bubble Sort
void  ArraysAlgo::bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // Flag to check if any swapping occurred
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true; // Set the flag to true
            }
        }
        // If no two elements were swapped in the inner loop, then the array is sorted
        if (!swapped) {
            break;
        }
    }
}

bool ArraysAlgo::binarySearch(string** arr, int rows, int targetDate) {
    int left = 1; // Start from 1 to skip the header row
    int right = rows - 1; // Adjust for zero-based indexing

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midDate = (arr[mid][3]); // assuming Date is in the 4th column

        if (midDate == targetDate) {
            return true; // Found the target date
        } else if (midDate < targetDate) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return false; // Target date not found
}


bool  ArraysAlgo::linearSearch(string** arr, int rows, int targetDate) {
    for (int i = 1; i < rows; i++) { // Start from 1 to skip the header row
        int currentDate = (arr[i][3]); // assuming Date is in the 4th column
        if (currentDate == targetDate) {
            return true; // Found the target date
        }
    }
    return false; // Target date not found
}

// Example usage of binary search
    int targetDate = 20170115; // Example date to search for (YYYYMMDD)
    bool found = binarySearch(array, row, targetDate);
    cout << "Date " << targetDate << " found: " << (found ? "Yes" : "No") << endl;


    int targetDate = 20230115; // Example date to search for (YYYYMMDD)
    bool found = linearSearch(array, row, targetDate);
    cout << "Date " << targetDate << " found: " << (found ? "Yes" : "No") << endl;


//quick sort algorithm by abu
//insertion sort algorithm by kashave
//selection sort algorithm by akira

