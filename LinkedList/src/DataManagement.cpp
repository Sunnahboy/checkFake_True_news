#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include "header/LinkedList.hpp"
#include "header/MasterList.hpp"
#include "header/LinkedList_Manipulation.hpp"
#include "header/llhashmap.hpp"
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



/*
We can add more functions here in this point
*/

int main() {
    dataManagement Data("News Articles");
    LinkedListAlgo algo;
    Data.ReadData(Data.getFakeData());
    // Data.displayArticlesfromEnd();
    Data.tokenizeWordsHash(Data.gethead());
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


    return 0;   
}
