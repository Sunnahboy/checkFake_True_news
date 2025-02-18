<<<<<<< HEAD
=======
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <cstring>

// #include "../header/LinkedList.hpp"
// #include "Algorithms.cpp"
// using namespace std;

// // Class to manage news articles data
// class DataManagement {
// private:
//     Node* head;
//     ifstream trueData;    // File stream for true news dataset
//     ifstream fakeData;    // File stream for fake news dataset
//     int trueArticlesCount;  // Counter for true articles
//     int fakeArticlesCount;  // Counter for fake articles

// public:
//     LinkedList list;

//     // Constructor: Initialize pointers and open data files
//     DataManagement() {
//         head = nullptr;
//         trueArticlesCount = 0;
//         fakeArticlesCount = 0;
//         trueData.open("../dataSets/true.csv");
//         fakeData.open("../dataSets/fake.csv");
//         if (!trueData.is_open() || !fakeData.is_open()) {
//             cout << "Error in reading the file" << endl;
//         }
//     }
    
//     // Destructor: Clean up memory and close files
//     ~DataManagement() {
//         while (head != nullptr) {
//             Node* temp = head;
//             head = head->next;
//             delete temp;
//         }
        
//         if (trueData.is_open()) trueData.close();
//         if (fakeData.is_open()) fakeData.close();
//     }

//     // // ***** MODIFIED: Add a new article using separate date parts *****
//     // void addArticle(const string& title, const string& content, const string& category, int year, int month, int day) {
//     //     Node* newNode = new Node(title, content, category, year, month, day);
//     //     if (head == nullptr) {
//     //         head = newNode;
//     //     } else {
//     //         Node* temp = head;
//     //         while (temp->next != nullptr) {
//     //             temp = temp->next;
//     //         }
//     //         temp->next = newNode;
//     //     }
//     // }

//     // Add a new article using separate date parts
//     void addArticle(string& title, string& content, string& category, int year, int month, int day) {
//         list.addNode(title, content, category, year, month, day);
//     }



//     // Remove unnecessary characters and spaces from strings
//     void trimString(string& str) {
//         // Remove quotes if present
//         if (!str.empty() && str[0] == '"') {
//             str = str.substr(1);
//         }
//         if (!str.empty() && str[str.length()-1] == '"') {
//             str = str.substr(0, str.length()-1);
//         }

//         // Remove spaces
//         while (!str.empty() && isspace(str[0])) {
//             str = str.substr(1);
//         }
//         while (!str.empty() && isspace(str[str.length()-1])) {
//             str = str.substr(0, str.length()-1);
//         }
//     }

//     // Check if character is valid for English text
//     bool isEnglishWordCharacter(char c) {
//         return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='-';
//     }

//     // Read and process data from CSV file
//     // void readData(ifstream& file, bool isTrue) {
//     //     string line;
//     //     bool firstLine = true;
//     //     int& count = isTrue ? trueArticlesCount : fakeArticlesCount;  // Reference to appropriate counter
//     //     count = 0;  // Reset counter before reading

//     //     while (getline(file, line)) {
//     //         if (firstLine) {  // Skip header line
//     //             firstLine = false;
//     //             continue;
//     //         }

//     //         string title, content, category, date;
//     //         bool inQuotes = false;
//     //         string currentField;
//     //         int fieldCount = 0;

//     //         // Parse CSV line considering quoted fields
//     //         for (int i = 0; i < line.length(); i++) {
//     //             char c = line[i];
                
//     //             if (c == '"') {
//     //                 inQuotes = !inQuotes;
//     //             } 
//     //             else if(!isEnglishWordCharacter(c)){
//     //                 continue;
//     //             }
//     //             else if (c == ',' && !inQuotes) {
//     //                 // Process the completed field
//     //                 trimString(currentField);
//     //                 switch(fieldCount) {
//     //                     case 0: title = currentField; break;
//     //                     case 1: content = currentField; break;
//     //                     case 2: category = currentField; break;
//     //                 }
//     //                 currentField.clear();
//     //                 fieldCount++;
//     //             } else {
//     //                 currentField += c;
//     //             }
//     //         }
//     //         // Process the last field (date)
//     //         trimString(currentField);
//     //         date = currentField;

//     //         // ***** MODIFIED: Parse the date into year, month, day *****
//     //         int year, month, day;
//     //         ParseDate(date, year, month, day);

