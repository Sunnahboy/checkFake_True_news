// // #include <iostream>
// // #include <fstream>
// // #include <string>

// // #include "../header/LinkedList.hpp"
// // #include "Algorithms.cpp"
// // using namespace std;

// // // Class to manage news articles data
// // class DataManagement {
// // private:
// //     // // Structure to store article information
// //     // struct Node {
// //     //     string title;
// //     //     string content;
// //     //     string category;
// //     //     string publicationDate;
// //     //     Node* next;
        
// //     //     Node(const string& t, const string& c, const string& cat, const string& pubDate)
// //     //         : title(t), content(c), category(cat), publicationDate(pubDate), next(nullptr) {}
// //     // };

// //     Node* head;
// //     ifstream trueData;    // File stream for true news dataset
// //     ifstream fakeData;    // File stream for fake news dataset
// //     int trueArticlesCount;  // Counter for true articles
// //     int fakeArticlesCount;  // Counter for fake articles

// // public:
// //     // Constructor: Initialize pointers and open data files
// //     DataManagement() {//: head(nullptr), trueArticlesCount(0), fakeArticlesCount(0) {
// //         trueData.open("../dataSets/true.csv");
// //         fakeData.open("../dataSets/fake.csv");
// //         if (!trueData.is_open() || !fakeData.is_open()) {
// //             cout << "Error in reading the file" << endl;
// //         }
// //     }
    
// //     // Destructor: Clean up memory and close files
// //     ~DataManagement() {
// //         while (head != nullptr) {
// //             Node* temp = head;
// //             head = head->next;
// //             delete temp;
// //         }
        
// //         if (trueData.is_open()) trueData.close();
// //         if (fakeData.is_open()) fakeData.close();
// //     }

// //     // Add a new article to the linked list
// //     void addArticle(const string& title, const string& content, const string& category, const string& publicationDate) {
// //         Node* newNode = new Node(title, content, category, publicationDate);
// //         if (head == nullptr) {
// //             head = newNode;
// //         } else {
// //             Node* temp = head;
// //             while (temp->next != nullptr) {
// //                 temp = temp->next;
// //             }
// //             temp->next = newNode;
// //         }
// //     }

// //     // Remove unnecessary characters and spaces from strings
// //     void trimString(string& str) {
// //         // Remove quotes if present
// //         if (!str.empty() && str[0] == '"') {
// //             str = str.substr(1);
// //         }
// //         if (!str.empty() && str[str.length()-1] == '"') {
// //             str = str.substr(0, str.length()-1);
// //         }

// //         // Remove spaces
// //         while (!str.empty() && isspace(str[0])) {
// //             str = str.substr(1);
// //         }
// //         while (!str.empty() && isspace(str[str.length()-1])) {
// //             str = str.substr(0, str.length()-1);
// //         }
// //     }

// //     // Check if character is valid for English text
// //     bool isEnglishWordCharacter(char c) {
// //         return isalnum(c) || c == '"' || c == ',' || c==' ';
// //     }

// //     // Read and process data from CSV file
// //     void readData(ifstream& file, bool isTrue) {
// //         string line;
// //         bool firstLine = true;
// //         int& count = isTrue ? trueArticlesCount : fakeArticlesCount;  // Reference to appropriate counter
// //         count = 0;  // Reset counter before reading

// //         while (getline(file, line)) {
// //             if (firstLine) {  // Skip header line
// //                 firstLine = false;
// //                 continue;
// //             }

// //             string title, content, category, date;
// //             int pos = 0;
// //             bool inQuotes = false;
// //             string currentField;
// //             int fieldCount = 0;

// //             // Parse CSV line considering quoted fields
// //             for (int i = 0; i < line.length(); i++) {
// //                 char c = line[i];
                
// //                 if (c == '"') {
// //                     inQuotes = !inQuotes;
// //                 } 
// //                 else if(!isEnglishWordCharacter(c)){
// //                     continue;
// //                 }
// //                 else if (c == ',' && !inQuotes) {
// //                     // Process the completed field
// //                     trimString(currentField);
// //                     switch(fieldCount) {
// //                         case 0: title = currentField; break;
// //                         case 1: content = currentField; break;
// //                         case 2: category = currentField; break;
// //                     }
// //                     currentField.clear();
// //                     fieldCount++;
// //                 } else {
// //                     currentField += c;
// //                 }
// //             }
// //             // Process the last field (date)
// //             trimString(currentField);
// //             date = currentField;

// //             ParseDate(date, year, month, day);

// //             addArticle(title, content, category, date);
// //             count++;  // Increment counter for each article added
// //         }
// //     }

