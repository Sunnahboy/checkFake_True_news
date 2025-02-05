#include <iostream>
#include <fstream>
#include <string>

#include "../header/LinkedList.hpp"
using namespace std;

// Class to manage news articles data
class DataManagement {
private:
    // // Structure to store article information
    // struct Node {
    //     string title;
    //     string content;
    //     string category;
    //     string publicationDate;
    //     Node* next;
        
    //     Node(const string& t, const string& c, const string& cat, const string& pubDate)
    //         : title(t), content(c), category(cat), publicationDate(pubDate), next(nullptr) {}
    // };

    Node* head;
    ifstream trueData;    // File stream for true news dataset
    ifstream fakeData;    // File stream for fake news dataset
    int trueArticlesCount;  // Counter for true articles
    int fakeArticlesCount;  // Counter for fake articles

public:
    // Constructor: Initialize pointers and open data files
    DataManagement() : head(nullptr), trueArticlesCount(0), fakeArticlesCount(0) {
        trueData.open("../dataSets/true.csv");
        fakeData.open("../dataSets/fake.csv");
        if (!trueData.is_open() || !fakeData.is_open()) {
            cout << "Error in reading the file" << endl;
        }
    }
    
    // Destructor: Clean up memory and close files
    ~DataManagement() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
        if (trueData.is_open()) trueData.close();
        if (fakeData.is_open()) fakeData.close();
    }

    // Add a new article to the linked list
    void addArticle(const string& title, const string& content, const string& category, const string& publicationDate) {
        Node* newNode = new Node(title, content, category, publicationDate);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Remove unnecessary characters and spaces from strings
    void trimString(string& str) {
        // Remove quotes if present
        if (!str.empty() && str[0] == '"') {
            str = str.substr(1);
        }
        if (!str.empty() && str[str.length()-1] == '"') {
            str = str.substr(0, str.length()-1);
        }

        // Remove spaces
        while (!str.empty() && isspace(str[0])) {
            str = str.substr(1);
        }
        while (!str.empty() && isspace(str[str.length()-1])) {
            str = str.substr(0, str.length()-1);
        }
    }

    // Check if character is valid for English text
    bool isEnglishWordCharacter(char c) {
        return isalnum(c) || c == '"' || c == ',' || c==' ';
    }

    // Read and process data from CSV file
    void readData(ifstream& file, bool isTrue) {
        string line;
        bool firstLine = true;
        int& count = isTrue ? trueArticlesCount : fakeArticlesCount;  // Reference to appropriate counter
        count = 0;  // Reset counter before reading

        while (getline(file, line)) {
            if (firstLine) {  // Skip header line
                firstLine = false;
                continue;
            }

            string title, content, category, date;
            int pos = 0;
            bool inQuotes = false;
            string currentField;
            int fieldCount = 0;

            // Parse CSV line considering quoted fields
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                
                if (c == '"') {
                    inQuotes = !inQuotes;
                } 
                else if(!isEnglishWordCharacter(c)){
                    continue;
                }
                else if (c == ',' && !inQuotes) {
                    // Process the completed field
                    trimString(currentField);
                    switch(fieldCount) {
                        case 0: title = currentField; break;
                        case 1: content = currentField; break;
                        case 2: category = currentField; break;
                    }
                    currentField.clear();
                    fieldCount++;
                } else {
                    currentField += c;
                }
            }
            // Process the last field (date)
            trimString(currentField);
            date = currentField;

            addArticle(title, content, category, date);
            count++;  // Increment counter for each article added
        }
    }

    // Display specified number of articles (or all if rows = -1)
    void displayArticles(int rows = -1) const {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr && (rows == -1 || count < rows)) {
            cout << "\n--- Article " << count + 1 << " ---\n";
            cout << "Title: " << temp->title << "\n";
            cout << "Content: " << temp->content << "\n";
            cout << "Category: " << temp->category << "\n";
            cout << "Date: " << temp->publicationDate << "\n";
            temp = temp->next;
            count++;
        }
    }

    // Display statistics about the number of articles in each dataset
    //NOTE: When main/Interface calls the ReadData function, it will automatically update the article count. 
    //Therefore, when the user calls to display the function for the article count, it will display the updated count.
    //Reducing time efficiency by not having to loop through the linked list to count the articles again.
    void displayArticleCounts() const {
        cout << "\n=== Article Count Statistics ===\n";
        cout << "True News Articles: " << trueArticlesCount << "\n";
        cout << "Fake News Articles: " << fakeArticlesCount << "\n";
        cout << "Total Articles: " << (trueArticlesCount + fakeArticlesCount) << "\n";
        cout << "==============================\n";
    }

    // Getter methods for file streams
    ifstream& getTrueData() { return trueData; }
    ifstream& getFakeData() { return fakeData; }

    //HERE
    // Add these as public members in the DataManagement class

    // Helper function to compare dates (assumes format YYYY-MM-DD)
    bool isDateInRange(const string& articleDate, const string& startDate, const string& endDate) {
        // Simple string comparison works for YYYY-MM-DD format
        return articleDate >= startDate && articleDate <= endDate;
    }

    // Helper function to convert string to lowercase for case-insensitive comparison
    string toLowerCase(const string& str) {
        string result = str;
        for (char& c : result) {
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
        }
        return result;
    }


    //Linear and Binary Search need to move to Algorithms.cpp
    // // Optimized Linear Search
    // void linearSearch(const string& searchTerm, const string& searchType) {
    //     Node* current = head;
    //     int matchCount = 0;
    //     string searchTermLower = toLowerCase(searchTerm);
        
    //     cout << "\n=== Linear Search Results ===\n";
        
    //     while (current != nullptr) {
    //         bool match = false;
    //         string fieldToSearch;
            
    //         if (searchType == "category") {
    //             fieldToSearch = toLowerCase(current->category);
    //         } else if (searchType == "title") {
    //             fieldToSearch = toLowerCase(current->title);
    //         } else {
    //             cout << "Invalid search type\n";
    //             return;
    //         }
            
    //         // Check if searchTerm is a substring of the field
    //         if (fieldToSearch.find(searchTermLower) != string::npos) {
    //             cout << "\nMatch found:\n";
    //             cout << "Title: " << current->title << "\n";
    //             cout << "Category: " << current->category << "\n";
    //             cout << "Date: " << current->publicationDate << "\n";
    //             matchCount++;
    //         }
            
    //         current = current->next;
    //     }
        
    //     cout << "\nTotal matches found: " << matchCount << "\n";
    // }


    // //Binary Search NOT WORKING!!! Fix it
    // // Binary Search for dates (searches by year)
    // void binarySearchByYear(const string& targetYear) {
    //     // First, create a sorted temporary linked list of nodes by year
    //     Node* sortedHead = nullptr;
    //     Node* current = head;
        
    //     // Copy nodes and insert them in sorted order by year
    //     while (current != nullptr) {
    //         string currentYear = current->publicationDate.substr(0, 4);
    //         Node* newNode = new Node(current->title, current->content, 
    //                             current->category, current->publicationDate);
            
    //         // Insert in sorted order
    //         if (sortedHead == nullptr || currentYear < sortedHead->publicationDate.substr(0, 4)) {
    //             newNode->next = sortedHead;
    //             sortedHead = newNode;
    //         } else {
    //             Node* temp = sortedHead;
    //             while (temp->next != nullptr && 
    //                 temp->next->publicationDate.substr(0, 4) < currentYear) {
    //                 temp = temp->next;
    //             }
    //             newNode->next = temp->next;
    //             temp->next = newNode;
    //         }
            
    //         current = current->next;
    //     }
        
    //     // Perform binary search
    //     int matchCount = 0;
    //     cout << "\n=== Binary Search Results for Year " << targetYear << " ===\n";
        
    //     // Convert linked list to array of pointers for binary search
    //     int count = 0;
    //     current = sortedHead;
    //     while (current != nullptr) {
    //         if (current->publicationDate.substr(0, 4) == targetYear) {
    //             cout << "\nMatch found:\n";
    //             cout << "Title: " << current->title << "\n";
    //             cout << "Category: " << current->category << "\n";
    //             cout << "Date: " << current->publicationDate << "\n";
    //             matchCount++;
    //         }
    //         current = current->next;
    //     }
        
    //     cout << "\nTotal matches found: " << matchCount << "\n";
        
    //     // Clean up temporary sorted list
    //     while (sortedHead != nullptr) {
    //         Node* temp = sortedHead;
    //         sortedHead = sortedHead->next;
    //         delete temp;
    //     }
    // }

    // Test search functionality
    void testSearch() {
        cout << "\n=== Testing Search Functions ===\n";
        
        // Test linear search
        cout << "\nTesting Linear Search by Category:\n";
        linearSearch("Trump", "title");
        
        // cout << "\nTesting Linear Search by Title:\n";
        // linearSearch("election", "title");
        
        // Test binary search
        // cout << "\nTesting Binary Search by Year:\n";
        // binarySearchByYear("2017");
    }


};

int main() {
    DataManagement data;
    data.readData(data.getTrueData(), true);   // Read and count true news articles
    data.readData(data.getFakeData(), false);  // Read and count fake news articles
    data.displayArticleCounts();               // Show article count statistics
    // data.displayArticles(3);                   // Display first 3 articles
    // data.testSearch();                          // Test search functionality
    
    return 0;
}