//     //         // Add the article using separate date parts
//     //         addArticle(title, content, category, year, month, day);
//     //         count++;  // Increment counter for each article added
//     //     }
//     // }

    
//     // void ParseDate(string& Date, int& year, int& month, int& day) {
//     //     string field = "";
//     //     int parseStage = 0;
//     //     for (char c : Date) {
//     //         if (c == '"') continue;
//     //         if (c == ' ' || c == ',') {
//     //             if (!field.empty()) {
//     //                 if (parseStage == 0) {
//     //                     // First field: Month (e.g., "December")
//     //                     month = monthToNumber(field);
//     //                 } else if (parseStage == 1) {
//     //                     // Second field: Day (e.g., "31")
//     //                     day = StringToInt(field);
//     //                 } else if (parseStage == 2) {
//     //                     // Third field: Year (e.g., "2017")
//     //                     year = StringToInt(field);
//     //                 }
//     //                 field = "";
//     //                 parseStage++;
//     //             }
//     //         } else {
//     //             field += c;
//     //         }
//     //     }
//     //     // In case the last field (year) hasn't been processed because there was no trailing delimiter:
//     //     if (!field.empty() && parseStage == 2) {
//     //         year = StringToInt(field);
//     //     }
//     // }

//     int fastMonthToNumber(const char* month) {
//         static const struct {
//             const char* name;
//             const char* abbrev;
//             int number;
//         } months[] = {
//             {"January", "Jan", 1}, {"February", "Feb", 2}, {"March", "Mar", 3},
//             {"April", "Apr", 4}, {"May", "May", 5}, {"June", "Jun", 6},
//             {"July", "Jul", 7}, {"August", "Aug", 8}, {"September", "Sep", 9},
//             {"October", "Oct", 10}, {"November", "Nov", 11}, {"December", "Dec", 12}
//         };
        
//         for (const auto& m : months) {
//             if (strcmp(month, m.name) == 0 || strncmp(month, m.abbrev, 3) == 0) {
//                 return m.number;
//             }
//         }
//         return -1;
//     }
    
//     void readData(ifstream& file, bool isTrue) {
//         string line;
//         bool firstLine = true;
//         int& count = isTrue ? trueArticlesCount : fakeArticlesCount;
//         count = 0;
    
//         char fileBuffer[131072];  // 128KB buffer
//         file.rdbuf()->pubsetbuf(fileBuffer, sizeof(fileBuffer));
    
//         string title, content, category, currentField;
//         title.reserve(500);
//         content.reserve(10000);
//         category.reserve(50);
//         currentField.reserve(10000);
    
//         while (getline(file, line)) {
//             if (firstLine) {
//                 firstLine = false;
//                 continue;
//             }
//             if (line.empty()) continue;
    
//             title.clear();
//             content.clear();
//             category.clear();
//             currentField.clear();
//             bool inQuotes = false, hasEmptyField = false;
//             int fieldCount = 0;
    
//             for (size_t i = 0; i < line.length(); i++) {
//                 char c = line[i];
    
//                 if (c == '"') { 
//                     inQuotes = !inQuotes;
//                     continue;
//                 }
//                 if (!isEnglishWordCharacter(c))
//                     continue;
                
//                 // For the first three fields, use comma as delimiter.
//                 if (c == ',' && !inQuotes && fieldCount < 3) {
//                     if (currentField.empty()) { 
//                         hasEmptyField = true; 
//                         break; 
//                     }
//                     switch(fieldCount) {
//                         case 0: 
//                             title = move(currentField);
//                             break;
//                         case 1: 
//                             content = move(currentField);
//                             break;
//                         case 2: 
//                             category = move(currentField);
//                             break;
//                     }
//                     currentField.clear();
//                     fieldCount++;
//                 }
//                 // Once we’re in the date field (fieldCount == 3), if we hit a comma outside quotes, ignore the rest.
//                 else if (c == ',' && !inQuotes && fieldCount == 3) {
//                     break;
//                 }
//                 else {
//                     currentField += c;
//                 }
//             }
            
//             // If any field was empty or we didn't get the date field properly, skip this line.
//             if (hasEmptyField || fieldCount < 3 || currentField.empty())
//                 continue;
            
//             int year = 0, month = 0, day = 0;
//             if (!ParseDate(currentField, year, month, day))
//                 continue;
            
//             addArticle(title, content, category, year, month, day);
//             count++;
//         }
//     }
    
    
    
//     bool ParseDate(string& Date, int& year, int& month, int& day) {
//         if (Date.empty()) return false;
    
//         string field;
//         field.reserve(20);
//         if (isdigit(Date[0])) {
//             size_t pos = 0;
//             while (pos < Date.length() && isdigit(Date[pos])) { day = day * 10 + (Date[pos] - '0'); pos++; }
//             if (pos < Date.length() && Date[pos] == '-') pos++;
            
