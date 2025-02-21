#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "header/Arrays_Manipulation.hpp"
#include <sstream>
#include "header/Arrays.hpp"
#include "header/NewsArticle.hpp"
#include "header/HashMap.hpp"
#include "../../header/PerformanceProfiler.hpp"
#include "Algorithms.cpp"
#include <chrono>
#include <string>
#include <functional>


using namespace std;

dataManagement::dataManagement(){
    capacity=1000;
    size=0;
    article=new NewsArticle[capacity];
    TrueData.open("dataSets/true.csv");
    FakeData.open("dataSets/fake.csv");
    if(!TrueData.is_open() || !FakeData.is_open()){
        cout << "Error in reading the file";
        size=0;
        capacity=1000;
    }
}


void dataManagement::ReadData(ifstream& file){
    bool QuotedFlag=false;
    string Line, CurrentField, Date;
    int i=0; //To add elements into the 2D array
    int maxGarbage=1000;
    string garbageCollector[maxGarbage];
    int garbageIndex=0;
    
    getline(file, Line);  // Skip the first line

    while(getline(file, Line)){

        if (size == capacity) {
            capacity *= 2;  
            NewsArticle* temp = new NewsArticle[capacity];
            for (int j = 0; j < size; j++) {
                temp[j] = article[j];
            }

            delete[] article;  
            article = temp;  
        }
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
                        article[i].title=CurrentField;
                    }else if(index==1){
                        article[i].content=CurrentField;
                    }else if (index==2){
                        article[i].category=CurrentField;
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
            article[i].publicationYear = year;
            article[i].publicationMonth = month;
            article[i].publicationDay = day;
        }
        if (!article[i].title.empty() && !article[i].content.empty() && !article[i].category.empty()) {
            i++;
            size++;
        }
    }
        file.clear();
        cout << "Data Loading Complete!" << endl; 
}

bool dataManagement::isEnglishWordCharacter(char c) {
    return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='\'';
}  

int dataManagement::getsize(){
    return size;
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



string** dataManagement::SortToArray(int size, int* temp) {
    string** arr = new string*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new string[6];  // Allocate 6 columns for each row
    }
    
    for (int i = 0; i < size; i++) {
        int index=temp[i];
        arr[i][0] = article[index].title;
        arr[i][1] = article[index].content;
        arr[i][2] = article[index].category;
        arr[i][3] = to_string(article[index].publicationYear);
        arr[i][4] = to_string(article[index].publicationMonth);
        arr[i][5] = to_string(article[index].publicationDay);
    }
    return arr;
}

string** dataManagement::StoreToArray(int size) {
    string** arr = new string*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new string[6];  // Allocate 6 columns for each row
    }
    for (int i = 0; i < size; i++) {
        arr[i][0] = article[i].title;
        arr[i][1] = article[i].content;
        arr[i][2] = article[i].category;
        arr[i][3] = to_string(article[i].publicationYear);
        arr[i][4] = to_string(article[i].publicationMonth);
        arr[i][5] = to_string(article[i].publicationDay);
    }
    return arr;
}


void dataManagement::DeleteArray(string**& arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];  // Delete each row
    }
    delete[] arr;  // Delete the main array
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
    delete[] article;
    if (TrueData.is_open()) {
        TrueData.close();
    }
    if (FakeData.is_open()) {
        FakeData.close();
    }
}

ifstream& dataManagement::getTrueData(){
    return TrueData;
}
ifstream& dataManagement::getFakeData(){
    return FakeData;
}

