#ifndef Arrays_HPP
#define Arrays_HPP

#include <iostream>
using namespace std;
class ArraysAlgo
{
    private:
        int * arr=NULL;
        int size;
        string indicator;

    public:
        ArraysAlgo(){
            size=1;
            arr=new int[size];
        }
        void InsertionSort(){}
        void MergeSort(int* arr, int left, int right){}
        void BubbleSort(){}
        void QuickSort(){}
};  





#endif