//             string monthStr;
//             while (pos < Date.length() && isalpha(Date[pos])) { monthStr += Date[pos]; pos++; }
//             month = fastMonthToNumber(monthStr.c_str());
            
//             if (pos < Date.length() && Date[pos] == '-') pos++;
//             while (pos < Date.length() && isdigit(Date[pos])) { year = year * 10 + (Date[pos] - '0'); pos++; }
//             if (year < 100) year += 2000;
            
//             return (month > 0 && day > 0 && year > 0);
//         }
        
//         int parseStage = 0;
//         const char* ptr = Date.c_str();
//         while (*ptr) {
//             if (*ptr == '"' || *ptr == ' ' || *ptr == ',') {
//                 if (!field.empty()) {
//                     switch(parseStage) {
//                         case 0: month = fastMonthToNumber(field.c_str()); break;
//                         case 1: day = fastStringToInt(field.c_str()); break;
//                         case 3: year = fastStringToInt(field.c_str()); break;
//                     }
//                     if ((parseStage == 0 && month == -1) || (parseStage == 1 && day == 0) || (parseStage == 3 && year == 0))
//                         return false;
//                     field.clear();
//                     parseStage++;
//                 }
//                 ptr++;
//             } else {
//                 field += *ptr++;
//             }
//         }
        
//         if (!field.empty() && parseStage <= 3) year = fastStringToInt(field.c_str());
//         return (month > 0 && day > 0 && year > 0);
//     }
    

//     // Optimized string to integer conversion
//     inline int fastStringToInt(const char* str) {
//         int result = 0;
//         while (*str >= '0' && *str <= '9') {
//             result = result * 10 + (*str++ - '0');
//         }
//         return result;
//     }


//     // an integer method that converts the strings to integers
//     int StringToInt(string& str) {
//         int result = 0;
//         for (char c : str) {
//             result = result * 10 + (c - '0');
//         }
//         return result;
//     }

//     int monthToNumber(string month) {
//         if (month == "January") return 1;
//         if (month == "February") return 2;
//         if (month == "March") return 3;
//         if (month == "April") return 4;
//         if (month == "May") return 5;
//         if (month == "June") return 6;
//         if (month == "July") return 7;
//         if (month == "August") return 8;
//         if (month == "September") return 9;
//         if (month == "October") return 10;
//         if (month == "November") return 11;
//         if (month == "December") return 12;
//         return -1; // Invalid month
//     }

//     // ***** MODIFIED: Display articles using separate date parts *****
//     void displayArticles(int rows = -1) const {
//         int count = 0;
//         Node* temp = head;
//         while (temp != nullptr && (rows == -1 || count < rows)) {
//             cout << "\n--- Article " << count + 1 << " ---\n";
//             cout << "Title: " << temp->title << "\n";
//             cout << "Content: " << temp->content << "\n";
//             cout << "Category: " << temp->category << "\n";
//             cout << "Date: " 
//                  << temp->publicationYear << "-" 
//                  << (temp->publicationMonth < 10 ? "0" : "") << temp->publicationMonth << "-" 
//                  << (temp->publicationDay < 10 ? "0" : "") << temp->publicationDay << "\n";
//             temp = temp->next;
//             count++;
//         }
//     }

//     // Display statistics about the number of articles in each dataset
//     void displayArticleCounts() const {
//         cout << "\n=== Article Count Statistics ===\n";
//         cout << "True News Articles: " << trueArticlesCount << "\n";
//         cout << "Fake News Articles: " << fakeArticlesCount << "\n";
//         cout << "Total Articles: " << (trueArticlesCount + fakeArticlesCount) << "\n";
//         cout << "==============================\n";
//     }

//     // Getter methods for file streams
//     ifstream& getTrueData() { return trueData; }
//     ifstream& getFakeData() { return fakeData; }

//     // (Other functions such as search remain unchanged.)

//     // Test search functionality
//     // void testSearch() {
//     //     cout << "\n=== Testing Search Functions ===\n";
        
//     //     // Test linear search
//     //     cout << "\nTesting Linear Search by Category:\n";
//     //     list.linearSearch("Trump", "title");

//     //     cout << "\nTesting Binary Search by Year:\n";
//     //     list.binarySearchByYear("2017");
//     // }

//     void testSearch() {
//         cout << "\n=== Testing Search Functions ===\n";
        
//         // Test linear search
//         cout << "\nTesting Linear Search by Category:\n";
//         string SearchTerm = "Trump";
//         string Field = "title";
//         list.linearSearch(SearchTerm, Field);  

