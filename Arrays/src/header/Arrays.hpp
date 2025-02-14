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
    void resizeArray(int*& array, int newCapacity);

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
    void InsertionSort(string** arr, int size);
    void MergeSort(int*& arr, int left, int right, int*& temp);
    //void BubbleSort();
    void BubbleSort(string** arr, int size);

    void QuickSort();
    void binarysearchYear(int year)const;
    // Utility methods
    void fillingarrays();
    void displayarrays();
};

#endif