// //     void ParseDate(string& Date, int& year, int& month, int& day){

// //         string field = "", basket="";
// //         int parseStage = 0;
// //         // Manual quote removal and parsing
// //         for (char c : Date) {
// //             if (c == '"') continue;
// //             if (c == ' ' || c == ',') {
// //                 switch(parseStage) {
// //                     case 0: month = monthToNumber(field);break;
// //                     case 1: day = StringToInt(field); break;
// //                     case 2: basket=field; break;// remove leading space from the year field     
// //                     case 3: while (!field.empty() && field[field.length()-1] == ' ') field.erase(field.length()-1); year = StringToInt(field); break;
// //                 }
// //                 field = "";
// //                 parseStage++;
// //             } else {
// //                 field += c;
// //             }
// //         }
// //     }

// //     // an integer method that converts the strings to integers
// //     int StringToInt(string& str) {
// //         int result = 0;
// //         for (char c : str) {
// //             result = result * 10 + (c - '0');
// //         }
// //         return result;
// //     }

// //     int monthToNumber(string month) {
// //         if (month == "January") return 1;
// //         if (month == "February") return 2;
// //         if (month == "March") return 3;
// //         if (month == "April") return 4;
// //         if (month == "May") return 5;
// //         if (month == "June") return 6;
// //         if (month == "July") return 7;
// //         if (month == "August") return 8;
// //         if (month == "September") return 9;
// //         if (month == "October") return 10;
// //         if (month == "November") return 11;
// //         if (month == "December") return 12;
// //         return -1; // Invalid month
// //     }



// //     // Display specified number of articles (or all if rows = -1)
// //     void displayArticles(int rows = -1) const {
// //         int count = 0;
// //         Node* temp = head;
// //         while (temp != nullptr && (rows == -1 || count < rows)) {
// //             cout << "\n--- Article " << count + 1 << " ---\n";
// //             cout << "Title: " << temp->title << "\n";
// //             cout << "Content: " << temp->content << "\n";
// //             cout << "Category: " << temp->category << "\n";
// //             cout << "Date: " << temp->publicationDate << "\n";
// //             temp = temp->next;
// //             count++;
// //         }
// //     }

// //     // Display statistics about the number of articles in each dataset
// //     //NOTE: When main/Interface calls the ReadData function, it will automatically update the article count. 
// //     //Therefore, when the user calls to display the function for the article count, it will display the updated count.
// //     //Reducing time efficiency by not having to loop through the linked list to count the articles again.
// //     void displayArticleCounts() const {
// //         cout << "\n=== Article Count Statistics ===\n";
// //         cout << "True News Articles: " << trueArticlesCount << "\n";
// //         cout << "Fake News Articles: " << fakeArticlesCount << "\n";
// //         cout << "Total Articles: " << (trueArticlesCount + fakeArticlesCount) << "\n";
// //         cout << "==============================\n";
// //     }

// //     // Getter methods for file streams
// //     ifstream& getTrueData() { return trueData; }
// //     ifstream& getFakeData() { return fakeData; }

// //     //HERE
// //     // Add these as public members in the DataManagement class

// //     // Helper function to compare dates (assumes format YYYY-MM-DD)
// //     // bool isDateInRange(const string& articleDate, const string& startDate, const string& endDate) {
// //     //     // Simple string comparison works for YYYY-MM-DD format
// //     //     return articleDate >= startDate && articleDate <= endDate;
// //     // }

// //     // // Helper function to convert string to lowercase for case-insensitive comparison
// //     // string toLowerCase(const string& str) {
// //     //     string result = str;
// //     //     for (char& c : result) {
// //     //         if (c >= 'A' && c <= 'Z') {
// //     //             c = c - 'A' + 'a';
// //     //         }
// //     //     }
// //     //     return result;
// //     // }


// //     //Linear and Binary Search need to move to Algorithms.cpp
// //     // // Optimized Linear Search
// //     // void linearSearch(const string& searchTerm, const string& searchType) {
// //     //     Node* current = head;
// //     //     int matchCount = 0;
// //     //     string searchTermLower = toLowerCase(searchTerm);
        
// //     //     cout << "\n=== Linear Search Results ===\n";
        
// //     //     while (current != nullptr) {
// //     //         bool match = false;
// //     //         string fieldToSearch;
            
// //     //         if (searchType == "category") {
// //     //             fieldToSearch = toLowerCase(current->category);
// //     //         } else if (searchType == "title") {
// //     //             fieldToSearch = toLowerCase(current->title);
// //     //         } else {
// //     //             cout << "Invalid search type\n";
// //     //             return;
// //     //         }
            
