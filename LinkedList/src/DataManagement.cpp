#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include "header/LinkedList.hpp"
#include "header/MasterList.hpp"
#include "header/LinkedList_Manipulation.hpp"
#include "../../header/PerformanceProfiler.hpp"
#include "header/llhashmap.hpp"
#include "Algorithms.cpp"
#include <functional>
using namespace std;


dataManagement::dataManagement(){
    size=0;
    head = nullptr;
    tail = nullptr;

    TrueData.open("dataSets/true.csv");
    FakeData.open("dataSets/fake.csv");
    if(!TrueData.is_open() || !FakeData.is_open()){
        cout << "Error in reading the file";
    }
}

article * dataManagement::CreateNewNode(string Title, string Content, string Category, int Day, int Month, int Year){
    article * newArticle=new article(Title, Content, Category, Day, Month, Year);
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
    getline(file, Line); //skip the first line

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

    }
        file.clear();
        cout << "Data Loading Complete!" << endl; 
}
        

bool dataManagement::ParseDate(string& Date, int& year, int& month, int& day) {
    string field = "";
    int parseStage = 0;

    if(Date.find('-')!=string::npos){
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
    if(year <=0 || year >2025){
        return false;
    }
    return true;
}
    


bool dataManagement::isEnglishWordCharacter(char c) {
    return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='\'';
}       

int dataManagement::getsize(){
    cout << "The size of the list is: " << size << endl;
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

void dataManagement::DisplayArticles(article* head) {
    int rows;
    cout << "How many articles would you like to display? (Enter -1 for all): ";

    // Validate input
    while (!(cin >> rows) || (rows < -1)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid number." << endl;
        return; // Exit the function if input is invalid
    }

    cout << "Displaying articles..." << endl; // Debugging line
    int count = 0;
    article* temp = head; // Assuming head is the pointer to the start of the linked list
    while (temp != nullptr && (rows == -1 || count < rows)) {
        cout << "\n--- Article " << count + 1 << " ---\n";
        cout << "Title: " << temp->title << "\n";
        cout << "Content: " << temp->content << "\n";
        cout << "Category: " << temp->category << "\n";
        cout << "Date: " 
             << temp->year << "-" 
             << (temp->month < 10 ? "0" : "") << temp->month << "-" 
             << (temp->day < 10 ? "0" : "") << temp->day << "\n";
        temp = temp->next;
        count++;
    }
    if (count == 0) {
        cout << "No articles to display." << endl; // Debugging line
    }
}


 

string IntToString(int num) {
    return to_string(num);
}

int StringToInt(string num) {
    return stoi(num);
}


// Helper function to redirect cout to a file while executing a given function
void runWithRedirectedOutput(const string& filePath, const function<void()>& func) {
    // Save original cout buffer
    streambuf* origBuf = cout.rdbuf();
    
    // Open file for writing (not appending)
    ofstream outFile(filePath);
    if (!outFile) {
        cerr << "Error opening file: " << filePath << "\n";
        return;
    }
    
    // Redirect cout to the file
    cout.rdbuf(outFile.rdbuf());
    
    // Run the provided function
    func();
    
    // Restore cout and close file
    cout.rdbuf(origBuf);
    outFile.close();
}

// display performance info and optionally compare with another function
void LinkedListAlgo::compareAndDisplayPerformance(article* head, int SearchSortChoice, string SearchVar, article*& result, int FunctionChoice) {
    dataManagement data;
    int compareOption;
    ifstream profileIn("dataSets/profile_output.txt");
    if (profileIn.is_open()) {
        cout << "\nCurrent Performance Info:\n";
        string line;
        while (getline(profileIn, line)) {
            cout << line << "\n";
        }
        profileIn.close();
    } else {
        cout << "\nNo performance info available.\n";
    }
    
    do {
        
        cout << "\nDo you want to compare performance with another algorithm ?\n";
        cout << "1. Yes\n2. No\nEnter your choice: ";
        // cin >> compareOption;
        while(!(cin >> compareOption)|| (compareOption != 1 && compareOption != 2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid Input... Please enter a number between 1 and 2: ";
        }
    
        switch(FunctionChoice) {
            case 1: // FAQ Tokenization comparison
                if (compareOption == 1) {
                    int funcOption;
                    cout << "\nSelect a algorithm to compare performance:\n";
                    cout << "1. Hashmap Tokenization\n";
                    cout << "2. Linear Search Tokenization\n";
                    cout << "Enter your choice: ";
                    cin >> funcOption;
                    cin.ignore();
    
                    // Append new performance info to the same profile file
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    if (!profileAppend) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout.rdbuf(profileAppend.rdbuf());
                        switch (funcOption) {
                            case 1:
                                profileAlgorithm("Hashmap Tokenization", "O(n)", "O(1)", [&]() {
                                    data.tokenizeWordsHash(head);
                                });
                                break;
                            case 2:
                                profileAlgorithm("Linear Search Tokenization", "O(n)", "O(1)", [&]() {
                                    data.tokenizeWords(head);
                                });
                                break;
                            default:
                                cout << "Invalid function choice.\n";
                        }
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
    
                    // Display the updated performance info
                    ifstream updatedProfile("dataSets/profile_output.txt");
                    if (updatedProfile.is_open()) {
                        cout << "\nUpdated Performance Info (Comparison):\n";
                        string line;
                        while (getline(updatedProfile, line)) {
                            cout << line << "\n";
                        }
                        updatedProfile.close();
                    }
                } else {
                    // If no comparison, clear the profile file
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                
                break;
                
            case 2: // Sorting comparison
                int funcOption, dataChoice;
                dataChoice = StringToInt(SearchVar);
                if (compareOption == 1) {
                    
                    cout << "\nSelect a algorithm to compare performance:\n";
                    cout << "1. Insertion Sort" << endl;
                    cout << "2. Bubble Sort" << endl;
                    cout << "3. Quick Sort" << endl;
                    cout << "4. Merge Sort" << endl;
                    cout << "Enter your choice: ";
                    cin >> funcOption;
                    cin.ignore();
                    
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    if (!profileAppend) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout.rdbuf(profileAppend.rdbuf());
                        switch (funcOption) {
                            
                            case 1:
                                if(dataChoice == 1){
                                    profileAlgorithm("Insertion Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });              
                               }
                               else{
                                    profileAlgorithm("insertion Sort for Fake: ", "O(n^2)",  "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });
                                }
                               
                                
                                break;
                            case 2:
                                if(dataChoice == 1){
                                    profileAlgorithm("Bubble Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });
                                }else{
                                    profileAlgorithm("Bubble Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });
    
                                }
                                break;
                            case 3:
                                if(dataChoice == 1) {
                                    profileAlgorithm("Quick Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });
                                } else {
                                    profileAlgorithm("Quick Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                        sortArticles(head, 2, SearchSortChoice);
                                    });
                                }
                            
                                break;
                            case 4:
                                if (dataChoice == 1) {
                                    profileAlgorithm("Bottom Up Merge Sort for True: ", "O(n log n)", "O(1)", [&]() {
                                        sortArticles(head, 4, SearchSortChoice);
                                    });
                                } 
                                else {
                                    profileAlgorithm("Bottom Up Merge Sort for Fake: ", "O(n log n)", "O(1)", [&]() {
                                        sortArticles(head, 4, SearchSortChoice);
                                    });
                                }
                            
                                break;
                            default:
                                cout << "Invalid function choice.\n";
                        }
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
    
                    // Display the updated performance info
                    ifstream updatedProfile("dataSets/profile_output.txt");
                    if (updatedProfile.is_open()) {
                        cout << "\nUpdated Performance Info (Comparison):\n";
                        string line;
                        while (getline(updatedProfile, line)) {
                            cout << line << "\n";
                        }
                        updatedProfile.close();
                    }
                } else {
                    // If no comparison, clear the profile file
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                break;
    
            case 3: // Searching comparison
                if (compareOption == 1) {
                    int funcOption;
                    cout << "\nSelect a algorithm to compare performance:\n";
                    cout << "1. Linear search\n";
                    cout << "2. Recursive search\n";
                    cout << "Enter your choice: ";
                    cin >> funcOption;
                    cin.ignore();
    
                    // Append new performance info to the same profile file
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    if (!profileAppend) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout.rdbuf(profileAppend.rdbuf());
                        switch (funcOption) {
                            
                            case 1:
                                if (SearchSortChoice == 1) {
                                    int year = StringToInt(SearchVar);
                                    profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
                                        result = linearSearch(head, year, compareByYear, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 2) {
                                    int month = StringToInt(SearchVar);
                                    profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
                                        result = linearSearch(head, month, compareByMonth, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 3) {
                                        profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
                                        result = linearSearch(head, SearchVar, compareByTitleKeyword, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 4) {
                                    profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
                                        result = linearSearch(head, SearchVar, compareByCategory, nullptr);
                                    });
                                }
                                break;
                            
                            case 2:
                                if (SearchSortChoice == 1) {
                                    int year = StringToInt(SearchVar);
                                    profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
                                        result = search(head, year, compareByYear, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 2) {
                                    int month = StringToInt(SearchVar);
                                    profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
                                        result = search(head, month, compareByMonth, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 3) {
                                        profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
                                            result = search(head, SearchVar, compareByTitleKeyword, nullptr);
                                    });
                                }
                                else if (SearchSortChoice == 4) {
                                    profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
                                        result = search(head, SearchVar, compareByCategory, nullptr);
                                    });
                                }
                                break;
                                
                            default:
                                cout << "Invalid function choice.\n";
                        }
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
    
                    // Display the updated performance info
                    ifstream updatedProfile("dataSets/profile_output.txt");
                    if (updatedProfile.is_open()) {
                        cout << "\nUpdated Performance Info (Comparison):\n";
                        string line;
                        while (getline(updatedProfile, line)) {
                            cout << line << "\n";
                        }
                        updatedProfile.close();
                    }
                } else {
                    // If no comparison, clear the profile file
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                break;
        }
    } while (compareOption != 2);
}


// Revised function integrating the changes
void LinkedListAlgo::userSearchAndSwitch(article* head, int SearchChoice) {
    int choice, year, month;
    string input, SearchVar;
    article* result = nullptr;

    cout << "Choose search option:\n";
    cout << "1. Search by Year\n";
    cout << "2. Search by Month\n";
    cout << "3. Search by Title (Matching Word)\n";
    cout << "4. Search by Category\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    if (SearchChoice == 1) {
        switch (choice) {
            case 1:
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); // Clear input buffer

                // Redirect output while profiling the linearSearch call
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                        result = linearSearch(head, year, compareByYear, nullptr);
                    });
                });
                break;
            case 2:
                cout << "Enter month: ";
                cin >> month;
               
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                        result = linearSearch(head, month, compareByMonth, nullptr);
                    });
                });
                break;
            case 3:
                cout << "Enter keyword in title: ";
                getline(cin, input);
                
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                        result = linearSearch(head, input, compareByTitleKeyword, nullptr);
                        
                    });
                });

                break;
            case 4:
                cout << "Enter category: ";
                getline(cin, input);
                
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                        result = linearSearch(head, input, compareByCategory, nullptr);

                    });
                });
                break;
            case 5:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                userSearchAndSwitch(head, SearchChoice);
                return;
        }
    } else {
        switch (choice) {
            case 1:
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); // Clear input buffer
                
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("recursive Search", "O(n)", "O(n)", [&]() {
                        result = search(head, year, compareByYear, nullptr);
                        
                    });
                });
                break;
            case 2:
                cout << "Enter month: ";
                cin >> month;
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("recursive Search", "O(n)", "O(n)", [&]() {
                        result = search(head, month, compareByMonth, nullptr);
                        
                    });
                });
                break;
            case 3:
                cout << "Enter keyword in title: ";
                getline(cin, input);
                
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("recursive Search", "O(n)", "O(n)", [&]() {
                        result = search(head, input, compareByTitleKeyword, nullptr);
                        
                    });
                });
                break;
            case 4:
                cout << "Enter category: ";
                getline(cin, input);
              
                runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                    profileAlgorithm("recursive Search", "O(n)", "O(n)", [&]() {
                        result = search(head, input, compareByCategory, nullptr);     
                    });
                });
                break;
            case 5:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                userSearchAndSwitch(head, SearchChoice);
                return;
        }
    }

    // Display search results
    if (result) {
        int matchCount = 0;
        article* current = result;
        cout << "\nFound matching articles:\n";
        cout << "------------------------\n";
        while (current) {
            matchCount++;
            cout << "\nMatch #" << matchCount << ":\n";
            cout << "Title: " << current->title << "\n";
            cout << "Category: " << current->category << "\n";
            cout << "Date: " << current->day << "/" << current->month << "/" << current->year << "\n";
            current = current->next;
        }
        cout << "\nTotal matches found: " << matchCount << "\n";
    } else { 
        cout << "No matching articles found.\n";
    }
    
   
    SearchVar = (choice == 1) ? IntToString(year) : (choice == 2) ? IntToString(month) : input;


    // Compare and display performance info (or clear the file)
    compareAndDisplayPerformance(head, choice, SearchVar, result, 3);
}