//         cout << "\nTesting Binary Search by Year:\n";
//         string year = "2017";
//         list.binarySearchByYear(year); 
//     }
// };

// // Implementation of LinkedList::addNode
// void LinkedList::addNode(string& title, string& content, string& category, int year, int month, int day) {
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

// int main() {

//     DataManagement data;
//     data.readData(data.getTrueData(), true);   // Read and count true news articles
//     data.readData(data.getFakeData(), false);    // Read and count fake news articles
//     data.displayArticleCounts();                 // Show article count statistics
//     // data.displayArticles(3);                  // Display first 3 articles
//     // data.testSearch();                        // Test search functionality
    
//     return 0;
// }   





>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
<<<<<<< HEAD
#include "header/LinkedList.hpp"
#include "header/MasterList.hpp"
#include "header/LinkedList_Manipulation.hpp"
#include "header/llhashmap.hpp"
#include "header/NewsArticle.hpp"
=======
#include "../header/LinkedList.hpp"
#include "../header/LinkedList_Manipulation.hpp"
>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6
using namespace std;


dataManagement::dataManagement(string listname){
    size=0;
    head = nullptr;
    tail = nullptr;
    this -> ListName=listname;
    TrueData.open("dataSets/true.csv");
    FakeData.open("dataSets/fake.csv");
    if(!TrueData.is_open() || !FakeData.is_open()){
        cout << "Error in reading the file";
    }
}

article * dataManagement::CreateNewNode(string Title, string Content, string Category, int Day, int Month, int Year){
    article * newArticle=new article();
    newArticle -> title =Title;
    newArticle -> content =Content;
    newArticle -> category=Category;
    newArticle -> day= Day;
    newArticle -> month= Month;
    newArticle -> year= Year;
    newArticle -> next =nullptr;
    return newArticle;
}

void dataManagement::addArticlefromFront(string Title, string Content, string Category, int Day, int Month, int Year){
    article* NewArticle=CreateNewNode(Title, Content,Category,  Day, Year, Month);
    if(head==nullptr){
        head=NewArticle;
    }else{
        NewArticle -> next = head;
        head=NewArticle;
    }
    size++;
}

void dataManagement::addArticlefromEnd(string Title, string Content, string Category, int Day, int Month, int Year) {
    article* NewArticle = CreateNewNode(Title, Content, Category, Day, Month, Year);
    
    if (head == nullptr) {  
        head = NewArticle;
        tail = NewArticle;  // Set tail if it's the first node
    } else {
        tail->next = NewArticle;  // Directly link the last node to new node
        tail = NewArticle;        // Update tail pointer
    }
    size++;  
}



void dataManagement::ReadData(ifstream& file){
    bool QuotedFlag=false;
    string Line, CurrentField, Date;
    int i=0; //To add elements into the 2D array
    int maxGarbage=1000;
    string garbageCollector[maxGarbage];
    int garbageIndex=0;
    while(getline(file, Line)){

        string title, content, category;
        //we create the index to parse the elements inside the file
        int index=0;
        //current field is initially set to none
        CurrentField="";
        //we make a loop to read the data and parse each character
        for(size_t j=0; j < Line.length(); j++){
            char c=Line[j];

            if(c=='"'){
                //if we found a quote the flag set to True
                QuotedFlag=!QuotedFlag;
                CurrentField+=c;//we add the quates to the field
            }else if (!isEnglishWordCharacter(c)){
                continue;
            }
            else if(c==',' && !QuotedFlag){
                if(!CurrentField.empty()){
                    
                    if(index==0){
                        title=CurrentField;
                    }else if(index==1){
                        content=CurrentField;
                    }else if (index==2){
                        category=CurrentField;
                    }
                }
                CurrentField=""; //we have to reset the current field
                index++;
            }else{
                //if none of the condition were True we reset the index
                CurrentField+=c;
            }
                //if we encouter a comma after the quates then we will specify each field based on the index
        }
        if(!CurrentField.empty()){
            Date= CurrentField;
            int year, month, day;
            if(!ParseDate(Date, year, month, day)){
                if(garbageIndex < maxGarbage){
                    garbageCollector[garbageIndex++]=Line;
                }
                continue;
            }
            
            addArticlefromEnd(title, content, category, day, month, year);
        }
        if (head != nullptr) {
            size++;
        }
    }
        file.clear();
        cout << "Data Loading Complete!" << endl; 
}
        

