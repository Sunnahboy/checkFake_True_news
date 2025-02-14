
#include "../header/PerformanceProfiler.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

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
        return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='-';
    }

    // Read and process data from CSV file
    // void readData(ifstream& file, bool isTrue) {
    //     string line;
    //     bool firstLine = true;
    //     int& count = isTrue ? trueArticlesCount : fakeArticlesCount;  // Reference to appropriate counter
    //     count = 0;  // Reset counter before reading

    //     while (getline(file, line)) {
    //         if (firstLine) {  // Skip header line
    //             firstLine = false;
    //             continue;
    //         }

    //         string title, content, category, date;
    //         bool inQuotes = false;
    //         string currentField;
    //         int fieldCount = 0;

    //         // Parse CSV line considering quoted fields
    //         for (int i = 0; i < line.length(); i++) {
    //             char c = line[i];
                
    //             if (c == '"') {
    //                 inQuotes = !inQuotes;
    //             } 
    //             else if(!isEnglishWordCharacter(c)){
    //                 continue;
    //             }
    //             else if (c == ',' && !inQuotes) {
    //                 // Process the completed field
    //                 trimString(currentField);
    //                 switch(fieldCount) {
    //                     case 0: title = currentField; break;
    //                     case 1: content = currentField; break;
    //                     case 2: category = currentField; break;
    //                 }
    //                 currentField.clear();
    //                 fieldCount++;
    //             } else {
    //                 currentField += c;
    //             }
    //         }
    //         // Process the last field (date)
    //         trimString(currentField);
    //         date = currentField;

    //         // ***** MODIFIED: Parse the date into year, month, day *****
    //         int year, month, day;
    //         ParseDate(date, year, month, day);

    //         // Add the article using separate date parts
    //         addArticle(title, content, category, year, month, day);
    //         count++;  // Increment counter for each article added
    //     }
    // }

    
    // void ParseDate(string& Date, int& year, int& month, int& day) {
    //     string field = "";
    //     int parseStage = 0;
    //     for (char c : Date) {
    //         if (c == '"') continue;
    //         if (c == ' ' || c == ',') {
    //             if (!field.empty()) {
    //                 if (parseStage == 0) {
    //                     // First field: Month (e.g., "December")
    //                     month = monthToNumber(field);
    //                 } else if (parseStage == 1) {
    //                     // Second field: Day (e.g., "31")
    //                     day = StringToInt(field);
    //                 } else if (parseStage == 2) {
    //                     // Third field: Year (e.g., "2017")
    //                     year = StringToInt(field);
    //                 }
    //                 field = "";
    //                 parseStage++;
    //             }
    //         } else {
    //             field += c;
    //         }
    //     }
    //     // In case the last field (year) hasn't been processed because there was no trailing delimiter:
    //     if (!field.empty() && parseStage == 2) {
    //         year = StringToInt(field);
    //     }
    // }

    int fastMonthToNumber(const char* month) {
        static const struct {
            const char* name;
            const char* abbrev;
            int number;
        } months[] = {
            {"January", "Jan", 1}, {"February", "Feb", 2}, {"March", "Mar", 3},
            {"April", "Apr", 4}, {"May", "May", 5}, {"June", "Jun", 6},
            {"July", "Jul", 7}, {"August", "Aug", 8}, {"September", "Sep", 9},
            {"October", "Oct", 10}, {"November", "Nov", 11}, {"December", "Dec", 12}
        };
        
        for (const auto& m : months) {
            if (strcmp(month, m.name) == 0 || strncmp(month, m.abbrev, 3) == 0) {
                return m.number;
            }
        }
        return -1;
    }
    
    void readData(ifstream& file, bool isTrue) {
        string line;
        bool firstLine = true;
        int& count = isTrue ? trueArticlesCount : fakeArticlesCount;
        count = 0;
    
        char fileBuffer[131072];  // 128KB buffer
        file.rdbuf()->pubsetbuf(fileBuffer, sizeof(fileBuffer));
    
        string title, content, category, currentField;
        title.reserve(500);
        content.reserve(10000);
        category.reserve(50);
        currentField.reserve(10000);
    
        while (getline(file, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            if (line.empty()) continue;
    
            title.clear();
            content.clear();
            category.clear();
            currentField.clear();
            bool inQuotes = false, hasEmptyField = false;
            int fieldCount = 0;
    
            for (size_t i = 0; i < line.length(); i++) {
                char c = line[i];
    
                if (c == '"') { 
                    inQuotes = !inQuotes;
                    continue;
                }
                if (!isEnglishWordCharacter(c))
                    continue;
                
                // For the first three fields, use comma as delimiter.
                if (c == ',' && !inQuotes && fieldCount < 3) {
                    if (currentField.empty()) { 
                        hasEmptyField = true; 
                        break; 
                    }
                    switch(fieldCount) {
                        case 0: 
                            title = move(currentField);
                            break;
                        case 1: 
                            content = move(currentField);
                            break;
                        case 2: 
                            category = move(currentField);
                            break;
                    }
                    currentField.clear();
                    fieldCount++;
                }
                // Once we’re in the date field (fieldCount == 3), if we hit a comma outside quotes, ignore the rest.
                else if (c == ',' && !inQuotes && fieldCount == 3) {
                    break;
                }
                else {
                    currentField += c;
                }
            }
            
            // If any field was empty or we didn't get the date field properly, skip this line.
            if (hasEmptyField || fieldCount < 3 || currentField.empty())
                continue;
            
            int year = 0, month = 0, day = 0;
            if (!ParseDate(currentField, year, month, day))
                continue;
            
            addArticle(title, content, category, year, month, day);
            count++;
        }
    }
    
    
    
    bool ParseDate(string& Date, int& year, int& month, int& day) {
        if (Date.empty()) return false;
    
        string field;
        field.reserve(20);
        if (isdigit(Date[0])) {
            size_t pos = 0;
            while (pos < Date.length() && isdigit(Date[pos])) { day = day * 10 + (Date[pos] - '0'); pos++; }
            if (pos < Date.length() && Date[pos] == '-') pos++;
            
            string monthStr;
            while (pos < Date.length() && isalpha(Date[pos])) { monthStr += Date[pos]; pos++; }
            month = fastMonthToNumber(monthStr.c_str());
            
            if (pos < Date.length() && Date[pos] == '-') pos++;
            while (pos < Date.length() && isdigit(Date[pos])) { year = year * 10 + (Date[pos] - '0'); pos++; }
            if (year < 100) year += 2000;
            
            return (month > 0 && day > 0 && year > 0);
        }
        
        int parseStage = 0;
        const char* ptr = Date.c_str();
        while (*ptr) {
            if (*ptr == '"' || *ptr == ' ' || *ptr == ',') {
                if (!field.empty()) {
                    switch(parseStage) {
                        case 0: month = fastMonthToNumber(field.c_str()); break;
                        case 1: day = fastStringToInt(field.c_str()); break;
                        case 3: year = fastStringToInt(field.c_str()); break;
                    }
                    if ((parseStage == 0 && month == -1) || (parseStage == 1 && day == 0) || (parseStage == 3 && year == 0))
                        return false;
                    field.clear();
                    parseStage++;
                }
                ptr++;
            } else {
                field += *ptr++;
            }
        }
        
        if (!field.empty() && parseStage <= 3) year = fastStringToInt(field.c_str());
        return (month > 0 && day > 0 && year > 0);
    }
    

    // Optimized string to integer conversion
    inline int fastStringToInt(const char* str) {
        int result = 0;
        while (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str++ - '0');
        }
        return result;
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


    void sortArticles() {
        
        cout << "Sorting articles..." << endl; // Debugging line
        list.head = list.bottomUpMergeSort(list.head); // Sort the linked list
        cout << "Articles sorted." << endl; // Debugging line
    }

    void DisplayArticles(int rows = -1) const {
        cout << "Displaying articles..." << endl; // Debugging line
        int count = 0;
        Node* temp = list.head; // Assuming head is the pointer to the start of the linked list
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
        if (count == 0) {
            cout << "No articles to display." << endl; // Debugging line
        }
    }
};

// Implementation of LinkedList::addNode
void LinkedList::addNode(string& title, string& content, string& category, int year, int month, int day) {
    Node* newNode = new Node(title, content, category, year, month, day);
    if (head == nullptr) {
        head = newNode;
       // cout << "Added first article: " << title << endl; 
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        //cout << "Added article: " << title << endl;
    }
}


int main() {

    DataManagement data;
    data.readData(data.getTrueData(), true);   // Read and count true news articles
    data.readData(data.getFakeData(), false);    // Read and count fake news articles
    //data.displayArticleCounts();                 // Show article count statistics
    // data.displayArticles(3);                  // Display first 3 articles
    // data.testSearch();  
    //data.displayArticles();                       // Test search functionality
    //data.sortArticles();  
    //data.DisplayArticles(); 
    profileAlgorithm("Merge Sort", "O(n log n)", "The algorithm does not require extra space but the linked list nodes do consume memory.O(1)", [&data]() { data.sortArticles(); });

    return 0;
}   