void dataManagement::head(string ** arr, int rows){
    for(int i=1; i<rows; i++){
        cout << " Row Number: " <<i <<endl;
        cout << "Title: " <<arr[i][0]<<endl; 
        cout << "Text: " <<arr[i][1]<<endl<<endl; 
        cout << "Subject: " <<arr[i][2]<<endl; 
        cout <<"Year: "<< arr[i][3]<<endl; 
        cout <<"Month: "<< arr[i][4]<<endl; 
        cout <<"Day: "<< arr[i][5]<<endl; 
        cout << string(166,'=');
        cout <<endl;
    }
}
//a void to view the contents of the struct created
void dataManagement::DisplayArray(string** arr, int totalArticles) {
    int rows;
    cout << "How many articles would you like to display? (Enter -1 for all): ";
    cin >> rows;

    // Validate input
    if (cin.fail() || rows < -1) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid number." << endl;
        return; // Exit the function if input is invalid
    }

    cout << "Displaying articles..." << endl;
    // If user enters -1 or a number larger than available, display all articles.
    int count = (rows == -1 || rows > totalArticles) ? totalArticles : rows;

    for (int i = 0; i < count; i++) {
        cout << "\n--- Article " << i + 1 << " ---\n";
        cout << "Title: " << arr[i][0] << "\n";
        // Uncomment below if you want to display content as well:
        // cout << "Content: " << arr[i][1] << "\n";
        cout << "Category: " << arr[i][2] << "\n";
        
        // Format month and day with a leading zero if needed:
        string month = arr[i][4];
        string day   = arr[i][5];
        if (month.length() == 1) month = "0" + month;
        if (day.length() == 1)   day = "0" + day;
        
        cout << "Date: " << arr[i][3] << "-" << month << "-" << day << "\n";
    }
    
    if (count == 0) {
        cout << "No articles to display." << endl;
    }
}


void dataManagement::ApplySort(string**& array, int size, int field, int sortType) {
    if (field >= 3) {
        ApplySortH<int>(array, size, field, sortType); 
    } else {
        ApplySortH<string>(array, size, field, sortType);
    }
    
    cout << "Exit ApplySort " << endl;
}

template <typename SelectedType>
void dataManagement::ApplySortH(string**& array, int size, int field, int sortType) {
    if (size <= 0) return;

    SelectedType* SelectedField = new SelectedType[size];
    int* index = new int[size];    

    for (int i = 0; i < size; i++) {
        
        if constexpr (is_same<SelectedType, int>::value) {
            SelectedField[i] = stoi(array[i][field]);  
        } else {
            SelectedField[i] = array[i][field];  
        }
        index[i] = i;  
    }
    cout << sortType << " Inside Array " << SelectedField[10]<< endl;

    ArraysAlgo algo;


    // Choose sorting algorithm based on sortType
    switch (sortType) {
        case 1:
            algo.InsertionSort(SelectedField, size, index);
           
            break;
        case 2:
            algo.BubbleSort(SelectedField, 0, size - 1, index);
            break;
        case 3:
            algo.QuickSort(SelectedField, size, index, 0);
            break;
        case 4:
            algo.MergeSort(SelectedField, 0, size - 1, index);
            break;
        default:
            cout << "Invalid sorting option: " << sortType << endl;
            break;
    }
    
    cout << "Exit ApplySortH " << endl;
    

    for (int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;
    
    
    array = SortToArray(size, index);
    // DeleteArray(array, size);
    
    cout << "K: Finished Sorting to Array!!! " << endl;
    
    delete[] SelectedField;
    delete[] index;

    
}


bool RegInput(int value){
            return (value==3||value==2||value==1);
}

bool RegInput2(int value){
    return (value==5 ||value==4||value==3||value==2||value==1);
}

bool RegInput3(int value){
    return (value==6||value==5 ||value==4||value==3||value==2||value==1);
}

void dataManagement::tokenizeWordsHash(string** array) {
    ArraysAlgo algo;
    HashMap hashmap;
    string filler_words[] = {"a", "the", "is", "it", "to", "and", "of", "on", 
                            "for", "in", "at", "this", "that", "was", "were", "with", "between", "infront",
                            "have", "had", "has", "been", "about", "into", "are", "after", "before", "not", "where", "when","those", "thus"};    
    int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);
    for (int i = 0; i < size; i++) {
        if(array[i][2].compare("Government News")!=0) continue; //filter the data only the government once are taken
        string text = array[i][1];  // Extract text from article
        string word = ""; // Temporary string for building words
        // Loop through each character in the text
        for (char c : text) {
            // Convert to lowercase
            c = tolower(c);
            // Check for word boundaries
            if (isspace(c) || ispunct(c)) {
                if (!word.empty()) { // If a word has been formed
                    // Check if it's a filler array
                    bool isFiller = false;
                    for (int k = 0; k < filler_size; k++) {
                        if (word == filler_words[k]) {
                            isFiller = true;
                            break;
                        }
                    }
                    if (!isFiller) {
                        hashmap.insert(word);
                    }
                    word = ""; 
                }
            } else {
                word += c;
            }
        }
    }
    auto result=hashmap.getKeysAndFrequencies();
    string* keys=result.first;
    int* freq=result.second;
    int* temp=new int[hashmap.getCount()];
    algo.QuickSort(freq, hashmap.getCount(), temp, 1);
    cout << "Word Frequency List:\n";
    for(int i=0; i <10; i++){
        cout << freq[i] << " :: " << keys[i] << endl;
    }

    delete[] keys;
    delete[] freq;
}