bool dataManagement::ParseDate(string& Date, int& year, int& month, int& day) {
    string field = "";
    int parseStage = 0;

    if(Date.find('-')!=string::npos){
        //format DD-MMM-YYYY
        int dashcount=0;
        for(char c :Date){
            if(c=='-'){
                if(dashcount==0){
                    day=StringToInt(field);
                }
                else if(dashcount==1){
                    month=monthToNumber(field);
                }
                field="";
                dashcount++;
            }else{
                field+=c;
            }
        }
        year=StringToInt(field);
    }else{
    
        // Manual quote removal and parsing
        for (char c : Date) {
            if (c == '"') continue;  // Skip quotes
            
            if (c == ' ' || c == ',') {
                switch(parseStage) {
                    case 0: 
                        month = monthToNumber(field);
                        break;
                    case 1: 
                    day = StringToInt(field); 
                        break;
                        case 2: 
                        // Skipping space
                        break;
                    case 3:
                        while (!field.empty() && field[field.length()-1] == ' ')
                            field.erase(field.length()-1);
                        year = StringToInt(field);
                        break;
                }
                field = "";
                parseStage++;
            } else {
                field += c;
            }
        }

        if (!field.empty() && parseStage == 3) {
            while (!field.empty() && field[field.length()-1] == ' ')
                field.erase(field.length()-1);
            year = StringToInt(field);
        }
    }
    if(year <=0){
        return false;
    }
    return true;
}
    


bool dataManagement::isEnglishWordCharacter(char c) {
    return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='\'';
}       

int dataManagement::getsize(){
    return size;
}

article * dataManagement::gethead(){
    return head;
}
// an integer method that converts the strings to integers
int dataManagement::StringToInt(string& str) {
    int result = 0;
    for (char c : str) {
        result = result * 10 + (c - '0');
    }
    return result;
}



int dataManagement::monthToNumber(string month) {
    if (month == "January" || month=="Jan") return 1;
    if (month == "February" || month=="Feb") return 2;
    if (month == "March" || month=="Mar") return 3;
    if (month == "April" || month=="Apr") return 4;
    if (month == "May") return 5;
    if (month == "June" || month=="Jun") return 6;
    if (month == "July" || month=="Jul") return 7;
    if (month == "August" || month=="Aug") return 8;
    if (month == "September" || month=="Sep") return 9;
    if (month == "October" || month=="Oct") return 10;
    if (month == "November" || month=="Nov") return 11;
    if (month == "December" || month=="Dec") return 12;
    return -1; // Invalid month
}

dataManagement::~dataManagement(){
    cout << "List of "<< ListName << " is removed from the memory now" <<endl;
}


ifstream& dataManagement::getTrueData(){
    return TrueData;
}
ifstream& dataManagement::getFakeData(){
    return FakeData;
}

void dataManagement::displayArticlesfromFront(){
    article * temp=head;
    int i=0;
    while(temp != nullptr){
        cout << " Row Number: " << 1+i <<endl;
        cout << "Title: " << temp -> title <<endl; 
        cout << "Text: " << temp -> content<<endl<<endl; 
        cout << "Subject: " << temp -> category<<endl; 
        cout <<"Year: "<< temp -> year<<endl; 
        cout <<"Month: "<< temp -> month<<endl; 
        cout <<"Day: "<< temp -> day<<endl; 
        cout <<"Total Rows: "<< getsize()<<endl; 
        cout << string(166,'=');
        cout <<endl;
        temp = temp -> next;
        i++;
    }
}

// void dataManagement::ApplySort(int size){
//     dataManagement data;
//     int* newYear= new int[size];
//     int* index=new int[size];
//     for (int i=0; i<size; i++){
//         newYear[i]=article[i].publicationYear;
//         index[i]=i;
//     }
//     algo.MergeSort(newYear, 0, size-1, index);
   
//     string** arr=SortToArray(size-1, index);
//     head(arr, currentSize);
//     for (int i = 0; i < size; i++) {
//         delete[] arr[i];
//     }
//     delete[] arr;

// }

// bool RegInput(int value){
//             return (value==3||value==2||value==1);
// }

// bool RegInput2(int value){
//     return (value==5 ||value==4||value==3||value==2||value==1);
// }

// bool RegInput3(int value){
//     return (value==6||value==5 ||value==4||value==3||value==2||value==1);
// }