// //     //         // Check if searchTerm is a substring of the field
// //     //         if (fieldToSearch.find(searchTermLower) != string::npos) {
// //     //             cout << "\nMatch found:\n";
// //     //             cout << "Title: " << current->title << "\n";
// //     //             cout << "Category: " << current->category << "\n";
// //     //             cout << "Date: " << current->publicationDate << "\n";
// //     //             matchCount++;
// //     //         }
            
// //     //         current = current->next;
// //     //     }
        
// //     //     cout << "\nTotal matches found: " << matchCount << "\n";
// //     // }


// //     // //Binary Search NOT WORKING!!! Fix it
// //     // // Binary Search for dates (searches by year)
// //     // void binarySearchByYear(const string& targetYear) {
// //     //     // First, create a sorted temporary linked list of nodes by year
// //     //     Node* sortedHead = nullptr;
// //     //     Node* current = head;
        
// //     //     // Copy nodes and insert them in sorted order by year
// //     //     while (current != nullptr) {
// //     //         string currentYear = current->publicationDate.substr(0, 4);
// //     //         Node* newNode = new Node(current->title, current->content, 
// //     //                             current->category, current->publicationDate);
            
// //     //         // Insert in sorted order
// //     //         if (sortedHead == nullptr || currentYear < sortedHead->publicationDate.substr(0, 4)) {
// //     //             newNode->next = sortedHead;
// //     //             sortedHead = newNode;
// //     //         } else {
// //     //             Node* temp = sortedHead;
// //     //             while (temp->next != nullptr && 
// //     //                 temp->next->publicationDate.substr(0, 4) < currentYear) {
// //     //                 temp = temp->next;
// //     //             }
// //     //             newNode->next = temp->next;
// //     //             temp->next = newNode;
// //     //         }
            
// //     //         current = current->next;
// //     //     }
        
// //     //     // Perform binary search
// //     //     int matchCount = 0;
// //     //     cout << "\n=== Binary Search Results for Year " << targetYear << " ===\n";
        
// //     //     // Convert linked list to array of pointers for binary search
// //     //     int count = 0;
// //     //     current = sortedHead;
// //     //     while (current != nullptr) {
// //     //         if (current->publicationDate.substr(0, 4) == targetYear) {
// //     //             cout << "\nMatch found:\n";
// //     //             cout << "Title: " << current->title << "\n";
// //     //             cout << "Category: " << current->category << "\n";
// //     //             cout << "Date: " << current->publicationDate << "\n";
// //     //             matchCount++;
// //     //         }
// //     //         current = current->next;
// //     //     }
        
// //     //     cout << "\nTotal matches found: " << matchCount << "\n";
        
// //     //     // Clean up temporary sorted list
// //     //     while (sortedHead != nullptr) {
// //     //         Node* temp = sortedHead;
// //     //         sortedHead = sortedHead->next;
// //     //         delete temp;
// //     //     }
// //     // }

// //     // Test search functionality
// //     void testSearch() {
// //         cout << "\n=== Testing Search Functions ===\n";
        
// //         // Test linear search
// //         cout << "\nTesting Linear Search by Category:\n";
// //         linearSearch("Trump", "title");
        
// //         // cout << "\nTesting Linear Search by Title:\n";
// //         // linearSearch("election", "title");
        
// //         // Test binary search
// //         // cout << "\nTesting Binary Search by Year:\n";
// //         // binarySearchByYear("2017");
// //     }


// // };

// // int main() {
// //     DataManagement data;
// //     data.readData(data.getTrueData(), true);   // Read and count true news articles
// //     data.readData(data.getFakeData(), false);  // Read and count fake news articles
// //     data.displayArticleCounts();               // Show article count statistics
// //     // data.displayArticles(3);                   // Display first 3 articles
// //     // data.testSearch();                          // Test search functionality
    
// //     return 0;
// // }





#include <iostream>
#include <fstream>
#include <string>

#include "../header/LinkedList.hpp"
#include "Algorithms.cpp"
using namespace std;

// Class to manage news articles data
class DataManagement {
private:
    Node* head;
    ifstream trueData;    // File stream for true news dataset
    ifstream fakeData;    // File stream for fake news dataset
    int trueArticlesCount;  // Counter for true articles
    int fakeArticlesCount;  // Counter for fake articles

public:
    LinkedList list;

