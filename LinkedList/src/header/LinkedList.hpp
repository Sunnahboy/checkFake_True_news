#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <iostream>
#include <string>
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
        // void addArticlefromEnd(string Title, string Content, string Category, int Day, int Month, int Year);

        void ReadData(ifstream& file);
        void ParseDate(string& Date, int& year, int& month, int& day);
        bool isEnglishWordCharacter(char c);
        int getsize();
        int StringToInt(string& str);
        int monthToNumber(string month);
        ifstream& getTrueData();
        ifstream& getFakeData();

        // Display all articles
        void displayArticlesfromFront();
        // void displayArticlesfromEnd();

        // Search for an article by title

        // Sort articles by publication date
        // void sortArticles();

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