<<<<<<< HEAD
void dataManagement::tokenizeWords(article * Node) {
    MasterList wordList; // Using MasterList instead of hashmap or arrays

    // List of filler words to ignore
    const string filler_words[] = {
        "a", "the", "is", "it", "to", "and", "of", "on", "for", "in", "at", "this",
        "that", "was", "were", "with", "between", "infront", "have", "had", "has", 
        "been", "about", "into", "are", "after", "before", "not", "where", "when", "thus"
    };
    int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);

    article* temp = Node; // Start from the first article node

    while (temp != nullptr) {
        if (temp->category != "Government News") { // Filter government-related news
            temp = temp->next;
            continue;
        }

        string text = temp->content; // Extract content from article
        string word = ""; // Temporary string for building words

        for (char c : text) {
            c = tolower(c); // Convert to lowercase
            if (isspace(c) || ispunct(c)) { // Check for word boundaries
                if (!word.empty()) { // If a word has been formed
                    // Check if it's a filler word
                    bool isFiller = false;
                    for (int k = 0; k < filler_size; k++) {
                        if (word == filler_words[k]) {
                            isFiller = true;
                            break;
                        }
                    }
                    if (!isFiller) {
                        wordList.insertOrUpdate(word); // Insert word into MasterList
                    }
                    word = ""; // Reset for next word
                }
            } else {
                word += c; // Add character to word
            }
        }

        // Insert last word if exists
        if (!word.empty()) {
            bool isFiller = false;
            for (int k = 0; k < filler_size; k++) {
                if (word == filler_words[k]) {
                    isFiller = true;
                    break;
                }
            }
            if (!isFiller) {
                wordList.insertOrUpdate(word);
            }
        }

        temp = temp->next; // Move to the next article
    }

    wordList.displayWords();
}


void dataManagement::tokenizeWordsHash(article* Node) {
    HashMap wordMap; // Using HashMap instead of arrays

    // List of filler words to ignore
    const string filler_words[] = {
        "a", "the", "is", "it", "to", "and", "of", "on", "for", "in", "at", "this",
        "that", "was", "were", "with", "between", "infront", "have", "had", "has",
        "been", "about", "into", "are", "after", "before", "not", "where", "when", "thus"
    };
    int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);

    article* temp = Node; // Start from the first article node

    while (temp != nullptr) {
        if (temp->category != "Government News") { // Filter only government news
            temp = temp->next;
            continue;
        }

        string text = temp->content; // Extract content from the article
        string word = ""; // Temporary string for building words

        for (char c : text) {
            c = tolower(c); // Convert to lowercase
            if (isspace(c) || ispunct(c)) { // Check for word boundaries
                if (!word.empty()) { // If a word has been formed
                    // Check if it's a filler word
                    bool isFiller = false;
                    for (int k = 0; k < filler_size; k++) {
                        if (word == filler_words[k]) {
                            isFiller = true;
                            break;
                        }
                    }
                    if (!isFiller) {
                        wordMap.insert(word); // Insert word into the linked list HashMap
                    }
                    word = ""; // Reset for next word
                }
            } else {
                word += c; // Add character to word
            }
        }

        // Insert last word if exists
        if (!word.empty()) {
            bool isFiller = false;
            for (int k = 0; k < filler_size; k++) {
                if (word == filler_words[k]) {
                    isFiller = true;
                    break;
                }
            }
            if (!isFiller) {
                wordMap.insert(word);
            }
        }

        temp = temp->next; // Move to the next article
    }

    // Get keys and frequencies from HashMap
    FreqTextWords* wordlist = wordMap.getKeysAndFrequencies();
        cout << "\nTop 20 Most Frequent Words in Government Fake News:\n";
        while(wordlist) {
            cout << wordlist ->word << " - " << wordlist -> freq << " times\n";
            wordlist=wordlist -> next;
        }
}
=======
// void dataManagement::tokenizeWords(string** array) {
//     ArraysAlgo algo;
//     HashMap hashmap;
//     string filler_words[] = {"a", "the", "is", "it", "to", "and", "of", "on", 
//                             "for", "in", "at", "this", "that", "was", "were", "with", "between", "infront",
//                             "have", "had", "has", "been", "about", "into", "are", "after", "before", "not", "where", "when","those", "thus"};    
//     int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);
//     for (int i = 0; i < currentSize; i++) {
//         if(array[i][2].compare("Government News")!=0) continue; //filter the data only the government once are taken
//         string text = array[i][1];  // Extract text from article
//         string word = ""; // Temporary string for building words
//         // Loop through each character in the text
//         for (char c : text) {
//             // Convert to lowercase
//             c = tolower(c);
//             // Check for word boundaries
//             if (isspace(c) || ispunct(c)) {
//                 if (!word.empty()) { // If a word has been formed
//                     // Check if it's a filler array
//                     bool isFiller = false;
//                     for (int k = 0; k < filler_size; k++) {
//                         if (word == filler_words[k]) {
//                             isFiller = true;
//                             break;
//                         }
//                     }
//                     if (!isFiller) {
//                         hashmap.insert(word);
//                     }
//                     word = ""; 
//                 }
//             } else {
//                 word += c;
//             }
//         }
//     }
//     auto result=hashmap.getKeysAndFrequencies();
//     string* keys=result.first;
//     int* freq=result.second;
//     algo.QuickSort(freq, hashmap.getCount(), 1);
//     cout << "Word Frequency List:\n";
//     for(int i=0; i <20; i++){
//         cout << freq[i] << " :: " << keys[i] << endl;
//     }

