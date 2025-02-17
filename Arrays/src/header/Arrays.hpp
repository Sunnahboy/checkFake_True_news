#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <iostream>
#include <string>

using namespace std;

struct NewsArticle {
    string title;         // Pointer to dynamically allocated memory
    string content;
    string category;
    int publicationYear=0;
    int publicationMonth=0;
    int publicationDay=0;
};

class ArraysAlgo {
private:
    int capacity;          // Capacity of the array
    int size;              // Current number of articles in the array
    int* arr;              // Pointer to an integer array
    string indicator;
    

    // Function to resize the integer array when needed
    void resizeArray2(int*& array, int newCapacity);

public:
    NewsArticle* articles; // Dynamic array of NewsArticle

    // Constructor
    ArraysAlgo(){}

    // Destructor
    ~ArraysAlgo(){}
    int getsize(){
        return size;
    }

    // Sorting algorithms
    
    template <typename Type>
    void MergeSort(Type*& arr, int left, int right, int*& temp);
    template <typename Type>
    void InsertionSort(Type*& arr, int size, int* index);
    void BinarySearch(string** arr, int choice, string field, int size);
    void BubbleSort();
    // void QuickSort();
    // // Utility methods
    void LinearSearch(string** arr, int choice, string field, int size);
    void QuickSort(int*& arr, int length, int order);
};

#endif
