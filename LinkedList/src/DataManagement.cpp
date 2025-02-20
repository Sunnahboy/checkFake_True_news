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
#include "header/NewsArticle.hpp"
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
    // newArticle -> title =Title;
    // newArticle -> content =Content;
    // newArticle -> category=Category;
    // newArticle -> day= Day;
    // newArticle -> month= Month;
    // newArticle -> year= Year;
    // newArticle -> next =nullptr;

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
        // if (head != nullptr) {
        //     size++;
        //     cout << size << " articles loaded." << endl;
        // }
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

void dataManagement::DisplayArticles(article* head, int totalArticles) {
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
        // cout << "Content: " << temp->content << "\n";
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



/*void LinkedListAlgo::userSearchAndSwitch(article* head, int SearchChoice) {
    int choice, year, month;
    string input;
    article* result = nullptr;

    cout << "Choose search option:\n";
    cout << "1. Search by Year\n";
    cout << "2. Search by Month\n";
    cout << "3. Search by Title (Matching Word)\n";
    cout << "4. Search by Category\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
    while(!(cin >> choice)|| !ValidInput(choice, 2, 1)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid Input... Enter Your choice Again: ";
    }

    if (SearchChoice == 1) {
        switch (choice) {
            case 1:
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); // Clear input buffer
                // result = linearSearch(head, year, compareByYear, nullptr);  // Don't need &pos anymore
                //profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                   // result = linearSearch(head, year, compareByYear, nullptr);
                //}); 
                 {   // redirect profiling output to a file so terminal doesn't flood
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileFile("dataSets/profile_output.txt");
                    if (!profileFile) {
                        cerr << "Error openin profile file.\n";
                    } else {
                        cout.rdbuf(profileFile.rdbuf());
                        profileAlgorithm("linear Search", "O(n)", "O(n)", [&]() {
                            result = linearSearch(head, year, compareByYear, nullptr);
                        });
                        // restore cout so next output goes to terminal
                        cout.rdbuf(origBuf);
                        profileFile.close();
                    }
                }                  
                
                break;
            case 2:
                cout << "Enter month: ";
                cin >> month;
                result = linearSearch(head, month, compareByMonth, nullptr);
                break;
            case 3:
                cout << "Enter keyword in title: ";
                getline(cin, input);
                result = linearSearch(head, input, compareByTitleKeyword, nullptr);
                break;
            case 4:
                cout << "Enter category: ";
                getline(cin, input);
                result = linearSearch(head, input, compareByCategory, nullptr);
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
    else {
        switch (choice) {
            case 1:
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); // Clear input buffer
                result = search(head, year, compareByYear, nullptr);  // Don't need &pos anymore
                break;
            case 2:
                cout << "Enter month: ";
                cin >> month;
                result = search(head, month, compareByMonth, nullptr);
                break;
            case 3:
                cout << "Enter keyword in title: ";
                getline(cin, input);
                result = search(head, input, compareByTitleKeyword, nullptr);
                break;
            case 4:
                cout << "Enter category: ";
                getline(cin, input);
                result = search(head, input, compareByCategory, nullptr);
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

    if (result) {
        // Count and display all matches
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
 }*/

 




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
void LinkedListAlgo::compareAndDisplayPerformance(article* head, int year, article*& result, int FunctionChoice) {
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

    //compare performance with another function
    int compareOption;
    cout << "\nDo you want to compare performance with another algorithm ?\n";
    cout << "1. Yes\n2. No\nEnter your choice: ";
    cin >> compareOption;
    cin.ignore();

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
                                tokenizeWordsHash(head);
                            });
                            break;
                        case 2:
                            profileAlgorithm("Linear Search Tokenization", "O(n)", "O(1)", [&]() {
                                tokenizeWords(head);
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
            
        case 2: // Sorting comparison
            if (compareOption == 1) {
                int funcOption, dataChoice;
                cout << "\nSelect a algorithm to compare performance:\n";
                cout << "1. Insertion Sort" << endl;
                cout << "2. Bubble Sort" << endl;
                cout << "3. Quick Sort" << endl;
                cout << "4. Merge Sort" << endl;
                cout << "Enter your choice: ";
                cin >> funcOption;
                cin.ignore();
                
                cout << "Select data set to sort:\n";
                cout << "1. True\n";
                cout << "2. Fake\n";
                cout << "Enter your choice: ";
                cin >> dataChoice;
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
                            if(dataChoice == 1){
                                profileAlgorithm("Insertion Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    algo.sortArticles(True.gethead(), 2, sortType);
                                });
                                
                           }else{
                                profileAlgorithm("insertion Sort for Fake: ", "O(n^2)",  "O(n)", [&]() {
                                    algo.sortArticles(Fake.gethead(), 2, sortType);
                                });
                            }
                           
                            
                            break;
                        case 2:
                            if(dataChoice == 1){
                                profileAlgorithm("Bubble Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                algo.sortArticles(True.gethead(), 2, sortType);
                            });
                            }else{
                                profileAlgorithm("Bubble Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    algo.sortArticles(Fake.gethead(), 2, sortType);
                                });

                            }
                            break;
                        case 3:
                            if(dataChoice == 1) {
                                profileAlgorithm("Quick Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    algo.sortArticles(True.gethead(), 2, sortType);
                                });
                            } else {
                                profileAlgorithm("Quick Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                    algo.sortArticles(Fake.gethead(), 2, sortType);
                                });
                            }
                        
                            break;
                        case 4:
                            if (dataChoice == 1) {
                                profileAlgorithm("Bottom Up Merge Sort for True: ", "O(n log n)", "O(1)", [&]() {
                                    algo.sortArticles(True.gethead(), 4, sortType);
                                });
                            } 
                            else {
                                profileAlgorithm("Bottom Up Merge Sort for Fake: ", "O(n log n)", "O(1)", [&]() {
                                    algo.sortArticles(Fake.gethead(), 4, sortType);
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
                            profileAlgorithm("search", "O(n)", "O(1)", [&]() {
                                result = linearSearch(head, year, compareByYear, nullptr);
                            });
                            break;
                        case 2:
                            profileAlgorithm("recursive search", "O(n)", "O(log n)", [&]() {
                                result = search(head, year, compareByYear, nullptr);
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
}


// Revised function integrating the changes
void LinkedListAlgo::userSearchAndSwitch(article* head, int SearchChoice) {
    int choice, year, month;
    string input;
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

    // Compare and display performance info (or clear the file)
    compareAndDisplayPerformance(head, year, result);
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


article* LinkedListAlgo::sortArticles(article* head, int choice, int sortType) {
            
    // auto comparator = [&](article* a, article* b) -> bool {
    //     if (sortType == 1) { 
    //         return compareSubject(a, b); // Sort by Subject
    //     } else if (sortType == 2) { 
    //         return compareDates(a, b); // Sort by Date
    //     }
    //     return false;
    // };

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


// template <typename Any>
// void dataManagement::resizeArray2(Any*& arr, int old, int newS){
//     Any* temp=new Any[newS];
//     int Iterations=(old < newS) ? old : newS;
//     for(int i=0; i <Iterations; i++){
//         temp[i]=arr[i];
//     }
//     delete []arr;
//     arr=temp;
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

// void dataManagement::runNewsProcessor(article* head, string datasetChoice) {
//     NewsArticleProcessor processor;
    
    
//     processor.processArticles(head); // Pass the linked list to process
//     int option;
//     cout << "\nSelect analysis type:\n";
//     cout << "1. View articles per year\n";
//     cout << "2. View articles per month\n";
//     cout << "3. View articles per day\n";
//     cout << "4. Exit\n";
//     cout << "Enter your choice: ";
//     while (!(cin >> option)) {
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         cout << "Invalid choice. Please enter a number between 1 and 4.\n";
//     }
//     int year, month, day;

//     switch (option) {
//         case 1:
//             cout << "Enter year: ";
//             cin >> year;
//             while (!processor.isValidYear(year, datasetChoice)) {
//                 cout << "Invalid year. Try again.\nEnter year: ";
//                 cin >> year;
//             }
//             processor.displayTable("Articles in " + to_string(year), processor.getArticleCount(year));
//             break;
        
//         case 2:
//             cout << "Enter year: ";
//             cin >> year;
//             while (!processor.isValidYear(year, datasetChoice)) {
//                 cout << "Invalid year. Try again.\nEnter year: ";
//                 cin >> year;
//             }
            
//             cout << "Enter month (1-12): ";
//             cin >> month;
//             while (!processor.isValidMonth(month)) {
//                 cout << "Invalid month. Try again.\nEnter month (1-12): ";
//                 cin >> month;
//             }
            
//             processor.displayTable("Articles in " + to_string(year) + " - Month " + to_string(month), processor.getArticleCount(year, month));
//             break;
        
//         case 3:
//             cout << "Enter year: ";
//             cin >> year;
//             while (!processor.isValidYear(year, datasetChoice)) {
//                 cout << "Invalid year. Try again.\nEnter year: ";
//                 cin >> year;
//             }
            
//             cout << "Enter month (1-12): ";
//             cin >> month;
//             while (!processor.isValidMonth(month)) {
//                 cout << "Invalid month. Try again.\nEnter month (1-12): ";
//                 cin >> month;
//             }
            
//             cout << "Enter day: ";
//             cin >> day;
//             while (!processor.isValidDay(year, month, day)) {
//                 cout << "Invalid day. Try again.\nEnter day: ";
//                 cin >> day;
//             }
            
//             processor.displayTable("Articles in " + to_string(year) + " - Month " + to_string(month) + " - Day " + to_string(day), processor.getArticleCount(year, month, day));
//             break;
        
//         default:
//             cout << "Invalid option selected.";
//             break;
//     }
    
// }



/*
We can add more functions here in this point
*/

// int main() {
//     dataManagement Data("News Articles");
//     LinkedListAlgo algo;
//     Data.ReadData(Data.getTrueData());
//     // Use linked list head directly
//     Data.runNewsProcessor(Data.gethead(), "true");
//     // Data.displayArticlesfromEnd();
//    // Data.tokenizeWordsHash(Data.gethead());
//     // cout << Data.getsize();
//     // Data.head(array, 9028);
//     // Data.ApplySort(Data.getsize());
//     // int choice;
//     // int choice2;
//     // string field;
//     // cout << " Select Searching Algorithm" << endl;
//     // cout << "1. Linear Search" << endl;
//     // cout << "2. Binary Search" << endl;
//     // cout << "3. Return to Arrays Menu" << endl;
//     // cout << "Please Enter your choice.... ";
//     // while(!(cin>>choice)|| !(RegInput(choice))){
//     //     cin.clear();
//     //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     //     cout << "Invalid.. Please Enter your choice again.... ";
//     // }
//     // cout << "Chose a field to search for"<<endl;
//     // cout << "1. Title "<<endl; 
//     // cout << "2. Text "<<endl;
//     // cout << "3. Subject "<<endl;
//     // cout << "4. Year "<<endl;
//     // cout << "5. Month "<<endl;
//     // cout << "6. Day "<<endl;
//     // cout << "Please Enter your choice.... ";
//     // while(!(cin>>choice2)|| !(RegInput3(choice2))){
//     //     cin.clear();
//     //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     //     cout << "Invalid.. Please Enter your choice again.... ";
//     // }
//     // cin.ignore();
//     // cout << "Enter the keyword or value to search for: ";
//     // getline(cin, field);
    
//     // if (choice == 1) {
//     //         algo.linearSearch(Data.gethead(), choice2-1, field);
//     // } 
//     // else if (choice == 2) {
//     //         algo.BinarySearch(Data.gethead(), choice2-1, field);
//     // }


//     return 0;   
// }
