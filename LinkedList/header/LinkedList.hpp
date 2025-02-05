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
    string publicationDate;
    Node* next;

    // Constructor to initialize node data
    Node(const string& t, const string& c, const string& cat, const string& pubDate)
        :title(t),
        content(c), 
        category(cat),
        publicationDate(pubDate), 
        next(nullptr) {}
};

// Define the LinkedList class
class LinkedList {
private:
    Node* head; // Pointer to the head of the list

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to free memory
    ~LinkedList();

    // Add a new article to the list
    void addArticle(const string& title, const string& content, const string& category, const string& publicationDate);

    // Display all articles
    void displayArticles() const;

    // Search for an article by title
    Node* searchByTitle(const string& title) const;

    // Sort articles by publication date
    void sortArticles();

};
#endif


// // Main function to test the implementation
// int main() {
//     LinkedList newsList;

//     // Add articles
//     newsList.addArticle("AI Breakthrough", "New AI model...", "Technology", "2023-10-01");
//     newsList.addArticle("Election Results", "The election...", "Politics", "2023-10-05");
//     newsList.addArticle("Sports Update", "Team wins...", "Sports", "2023-10-03");

//     // Display articles
//     cout << "All Articles:\n";
//     newsList.displayArticles();

//     // Search for an article
//     string searchTitle = "AI Breakthrough";
//     Node* result = newsList.searchByTitle(searchTitle);
//     if (result) {
//         cout << "Found Article: " << result->title << "\n\n";
//     } else {
//         cout << "Article not found.\n\n";
//     }

//     // Sort articles
//     cout << "Sorted Articles:\n";
//     newsList.sortArticles();
//     newsList.displayArticles();

//     // Delete an article
//     string deleteTitle = "Sports Update";
//     newsList.deleteArticle(deleteTitle);
//     cout << "After Deleting '" << deleteTitle << "':\n";
//     newsList.displayArticles();

//     return 0;
// } 