    // Constructor: Initialize pointers and open data files
    DataManagement() {
        head = nullptr;
        trueArticlesCount = 0;
        fakeArticlesCount = 0;
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

    // // ***** MODIFIED: Add a new article using separate date parts *****
    // void addArticle(const string& title, const string& content, const string& category, int year, int month, int day) {
    //     Node* newNode = new Node(title, content, category, year, month, day);
    //     if (head == nullptr) {
    //         head = newNode;
    //     } else {
    //         Node* temp = head;
    //         while (temp->next != nullptr) {
    //             temp = temp->next;
    //         }
    //         temp->next = newNode;
    //     }
    // }

    // Add a new article using separate date parts
    void addArticle(string& title, string& content, string& category, int year, int month, int day) {
        list.addNode(title, content, category, year, month, day);
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

            // ***** MODIFIED: Parse the date into year, month, day *****
            int year, month, day;
            ParseDate(date, year, month, day);

            // Add the article using separate date parts
            addArticle(title, content, category, year, month, day);
            count++;  // Increment counter for each article added
        }
    }

    
    void ParseDate(string& Date, int& year, int& month, int& day) {
        string field = "";
        int parseStage = 0;
        for (char c : Date) {
            if (c == '"') continue;
            if (c == ' ' || c == ',') {
                if (!field.empty()) {
                    if (parseStage == 0) {
                        // First field: Month (e.g., "December")
                        month = monthToNumber(field);
                    } else if (parseStage == 1) {
                        // Second field: Day (e.g., "31")
                        day = StringToInt(field);
                    } else if (parseStage == 2) {
                        // Third field: Year (e.g., "2017")
                        year = StringToInt(field);
                    }
                    field = "";
                    parseStage++;
                }
            } else {
                field += c;
            }
        }
        // In case the last field (year) hasn't been processed because there was no trailing delimiter:
        if (!field.empty() && parseStage == 2) {
            year = StringToInt(field);
        }
    }


    // an integer method that converts the strings to integers
    int StringToInt(string& str) {
        int result = 0;
        for (char c : str) {
            result = result * 10 + (c - '0');
        }
        return result;
    }

    int monthToNumber(string month) {
        if (month == "January") return 1;
        if (month == "February") return 2;
        if (month == "March") return 3;
        if (month == "April") return 4;
        if (month == "May") return 5;
        if (month == "June") return 6;
        if (month == "July") return 7;
        if (month == "August") return 8;
        if (month == "September") return 9;
        if (month == "October") return 10;
        if (month == "November") return 11;
        if (month == "December") return 12;
        return -1; // Invalid month
    }

    // ***** MODIFIED: Display articles using separate date parts *****
    void displayArticles(int rows = -1) const {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr && (rows == -1 || count < rows)) {
            cout << "\n--- Article " << count + 1 << " ---\n";
            cout << "Title: " << temp->title << "\n";
            cout << "Content: " << temp->content << "\n";
            cout << "Category: " << temp->category << "\n";
            cout << "Date: " 
                 << temp->publicationYear << "-" 
                 << (temp->publicationMonth < 10 ? "0" : "") << temp->publicationMonth << "-" 
                 << (temp->publicationDay < 10 ? "0" : "") << temp->publicationDay << "\n";
            temp = temp->next;
            count++;
        }
    }

    // Display statistics about the number of articles in each dataset
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

    // (Other functions such as search remain unchanged.)

    // Test search functionality
    // void testSearch() {
    //     cout << "\n=== Testing Search Functions ===\n";
        
    //     // Test linear search
    //     cout << "\nTesting Linear Search by Category:\n";
    //     list.linearSearch("Trump", "title");

    //     cout << "\nTesting Binary Search by Year:\n";
    //     list.binarySearchByYear("2017");
    // }

    void testSearch() {
        cout << "\n=== Testing Search Functions ===\n";
        
        // Test linear search
        cout << "\nTesting Linear Search by Category:\n";
        string SearchTerm = "Trump";
        string Field = "title";
        list.linearSearch(SearchTerm, Field);  

        cout << "\nTesting Binary Search by Year:\n";
        string year = "2017";
        list.binarySearchByYear(year); 
    }
};

// Implementation of LinkedList::addNode
void LinkedList::addNode(string& title, string& content, string& category, int year, int month, int day) {
    Node* newNode = new Node(title, content, category, year, month, day);
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

int main() {

    DataManagement data;
    data.readData(data.getTrueData(), true);   // Read and count true news articles
    data.readData(data.getFakeData(), false);    // Read and count fake news articles
    data.displayArticleCounts();                 // Show article count statistics
    // data.displayArticles(3);                  // Display first 3 articles
    data.testSearch();                        // Test search functionality
    
    return 0;
}