//     delete[] keys;
//     delete[] freq;
// }


// void dataManagement::tokenizeWords(string** array) {
//     ArraysAlgo algo;
//     int capacity=1000;
//     string* wordsList = new string[capacity];  
//     int* wordsFreq = new int[capacity];     
//     string filler_words[] = {"a", "the", "is", "it", "to", "and", "of", "on", 
//                             "for", "in", "at", "this", "that", "was", "were", "with", "between", "infront",
//                             "have", "had", "has", "been", "about", "into", "are", "after", "before", "not", "where", "when","those", "thus"};    
//     int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);
//     int Unique = 0; 
//     for (int i = 0; i < size; i++) {
//         if(array[i][2].compare("Government News")!=0) continue; //filter the data only the government once are taken
//         string text = array[i][1];  // Extract text from article
//         string word = ""; // Temporary string for building words

//         // Loop through each character in the text
//         for (char c : text) {
//             // Convert to lowercase
//             c = tolower(c);
//             // Check for word boundaries
//             if (isspace(c) || ispunct(c)) {
//                 if (!word.empty()) { // If a word has been formed
//                     // Check if it's a filler array
//                     bool isFiller = false;
//                     for (int k = 0; k < filler_size; k++) {
//                         if (word == filler_words[k]) {
//                             isFiller = true;
//                             break;
//                         }
//                     }
                
//                     if (!isFiller) {
//                         bool found = false;
//                         for (int v = 0; v < Unique; v++) {
//                             if (wordsList[v] == word) {
//                                 wordsFreq[v] += 1;  
//                                 found = true;
//                                 break;
//                             }
//                         }
//                         if (!found) { 
//                             if(Unique==capacity){
//                                 int newcap= capacity*2;
//                                 resizeArray(wordsList, capacity, newcap);
//                                 resizeArray(wordsFreq, capacity, newcap);
//                                 capacity=newcap;
//                             }
//                             wordsList[Unique] =word;
//                             wordsFreq[Unique] = 1;
//                             Unique++;
//                         }
//                     }
//                     word = ""; 
//                 }
//             } else {
//                 word += c;
//             }
//         }
//     }
//     algo.QuickSort(wordsFreq, Unique, 1);
//     cout << "Word Frequency List:\n";
//     for(int i=0; i <20; i++){
//         cout << wordsList[i] << " :: " << wordsFreq[i] << endl;
//     }

//     delete[] wordsList;
//     delete[] wordsFreq;
// }

>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6

// template <typename Any>
// void dataManagement::resizeArray2(Any*& arr, int old, int newS){
//     Any* temp=new Any[newS];
//     int Iterations=(old < newS) ? old : newS;
//     for(int i=0; i <Iterations; i++){
//         temp[i]=arr[i];
//     }
//     delete []arr;
//     arr=temp;
<<<<<<< HEAD

=======
>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6
// }

bool RegInput(int value){
    return (value==3||value==2||value==1);
}

bool RegInput2(int value){
return (value==5 ||value==4||value==3||value==2||value==1);
}

bool RegInput3(int value){
return (value==6||value==5 ||value==4||value==3||value==2||value==1);
}

