#include <iostream>
#include <limits>
#include "header/Arrays.hpp"

using namespace std;
//bubble sort algorithm by akira
//merge sort ahorithm by ahemed
void Merge(int*& arr, int LEFT, int MID, int RIGHT){
    
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

void ArraysAlgo::MergeSort(int*& arr, int left, int right){
    if(left==right)return;
    int mid=(left+right)/2;
    MergeSort(arr, left, mid);
    MergeSort(arr,mid+1, right);
    Merge(arr, left, mid, right);
}

//quick sort algorithm by abu
//insertion sort algorithm by kashave
//selection sort algorithm by akira