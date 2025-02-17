#ifndef Arrays_Manipulation_HPP
#define Arrays_Manipulation_HPP


#include <iostream>
#include <fstream>
#include "Arrays.hpp"
#include "HashMap.hpp"

using namespace std;
class dataManagement
{
    private:
        ArraysAlgo algo;
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
        int size;
        int capacity;
    public:
        dataManagement();
        void ReadData(ifstream& file);
        bool isEnglishWordCharacter(char c);
        bool ParseDate(string& Date, int& year, int& month, int& day);
        string** SortToArray(int size, int* temp);
        string** StoreToArray(int size);
        int StringToInt(string& str);
        int monthToNumber(string month);
        int getsize();
        void setsize(ifstream& file);
        ~dataManagement();
        ifstream& getTrueData();
        ifstream& getFakeData();

       void head(string ** arr, int rows);
       void displayStruct(int rows);
       template <typename SelectedType>
       void ApplySortH(string**& arr,int size, int field);
       void ApplySort(string**& arr,int size, int field);
       void ApplyInsertionSort(string**& array, int size, int field);
       void tokenizeWords(string** arr);
       template <typename Any> 
       void resizeArray(Any*& array, int oldsize, int newSize);
};
#endif