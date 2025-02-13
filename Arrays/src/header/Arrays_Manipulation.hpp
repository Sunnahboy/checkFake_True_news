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
        int size;
        int capacity;
    protected:
        ArraysAlgo algo;
        HashMap hashmap;
        YearHashMap hashmapYear;
        DayHashMap hashmapDay;
        MonthHashMap hashmapMonth; 
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
    public:
        dataManagement();
        void ReadData(ifstream& file);
        bool isEnglishWordCharacter(char c);
        void ParseDate(string& Date, int& year, int& month, int& day);
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
       void ApplySort(int size);
       void tokenizeWords(string** arr);
       template <typename Any> 
       void resizeArray(Any*& array, int oldsize, int newSize);
};
#endif