void dataManagement::tokenizeWords(string** array) {
    ArraysAlgo algo;
    int capacity=1000;
    string* wordsList = new string[capacity];  
    int* wordsFreq = new int[capacity];     
    string filler_words[] = {"a", "the", "is", "it", "to", "and", "of", "on", 
                            "for", "in", "at", "this", "that", "was", "were", "with", "between", "infront",
                            "have", "had", "has", "been", "about", "into", "are", "after", "before", "not", "where", "when","those", "thus"};    
    int filler_size = sizeof(filler_words) / sizeof(filler_words[0]);
    int Unique = 0; 
    for (int i = 0; i < size; i++) {
        if(array[i][2].compare("Government News")!=0) continue; //filter the data only the government once are taken
        string text = array[i][1];  // Extract text from article
        string word = ""; // Temporary string for building words

        // Loop through each character in the text
        for (char c : text) {
            // Convert to lowercase
            c = tolower(c);
            // Check for word boundaries
            if (isspace(c) || ispunct(c)) {
                if (!word.empty()) { // If a word has been formed
                    // Check if it's a filler array
                    bool isFiller = false;
                    for (int k = 0; k < filler_size; k++) {
                        if (word == filler_words[k]) {
                            isFiller = true;
                            break;
                        }
                    }
                
                    if (!isFiller) {
                        bool found = false;
                        for (int v = 0; v < Unique; v++) {
                            if (wordsList[v] == word) {
                                wordsFreq[v] += 1;  
                                found = true;
                                break;
                            }
                        }
                        if (!found) { 
                            if(Unique==capacity){
                                int newcap= capacity*2;
                                resizeArray(wordsList, capacity, newcap);
                                resizeArray(wordsFreq, capacity, newcap);
                                capacity=newcap;
                            }
                            wordsList[Unique] =word;
                            wordsFreq[Unique] = 1;
                            Unique++;
                        }
                    }
                    word = ""; 
                }
            } else {
                word += c;
            }
        }
    }
    int * temp=new int[Unique];
    algo.QuickSort(wordsFreq, Unique, temp, 1);
    cout << "Word Frequency List:\n";
    for(int i=0; i <10; i++){
        cout << wordsList[i] << " :: " << wordsFreq[i] << endl;
    }

    delete[] wordsList;
    delete[] wordsFreq;
}


template <typename Any>
void dataManagement::resizeArray(Any*& arr, int old, int newS){
    Any* temp=new Any[newS];
    int Iterations=(old < newS) ? old : newS;
    for(int i=0; i <Iterations; i++){
        temp[i]=arr[i];
    }
    delete []arr;
    arr=temp;

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
// void ArraysAlgo::compareAndDisplayPerformance(string** articles, int size, int SearchSortChoice, string SearchVar, int dataChoice, int FunctionChoice)
// {
//     dataManagement data;
//     int compareOption;
//     ifstream profileIn("dataSets/profile_output.txt");
//     if (profileIn.is_open()) {
//         cout << "\nCurrent Performance Info:\n";
//         string line;
//         while (getline(profileIn, line)) {
//             cout << line << "\n";
//         }
//         profileIn.close();
//     } else {
//         cout << "\nNo performance info available.\n";
//     }
    
//     do {
//         //compare performance with another function
        
//         cout << "\nDo you want to compare performance with another algorithm ?\n";
//         cout << "1. Yes\n2. No\nEnter your choice: ";
//         // cin >> compareOption;
//         while(!(cin >> compareOption)|| (compareOption != 1 && compareOption != 2)){
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(),'\n');
//             cout << "Invalid Input... Please enter a number between 1 and 2: ";
//         }
    
//         switch(FunctionChoice) {
//             case 1: // FAQ Tokenization comparison
//                 if (compareOption == 1) {
//                     int funcOption;
//                     cout << "\nSelect a algorithm to compare performance:\n";
//                     cout << "1. Hashmap Tokenization\n";
//                     cout << "2. Linear Search Tokenization\n";
//                     cout << "Enter your choice: ";
//                     while(!(cin >> funcOption)|| (funcOption > 2 || funcOption < 1)){
//                         cin.clear();
//                         cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                         cout << "Invalid Input... Enter Your choice Again: ";
//                     }
    