<<<<<<< HEAD
void dataManagement::runNewsProcessor(article* head, string datasetChoice) {
    NewsArticleProcessor processor;
    
    
    processor.processArticles(head); // Pass the linked list to process
    int option;
    cout << "\nSelect analysis type:\n";
    cout << "1. View articles per year\n";
    cout << "2. View articles per month\n";
    cout << "3. View articles per day\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    while (!(cin >> option)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 1 and 4.\n";
    }
    int year, month, day;

    switch (option) {
        case 1:
            cout << "Enter year: ";
            cin >> year;
            while (!processor.isValidYear(year, datasetChoice)) {
                cout << "Invalid year. Try again.\nEnter year: ";
                cin >> year;
            }
            processor.displayTable("Articles in " + to_string(year), processor.getArticleCount(year));
            break;
        
        case 2:
            cout << "Enter year: ";
            cin >> year;
            while (!processor.isValidYear(year, datasetChoice)) {
                cout << "Invalid year. Try again.\nEnter year: ";
                cin >> year;
            }
            
            cout << "Enter month (1-12): ";
            cin >> month;
            while (!processor.isValidMonth(month)) {
                cout << "Invalid month. Try again.\nEnter month (1-12): ";
                cin >> month;
            }
            
            processor.displayTable("Articles in " + to_string(year) + " - Month " + to_string(month), processor.getArticleCount(year, month));
            break;
        
        case 3:
            cout << "Enter year: ";
            cin >> year;
            while (!processor.isValidYear(year, datasetChoice)) {
                cout << "Invalid year. Try again.\nEnter year: ";
                cin >> year;
            }
            
            cout << "Enter month (1-12): ";
            cin >> month;
            while (!processor.isValidMonth(month)) {
                cout << "Invalid month. Try again.\nEnter month (1-12): ";
                cin >> month;
            }
            
            cout << "Enter day: ";
            cin >> day;
            while (!processor.isValidDay(year, month, day)) {
                cout << "Invalid day. Try again.\nEnter day: ";
                cin >> day;
            }
            
            processor.displayTable("Articles in " + to_string(year) + " - Month " + to_string(month) + " - Day " + to_string(day), processor.getArticleCount(year, month, day));
            break;
        
        default:
            cout << "Invalid option selected.";
            break;
    }
    
}

=======
>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6


/*
We can add more functions here in this point
*/

int main() {
    dataManagement Data("News Articles");
    LinkedListAlgo algo;
<<<<<<< HEAD
    Data.ReadData(Data.getTrueData());
    // Use linked list head directly
    Data.runNewsProcessor(Data.gethead(), "true");
    // Data.displayArticlesfromEnd();
   // Data.tokenizeWordsHash(Data.gethead());
    // cout << Data.getsize();
    // Data.head(array, 9028);
    // Data.ApplySort(Data.getsize());
    // int choice;
    // int choice2;
    // string field;
    // cout << " Select Searching Algorithm" << endl;
    // cout << "1. Linear Search" << endl;
    // cout << "2. Binary Search" << endl;
    // cout << "3. Return to Arrays Menu" << endl;
    // cout << "Please Enter your choice.... ";
    // while(!(cin>>choice)|| !(RegInput(choice))){
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //     cout << "Invalid.. Please Enter your choice again.... ";
    // }
    // cout << "Chose a field to search for"<<endl;
    // cout << "1. Title "<<endl; 
    // cout << "2. Text "<<endl;
    // cout << "3. Subject "<<endl;
    // cout << "4. Year "<<endl;
    // cout << "5. Month "<<endl;
    // cout << "6. Day "<<endl;
    // cout << "Please Enter your choice.... ";
    // while(!(cin>>choice2)|| !(RegInput3(choice2))){
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //     cout << "Invalid.. Please Enter your choice again.... ";
    // }
    // cin.ignore();
    // cout << "Enter the keyword or value to search for: ";
    // getline(cin, field);
    
    // if (choice == 1) {
    //         algo.linearSearch(Data.gethead(), choice2-1, field);
    // } 
    // else if (choice == 2) {
    //         algo.BinarySearch(Data.gethead(), choice2-1, field);
    // }
=======
    Data.ReadData(Data.getFakeData());
    // Data.displayArticlesfromEnd();
    // Data.tokenizeWords(array);
    // cout << Data.getsize();
    // Data.head(array, 9028);
    // Data.ApplySort(Data.getsize());
    int choice;
    int choice2;
    string field;
    cout << " Select Searching Algorithm" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "3. Return to Arrays Menu" << endl;
    cout << "Please Enter your choice.... ";
    while(!(cin>>choice)|| !(RegInput2(choice))){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid.. Please Enter your choice again.... ";
    }
    cout << "Chose a field to search for"<<endl;
    cout << "1. Title "<<endl; 
    cout << "2. Text "<<endl;
    cout << "3. Subject "<<endl;
    cout << "4. Year "<<endl;
    cout << "5. Month "<<endl;
    cout << "6. Day "<<endl;
    cout << "Please Enter your choice.... ";
    while(!(cin>>choice2)|| !(RegInput3(choice))){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid.. Please Enter your choice again.... ";
    }
    cin.ignore();
    cout << "Enter the keyword or value to search for: ";
    getline(cin, field);

    algo.linearSearch(Data.gethead(), choice2-1, field);
>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6


    return 0;   
}