void dataManagement::tokenizeWords(article * Node) {
    MasterList wordList; // Using MasterList instead of hashmap or arrays
    
    cout << "Inside Tokenise Words" << endl;

    // List of filler words to ignore
    const string filler_words[] = {
        "a", "the", "is", "it", "to", "and", "of", "on", "for", "in", "at", "this",
        "that", "was", "were", "with", "between", "infront", "have", "had", "has", 
        "been", "about", "into", "are", "after", "before", "not", "where", "when", "thus",
        "s", "he", "as", "by", "from", "we", "be", "they", "said", "who",
        "an", "his", "i", "you", "t", "their", "will", "us", "but",
        "more", "or", "our", "would", "all", "what", "she",
        "one", "her", "out", "if", "which",
        "just", "there", "can", "no", "so", "up",
        "do", "does", "did", "done", "could", "should", "would", "shall", "may", "might",
        "because", "although", "while", "since", "though", "unless", "whether",
        "me", "him", "them", "my", "mine", "your", "yours", "ours", "theirs",
        "any", "some", "every", "each", "either", "neither",
        "over", "under", "inside", "outside", "above", "below",
        "towards", "onto", "upon", "against", "beside", "among", "through",
        "again", "already", "yet", "ever", "never", "always", "sometimes",
        "soon", "later", "now", "then", "here", "there", "everywhere",
        "am", "are", "is", "was", "were", "being", "been",
        "also", "even", "however", "furthermore", "nevertheless",
        "somewhere", "anywhere", "nowhere", "wherever"
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
    
    cout << "Start of Display" << endl;
    wordList.displayTopWords();
    cout << "End of Display" << endl;
}


void dataManagement::tokenizeWordsHash(article* Node) {
    HashMap wordMap; // Using HashMap instead of arrays

    // List of filler words to ignore
    const string filler_words[] = {
        "a", "the", "is", "it", "to", "and", "of", "on", "for", "in", "at", "this",
        "that", "was", "were", "with", "between", "infront", "have", "had", "has", 
        "been", "about", "into", "are", "after", "before", "not", "where", "when", "thus",
        "s", "he", "as", "by", "from", "we", "be", "they", "said", "who",
        "an", "his", "i", "you", "t", "their", "will", "us", "but",
        "more", "or", "our", "would", "all", "what", "she",
        "one", "her", "out", "if", "which", "just", "there", "can", "no", "so", "up",
        "do", "does", "did", "done", "could", "should", "would", "shall", "may", "might",
        "because", "although", "while", "since", "though", "unless", "whether",
        "me", "him", "them", "my", "mine", "your", "yours", "ours", "theirs",
        "any", "some", "every", "each", "either", "neither",
        "over", "under", "inside", "outside", "above", "below",
        "towards", "onto", "upon", "against", "beside", "among", "through",
        "again", "already", "yet", "ever", "never", "always", "sometimes",
        "soon", "later", "now", "then", "here", "there", "everywhere",
        "am", "are", "is", "was", "were", "being", "been",
        "also", "even", "however", "furthermore", "nevertheless",
        "somewhere", "anywhere", "nowhere", "wherever"
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
    
    FreqTextWords* wordlist = wordMap.getKeysAndFrequencies();
    if (!wordlist) {
        cout << "No words found." << endl;
        return;
    }
    
    wordMap.sortAndPrintTop10(wordlist);


}


article* LinkedListAlgo::sortArticles(article* head, int choice, int sortType) {

    switch (choice) {
        case 1:
            if (sortType == 1) {
                head = insertionSort(head, compareSubject);
            }
            else {
                head = insertionSort(head, compareDates);
            }
            break;
        case 2:
            if (sortType == 1) {
                head = bubbleSort(head, compareSubject);
            }
            else {
                head = bubbleSort(head, compareDates);
            }
            break;
        case 3:
            if (sortType == 1) {
                head = quickSort(head, compareSubject);
            }
            else {
                head = quickSort(head, compareDates);
            }
            break;
        case 4:
            if (sortType == 1) {
                head = bottomUpMergeSort(head, compareSubject);
            }
            else {
                head = bottomUpMergeSort(head, compareDates);
            }
            break;
        default:
            cout << "Invalid sorting choice." << endl;
            break;
        
        }
    return head;
}