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
        HashMap hashmap;
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
        int size;
        int capacity;
    public:
        dataManagement();
        ~dataManagement();
        
        void ReadData(ifstream& file);
        bool isEnglishWordCharacter(char c);
        bool ParseDate(string& Date, int& year, int& month, int& day);
        
        string** SortToArray(string** sourceArray, int size, int* temp);  //int size, int* temp);
        string** StoreToArray(int size);
        
        int StringToInt(string& str);
        int monthToNumber(string month);
        int getsize();

        void DeleteArray(string**& arr, int size);
        
        
        ifstream& getTrueData();
        ifstream& getFakeData();
  
       void head(string ** arr, int rows);
       void DisplayArray(string** arr, int totalArticles);
       
       template <typename SelectedType>
       void ApplySortH(string**& arr,int size, int field, int sortType);
       void ApplySort(string**& arr,int size, int field, int sortType);
       
       template <typename Any> 
       void resizeArray(Any*& array, int oldsize, int newSize);
       
       template <typename SelectedType>
       void MergeSortBinary(string**& array, int size, int field);
       void MergeSortForBinarySearch(string**& array, int size, int field);
       
       void tokenizeWordsHash(string** arr, int size);
       string ** SortToArrayHash(string** sourceArray, int size, int* temp);
       
       void tokenizeWords(string** arr, int size);
       
};
#endif