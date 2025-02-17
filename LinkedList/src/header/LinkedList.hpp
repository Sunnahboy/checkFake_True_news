#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Define the Node structure
struct article{
    string title;
    string content;
    string category;
    int day;
    int month;
    int year;
    article* next;

    // Constructor to initialize node data
    
};

// Define the LinkedList class
class dataManagement{
    private:
        article* head=nullptr;
        article* tail = nullptr; // New tail pointer
        int size;
        string ListName;
        ifstream TrueData;
        ifstream FakeData;
    
    public:
        // Constructor
        dataManagement(string Name);
        // Destructor to free memory
        ~dataManagement();


        // Constructor of the list
        article * CreateNewNode(string Title, string Content, string Category, int Day, int Month, int Year);
        void addArticlefromFront(string Title, string Content, string Category,int Day, int Month, int Yearr);
        void addArticlefromEnd(string Title, string Content, string Category, int Day, int Month, int Year);

        void ReadData(ifstream& file);
        bool ParseDate(string& Date, int& year, int& month, int& day);
        bool isEnglishWordCharacter(char c);
        int getsize();
        int StringToInt(string& str);
        int monthToNumber(string month);
        ifstream& getTrueData();
        ifstream& getFakeData();

        // Display all articles
        void displayArticlesfromFront();
        // void displayArticlesfromEnd();
        article *gethead();
        void tokenizeWords(article * Node);
        void tokenizeWordsHash(article * Node);
        // Search for an article by title

        // Sort articles by publication date
        void insertionSortByDate();
        bool compareDates(article* a, article* b);
        
        // void sortArticles();

        void calculatePoliticalFakePercentage(article* trueHead, article* fakeHead);
        void analyzeMonthlyFakePoliticalNews(article* fakeHead);

};
#endif