#ifndef Arrays_Manipulation_HPP
#define Arrays_Manipulation_HPP


#include <iostream>
#include <fstream>
#include "Arrays.hpp"

using namespace std;
class dataManagement
{
    protected:
        ArraysAlgo algo;
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
    public:
        dataManagement();
        void ReadData(ifstream& file);
        bool isEnglishWordCharacter(char c);
        void ParseDate(string& Date, int& year, int& month, int& day);
        string** StoreToArray(int size, int* temp);
        int StringToInt(string& str);
        int monthToNumber(string month);

        ~dataManagement();
        ifstream& getTrueData();
        ifstream& getFakeData();

       void head(string ** arr, int rows);
       void displayStruct(int rows);
    //    void ApplySort(int size);
};
#endif