//                     // Append new performance info to the same profile file
//                     streambuf* origBuf = cout.rdbuf();
//                     ofstream profileAppend("dataSets/profile_output.txt", ios::app);
//                     if (!profileAppend) {
//                         cerr << "Error opening profile file for appending.\n";
//                     } else {
//                         cout.rdbuf(profileAppend.rdbuf());
//                         switch (funcOption) {
//                             case 1:
//                                 profileAlgorithm("Hashmap Tokenization", "O(n)", "O(1)", [&]() {
//                                     data.tokenizeWordsHash(articles);
//                                 });
//                                 break;
//                             case 2:
//                                 profileAlgorithm("Linear Search Tokenization", "O(n)", "O(1)", [&]() {
//                                     data.tokenizeWords(articles);
//                                 });
//                                 break;
//                             default:
//                                 cout << "Invalid function choice.\n";
//                         }
//                         cout.rdbuf(origBuf);
//                         profileAppend.close();
//                     }
    
//                     // Display the updated performance info
//                     ifstream updatedProfile("dataSets/profile_output.txt");
//                     if (updatedProfile.is_open()) {
//                         cout << "\nUpdated Performance Info (Comparison):\n";
//                         string line;
//                         while (getline(updatedProfile, line)) {
//                             cout << line << "\n";
//                         }
//                         updatedProfile.close();
//                     }
//                 } else {
//                     // If no comparison, clear the profile file
//                     ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
//                     if (clearFile.is_open()) {
//                         clearFile.close();
//                         cout << "\nProfile performance file cleared.\n";
//                     }
//                 }
                
//                 break;
                
//             case 2: // Sorting comparison
//                 int funcOption;
//                 if (compareOption == 1) {
                    
//                     cout << "\nSelect a algorithm to compare performance:\n";
//                     cout << "1. Insertion Sort" << endl;
//                     cout << "2. Bubble Sort" << endl;
//                     cout << "3. Quick Sort" << endl;
//                     cout << "4. Merge Sort" << endl;
//                     cout << "Enter your choice: ";
//                     while(!(cin >> funcOption)|| (funcOption >4 || funcOption < 1)){
//                         cin.clear();
//                         cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                         cout << "Invalid Input... Enter Your choice Again: ";
//                     }
    
//                     // Append new performance info to the same profile file
//                     streambuf* origBuf = cout.rdbuf();
//                     ofstream profileAppend("dataSets/profile_output.txt", ios::app);
//                     if (!profileAppend) {
//                         cerr << "Error opening profile file for appending.\n";
//                     } else {
//                         cout.rdbuf(profileAppend.rdbuf());
//                         switch (funcOption) {                            
//                             case 1:
//                                 if(dataChoice == 1){
//                                     profileAlgorithm("Insertion Sort for True: ", "O(n^2)", "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });              
//                                }
//                                else{
//                                     profileAlgorithm("insertion Sort for Fake: ", "O(n^2)",  "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 }
                               
                                
//                                 break;
//                             case 2:
//                                 if(dataChoice == 1){
//                                     profileAlgorithm("Bubble Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 }else{
//                                     profileAlgorithm("Bubble Sort for True: ", "O(n^2)", "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 }
//                                 break;
//                             case 3:
//                                 if(dataChoice == 1) {
//                                     profileAlgorithm("Quick Sort for True: ", "O(n^2)", "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 } else {
//                                     profileAlgorithm("Quick Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 }
                            
//                                 break;
//                             case 4:
//                                 cout << "Compare Merge Sort: " << endl;
//                                 if (dataChoice == 1) {
//                                     profileAlgorithm("Bottom Up Merge Sort for True: ", "O(n log n)", "O(1)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 } 
//                                 else {
//                                     profileAlgorithm("Bottom Up Merge Sort for Fake: ", "O(n log n)", "O(1)", [&]() {
//                                         data.ApplySort(articles, size, 3, funcOption);
//                                     });
//                                 }
                            
//                                 break;
//                             default:
//                                 cout << "Invalid function choice.\n";
//                         }
//                         cout.rdbuf(origBuf);
//                         profileAppend.close();
//                     }
    
