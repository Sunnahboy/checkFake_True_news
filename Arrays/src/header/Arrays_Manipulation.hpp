#ifndef Arrays_Manipulation_HPP
#define Arrays_Manipulation_HPP


#include <iostream>
#include <fstream>
#include "Arrays.hpp"
#include "HashMap.hpp"
#include "NewsArticle.hpp"

using namespace std;
class dataManagement
{
    private:
        ArraysAlgo algo;
        HashMap hashmap;
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
       void StatisticalSum();
       void head(string ** arr, int rows);
       void displayStruct(int rows);
       template <typename SelectedType>
       void ApplySortH(string**& arr,int size, int field, int sortType);
       void ApplySort(string**& arr,int size, int field, int sortType);
       void tokenizeWordsHash(string** arr);
       void tokenizeWords(string** arr);
       template <typename Any> 
       void resizeArray(Any*& array, int oldsize, int newSize);
};
#endif