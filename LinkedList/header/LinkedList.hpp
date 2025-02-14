#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <iostream>
#include <string>
using namespace std;

// Define the Node structure
struct Node {
    string title;
    string content;
    string category;
    int publicationYear;
    int publicationMonth;
    int publicationDay;
    
    Node* next;

    // Constructor to initialize node data
    Node(const string& t, const string& c, const string& cat, const int& pubYear, const int& pubMonth, const int& pubDay)
        :title(t),
        content(c), 
        category(cat),
        publicationYear(pubYear), 
        publicationMonth(pubMonth),
        publicationDay(pubDay),
        next(nullptr) {}
};

// Define the LinkedList class
class LinkedList {
private:
     // Pointer to the head of the list

public:
    Node* head;
    // Constructor
    LinkedList();

    // Destructor to free memory
    ~LinkedList();

    // Add a new article to the list
    void addArticle(string& title, string& content, string& category, string& publicationDate);

    // Display all articles
    void displayArticles() const;

    // Search for an article by title
    Node* searchByTitle(string& title) ;

    // Sort articles by publication date
    void sortArticles();

    void addNode(string& title, string& content, string& category, int year, int month, int day);

    // Optimized Linear Search
    void linearSearch(string& searchTerm, string& searchType);
    Node* mergeSortedLists(Node* a, Node* b);
    Node* bottomUpMergeSort(Node* head);
    //Binary Search
    void binarySearchByYear(string& targetYear);

};

#endif