//                     // Display the updated performance info
//                     ifstream updatedProfile("dataSets/profile_output.txt");
//                     if (updatedProfile.is_open()) {
//                         cout << "\nUpdated Performance Info (Comparison):\n";
//                         string line;
//                         while (getline(updatedProfile, line)) {
//                             cout << line << "\n";
//                         }
//                         updatedProfile.close();
//                     }
//                 } else {
//                     // If no comparison, clear the profile file
//                     ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
//                     if (clearFile.is_open()) {
//                         clearFile.close();
//                         cout << "\nProfile performance file cleared.\n";
//                     }
//                 }
//                 break;
    
//             case 3: // Searching comparison
//                 if (compareOption == 1) {
//                     int funcOption;
//                     cout << "\nSelect a algorithm to compare performance:\n";
//                     cout << "1. Linear search\n";
//                     cout << "2. Recursive search\n";
//                     cout << "Enter your choice: ";
//                     cin >> funcOption;
//                     cin.ignore();
    
//                     // Append new performance info to the same profile file
//                     streambuf* origBuf = cout.rdbuf();
//                     ofstream profileAppend("dataSets/profile_output.txt", ios::app);
//                     if (!profileAppend) {
//                         cerr << "Error opening profile file for appending.\n";
//                     } else {
//                         cout.rdbuf(profileAppend.rdbuf());
//                         switch (funcOption) {                           
//                             case 1:
//                                 if (SearchSortChoice == 1) {
//                                     int year = StringToInt(SearchVar);
//                                     profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
//                                         LinearSearch(articles, SearchSortChoice -1, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 2) {
//                                     int month = StringToInt(SearchVar);
//                                     profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
//                                         LinearSearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 3) {
//                                         profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
//                                             LinearSearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 4) {
//                                     profileAlgorithm("Linear search", "O(n)", "O(1)", [&]() {
//                                         LinearSearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 break;
                            
//                             case 2:
//                                 if (SearchSortChoice == 1) {
//                                     int year = StringToInt(SearchVar);
//                                     profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
//                                         BinarySearch(articles, SearchSortChoice -1, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 2) {
//                                     int month = StringToInt(SearchVar);
//                                     profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
//                                         BinarySearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 3) {
//                                     profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
//                                         BinarySearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 else if (SearchSortChoice == 4) {
//                                     profileAlgorithm("Recursive search", "O(n)", "O(1)", [&]() {
//                                         BinarySearch(articles, SearchSortChoice, SearchVar, size);
//                                     });
//                                 }
//                                 break;
                                
//                             default:
//                                 cout << "Invalid function choice.\n";
//                         }
//                         cout.rdbuf(origBuf);
//                         profileAppend.close();
//                     }
    
//                     // Display the updated performance info
//                     ifstream updatedProfile("dataSets/profile_output.txt");
//                     if (updatedProfile.is_open()) {
//                         cout << "\nUpdated Performance Info (Comparison):\n";
//                         string line;
//                         while (getline(updatedProfile, line)) {
//                             cout << line << "\n";
//                         }
//                         updatedProfile.close();
//                     }
//                 } else {
//                     // If no comparison, clear the profile file
//                     ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
//                     if (clearFile.is_open()) {
//                         clearFile.close();
//                         cout << "\nProfile performance file cleared.\n";
//                     }
//                 }
//         }
//     } while (compareOption != 2);
// }


