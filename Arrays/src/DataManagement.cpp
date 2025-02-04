#include <iostream>
#include <fstream>
#include <iomanip>
#include "header/Arrays_Manipulation.hpp"
#include "header/Arrays.hpp"

#include "Algorithms.cpp"
using namespace std;


dataManagement::dataManagement(){
    capacity=1000;
    article=new NewsArticle[capacity];
    TrueData.open("dataSets/true.csv");
    FakeData.open("dataSets/fake.csv");
    if(!TrueData.is_open() || !FakeData.is_open()){
        cout << "Error in reading the file";
        size=0;
        capacity=1000;
    }
    size=0;
}

void dataManagement::ReadData(ifstream& file){
    bool QuotedFlag=false;
    string Line, CurrentField, Date;
    int i=0; //To add elements into the 2D array
    while(getline(file, Line)){

        if (size == capacity) {
            capacity *= 2;  
            NewsArticle* temp = new NewsArticle[capacity];
            int Iterations=(size<capacity) ? size : capacity;
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
                //if we encouter a comma after the quates then we will specify each field based on the index
                if(index==0){
                    article[i].title=CurrentField;
                }else if(index==1){
                    article[i].content=CurrentField;
                }else if (index==2){
                    article[i].category=CurrentField;
                }
                CurrentField=""; //we have to reset the current field
                index++;
            }else{
                //if none of the condition were True we reset the index
                CurrentField+=c;
            }
        } 
        Date= CurrentField;
        // Handle last field (year)
        ParseDate(Date, article[i].publicationYear, article[i].publicationMonth, article[i].publicationDay);
        i++;
        size++;
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

void dataManagement::ParseDate(string& Date, int& year, int& month, int& day) {
    string field = "";
    int parseStage = 0;
    
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
void dataManagement::displayStruct(int rows){
    for(int i=1; i<rows; i++){
        cout << " Row Number: " <<i <<endl;
        cout << "Title: " <<article[i].title<<endl; 
        cout << "Text: " <<article[i].content<<endl<<endl; 
        cout << "Subject: " <<article[i].category<<endl; 
        cout <<"Year: "<< article[i].publicationYear<<endl; 
        cout <<"Month: "<< article[i].publicationMonth<<endl; 
        cout <<"Day: "<< article[i].publicationDay<<endl; 
        cout << string(166,'=');
        cout <<endl;
    }
}

void dataManagement::ApplySort(int size){
    dataManagement data;
    int* newYear= new int[size];
    int* index=new int[size];
    for (int i=0; i<size; i++){
        newYear[i]=article[i].publicationYear;
        index[i]=i;
    }
    algo.MergeSort(newYear, 0, size-1, index);
   
    string** arr=SortToArray(size-1, index);
    head(arr, 20);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;

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

void dataManagement::tokenizeWords(string** array) {
    int capacity=1000;
    string* wordsList = new string[capacity];  
    int* wordsFreq = new int[capacity];     
    string filler_words[] = {"a", "the", "is", "it", "to", "and", "of", "on", 
                            "for", "in", "at", "this", "that", "was", "were", "with", "between", "infront",
                            "have", "had", "has", "been", "about", "into", "are"};    
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
    cout << "Word Frequency List:\n";
    for(int i=0; i <Unique; i++){
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




/*
We can add more functions here in this point
*/

int main() {
    dataManagement Data;
    ArraysAlgo algo;
    Data.ReadData(Data.getFakeData());
    string** array=Data.StoreToArray(Data.getsize());
    Data.tokenizeWords(array);
    // cout << Data.getsize();
    // Data.ApplySort(Data.getsize());
    // int choice;
    // int choice2;
    // string field;
    // cout << " Select Searching Algorithm" << endl;
    // cout << "1. Linear Search" << endl;
    // cout << "2. Binary Search" << endl;
    // cout << "3. Return to Arrays Menu" << endl;
    // cout << "Please Enter your choice.... ";
    // while(!(cin>>choice)|| !(RegInput2(choice))){
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
    // while(!(cin>>choice2)|| !(RegInput3(choice))){
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //     cout << "Invalid.. Please Enter your choice again.... ";
    // }
    // cin.ignore();
    // cout << "Enter the keyword or value to search for: ";
    // getline(cin, field);

    // algo.LinearSearch(array, choice2-1, field, Data.getsize());
    for (int i = 0; i < TRUEMAX; ++i) {
        delete[] array[i];
    }
    delete[] array;

    return 0;   
}
