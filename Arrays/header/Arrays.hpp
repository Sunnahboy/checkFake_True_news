#ifndef Arrays_HPP
#define Arrays_HPP
#include <iostream>

using namespace std;
struct NewsArticle {
    *char title;//Pointer to dynamically allocated memory
    *char content;
    *char category;
    int publicationYear;
    int publicationMonth;
    int publicationDay;
};
class ArraysAlgo
{
    private:

        NewsArticle* articles;
        int capacity;//capacity of array
        int size;//current number of articles in the array



        // Function to resize the array when needed
        void resizeArray(int newCapacity) {};

        // Function to manually copy a string to a dynamically allocated char array
        void copyString(char*& dest, const char* src) {};

        // Function to manually calculate the length of a string
        int stringLength(const char* str) {};



        int * arr=NULL;
        int size;
        string indicator;

    public:
        // Constructor
        ArraysAlgo(){}


        // Destructor to free dynamically allocated memory
        ~ArraysAlgo() {};

        // Function to add a news article to the collection
        void addArticle(const char* title, const char* content, const char* category,
            int publicationYear, int publicationMonth, int publicationDay) {
        };

        // Function to display all articles
        void displayArticles() const {};//only read the data members of the object and cannot modify them.

        // Function to sort articles by publication year (ascending)
        void sortByYear() {};

        // Function to search for articles by title
        NewsArticle* searchByTitle(const char* title) {};

        // Function to search for articles by category
        NewsArticle* searchByCategory(const char* category, int& foundCount) {};

        // Function to display articles published in a specific year
        void displayArticlesByYear(int year) const {};


        //Custom String Comparison Function
        bool customStringCompare(const char* str1, const char* str2) {};



        void InsertionSort(){}
        void MergeSort(int* arr, int left, int right){}
        void BubbleSort(){}
        void QuickSort(){}

        void fillingarrays(){}
        bool binarysearch(){}
        LinearsearchByCategory(const char* category) {};
        
};  


#endif