void ArraysAlgo::compareAndDisplayPerformance(string** arr, int n, int algoType, string searchValue, const int dataChoice, int FunctionChoice) {
    dataManagement data;
    
    // Display current performance info
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
    
    int compareOption;
    do {
        cout << "\nDo you want to compare performance with another algorithm?\n";
        cout << "1. Yes\n2. No\nEnter your choice: ";
        while (!(cin >> compareOption) || (compareOption != 1 && compareOption != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input... Please enter a number between 1 and 2: ";
        }
        
        switch(FunctionChoice) {
            case 1: // FAQ Tokenization comparison
            {
                if (compareOption == 1) {
                    int funcOption;
                    cout << "\nSelect an algorithm to compare performance:\n";
                    cout << "1. Hashmap Tokenization\n";
                    cout << "2. Linear Search Tokenization\n";
                    cout << "Enter your choice: ";
                    cin >> funcOption;
                    cin.ignore();
                    
                    // Append new performance info to the profile file
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    if (!profileAppend) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout.rdbuf(profileAppend.rdbuf());
                        switch (funcOption) {
                            case 1:
                                profileAlgorithm("Hashmap Tokenization", "O(n)", "O(1)", [&]() {
                                    // Assumes a tokenizeWordsHash(string** arr, int n) exists
                                    data.tokenizeWordsHash(arr);
                                });
                                break;
                            case 2:
                                profileAlgorithm("Linear Search Tokenization", "O(n)", "O(1)", [&]() {
                                    // Assumes a tokenizeWords(string** arr, int n) exists
                                    data.tokenizeWords(arr);
                                });
                                break;
                            default:
                                cout << "Invalid function choice.\n";
                        }
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
                    
                    // Display updated performance info
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
                    // Clear performance file if not comparing
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                break;
            }
            
            case 2: // Sorting comparison
            {
                int funcOption;
                if (compareOption == 1) {
                    cout << "\nSelect an algorithm to compare performance:\n";
                    cout << "1. Insertion Sort" << endl;
                    cout << "2. Bubble Sort" << endl;
                    cout << "3. Quick Sort" << endl;
                    cout << "4. Merge Sort" << endl;
                    cout << "Enter your choice: ";
                    
                    while(!(cin >> funcOption)|| (funcOption > 4 || funcOption < 1)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "Invalid Input... Enter Your choice Again: ";
                    }
    
                    if (dataChoice != 1 && dataChoice != 2) {
                        cerr << "Error: Invalid DataChoice Variable.\n";
                        return;
                    }


                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    streambuf* origBuf = cout.rdbuf();
                    if (!profileAppend.is_open()) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout << "1. User Choice for Sort: " << funcOption << endl;
                        
                        cout.rdbuf(profileAppend.rdbuf());
                        
                        string algoName; //, timeComplexity, spaceComplexity;
                        
                        // Here dataChoice: 1 means True dataset, 2 means False dataset.
                        switch (funcOption) {
                            case 1:
                            algoName = (dataChoice == 1 ? "Insertion Sort for True: " : "Insertion Sort for False: ");
                                // timeComplexity = "O(n^2)";
                                // spaceComplexity = "O(n)";
                                profileAlgorithm(algoName, "O(n^2)", "O(n)", [&]() {
                                    // Assumes ApplySort(string** arr, int n, int field, int sortAlgo)
                                    data.ApplySort(arr, n, 3, funcOption);
                                });
                                break;
                            case 2:
                                algoName = (dataChoice == 1 ? "Bubble Sort for True: " : "Bubble Sort for False: ");
                                // timeComplexity = "O(n^2)";
                                // spaceComplexity = "O(n)";
                                profileAlgorithm(algoName, "O(n^2)", "O(n)", [&]() {
                                    data.ApplySort(arr, n, 3, funcOption);
                                });
                                break;
                            case 3:
                                algoName = (dataChoice == 1 ? "Quick Sort for True: " : "Quick Sort for False: ");
                                
                                profileAlgorithm(algoName, "O(n^2)", "O(n)", [&]() {
                                    data.ApplySort(arr, n, 3, funcOption);
                                });
                                cout << "Stuck Inside QUick Sort Switch" << endl;
                                break;
                            case 4:
                                algoName = (dataChoice == 1 ? "Merge Sort for True: " : "Merge Sort for False: ");
                                // timeComplexity = "O(n log n)";
                                // spaceComplexity = "O(n)";
                                profileAlgorithm(algoName, "O(n log n)", "O(n)", [&]() {
                                    data.ApplySort(arr, n, 3, funcOption);
                                });
                                
                                cout << "Stuck In Merge!" << endl;
                                break;
                            default:
                            cout << "Invalid function choice.\n";
                        }
                        cout << "Inside the Else after the switch case"<<endl;
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
                    
                    if (profileAppend.is_open()) {
                        cerr << "The file still Open mother fuckers\n";
                    }
                    cout << "Exited the Switch Case" <<endl;

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
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                break;
            }
            case 3: // Searching comparison
            {
                if (compareOption == 1) {
                    int funcOption;
                    cout << "\nSelect an algorithm to compare performance:\n";
                    cout << "1. Linear Search\n";
                    cout << "2. Binary Search\n";
                    cout << "Enter your choice: ";
                    cin >> funcOption;
                    cin.ignore();
                    
                    // For searching, prompt again for the field number (since the original call did not pass it)
                    int fieldIndex;
                    cout << "Enter the field number to search for (e.g., 1 for Title, 2 for Subject, etc.): ";
                    while (!(cin >> fieldIndex)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number: ";
                    }
                    cin.ignore();
                    
                    streambuf* origBuf = cout.rdbuf();
                    ofstream profileAppend("dataSets/profile_output.txt", ios::app);
                    if (!profileAppend) {
                        cerr << "Error opening profile file for appending.\n";
                    } else {
                        cout.rdbuf(profileAppend.rdbuf());
                        switch (funcOption) {
                            case 1:
                                profileAlgorithm("Linear Search", "O(n)", "O(1)", [&]() {
                                    // Assumes LinearSearch(string** arr, int fieldIndex, string value, int n)
                                    LinearSearch(arr, fieldIndex - 1, searchValue, n);
                                });
                                break;
                            case 2:
                                profileAlgorithm("Binary Search", "O(log n)", "O(1)", [&]() {
                                    // Assumes BinarySearch(string** arr, int fieldIndex, string value, int n)
                                    BinarySearch(arr, fieldIndex - 1, searchValue, n);
                                });
                                break;
                            default:
                                cout << "Invalid function choice.\n";
                        }
                        cout.rdbuf(origBuf);
                        profileAppend.close();
                    }
                    
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
                    ofstream clearFile("dataSets/profile_output.txt", ios::trunc);
                    if (clearFile.is_open()) {
                        clearFile.close();
                        cout << "\nProfile performance file cleared.\n";
                    }
                }
                break;
            }
            default:
                cout << "Invalid Function Choice.\n";
        }
    } while (compareOption != 2);
}









// int main() {
//     dataManagement Data;
//     ArraysAlgo algo;
//     Data.ReadData(Data.getTrueData());
//     string** array=Data.StoreToArray(Data.getsize());
//     Data.StatisticalSum(array, "true");
    // Data.displayStruct(10000);
    // Data.tokenizeWords(array);
    // Data.tokenizeWordsHash(array);
    // int choice, choice2, sortType;
    // string field;
    // cout << " Select Searching Algorithm" << endl;
    // cout << "1. Linear Search" << endl;
    // cout << "2. Binary Search" << endl;
    // cout << "3. Return to Arrays Menu" << endl;
    // cout << "Please Enter your choice.... ";
    // while(!(cin>>choice)|| !(RegInput2(choice))){
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         cout << "Invalid.. Please Enter your choice again.... ";
    //     }
    //     cout << "Chose a field to search for"<<endl;
    //     cout << "1. Title "<<endl; 
    //     cout << "2. Text "<<endl;
    //     cout << "3. Subject "<<endl;
    //     cout << "4. Year "<<endl;
    //     cout << "5. Month "<<endl;
    //     cout << "6. Day "<<endl;
    //     cout << "Please Enter your choice.... ";
    //     while(!(cin>>choice2)|| !(RegInput3(choice))){
    //             cin.clear();
    //             cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //             cout << "Invalid.. Please Enter your choice again.... ";
    //     }
    //     cin.ignore();
    //     cout << "Enter the keyword or value to search for: ";
    //     getline(cin, field);
        
    //         // Sorting Algorithm Selection
    //     cout << "Select Sorting Algorithm: " << endl;
    //     cout << "1. Merge Sort" << endl;
    //     cout << "2. Bubble Sort" << endl;
    //     cout << "3. Insertion Sort" << endl;
    //     cout << "4. Quick Sort" << endl;
    //     cout << "Enter your choice: ";

    //     while (!(cin >> sortType) || (sortType < 1 || sortType > 4)) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         cout << "Invalid choice. Enter 1 (Merge Sort) or 2 (Bubble Sort): ";
    //     }
        
    //     Data.ApplySort(array, Data.getsize(), choice2 - 1, sortType);

    //     // Perform search
    //     if (choice == 1) {
    //         algo.LinearSearch(array, choice2 - 1, field, Data.getsize());
    //     } else if (choice == 2) {
    //         algo.BinarySearch(array, choice2 - 1, field, Data.getsize());
    //     }
//         for (int i = 0; i < Data.getsize(); ++i) {
//             delete[] array[i];
//         }
//         delete[] array;

//     return 0;   
// }
