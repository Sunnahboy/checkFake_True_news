#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "header/LinkedList.hpp"
using namespace std;


dataManagement::dataManagement(string listname){
    size=0;
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


void dataManagement::ReadData(ifstream& file) {
    //lambda function to read the data

    auto readCSVField = [](istringstream &iss) -> string {
        string field;
        char firstChar = iss.peek();
    
        if (firstChar == '"') {  
            iss.get(); // Consume the opening quote
            bool insideQuotes = true;
            char c;
    
            while (iss.get(c)) {
                if (c == '"' && iss.peek() == '"') {
                    iss.get(); // Consume escaped quote `""`
                    field += '"';
                } else if (c == '"') {
                    insideQuotes = false; // End of quoted field
                } else if (!insideQuotes && c == ',') {
                    break; // End of field
                } else {
                    field += c; // Store character normally
                }
            }
        } else {
            getline(iss, field, ','); // Read unquoted fields normally
        }
    
        return field;
    };
    string header;
    getline(file, header);//Skipping the header of the data
    string line;

    while (getline(file, line)) {
        // Trim leading and trailing whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == string::npos) continue; // Skip empty or whitespace-only lines
        size_t end = line.find_last_not_of(" \t\r\n");
        string trimmedLine = line.substr(start, end - start + 1);
        
        if (trimmedLine.empty()) continue; // Double check for empty lines
        
        istringstream iss(trimmedLine);

        // Read CSV fields efficiently
        string title    = readCSVField(iss);
        string content  = readCSVField(iss);
        string category = readCSVField(iss);
        string dateField;
        getline(iss, dateField); // Read remaining date field

        // Remove leading comma if present in the date field
        if (!dateField.empty() && dateField[0] == ',') {
            dateField.erase(0, 1);
        }

        if (title.empty() || content.empty() || category.empty() || dateField.empty() ) continue;
        // Store parsed data

        int year, month, day;
        ParseDate(dateField, year, month, day);
        addArticlefromFront(title, content, category, day, month, year);
    }
    cout << "Data Loading complete";
}
        

void dataManagement::ParseDate(string& Date, int& year, int& month, int& day) {
    // Remove any extraneous quotation marks from the Date string.
    string cleanDate;
    string monthToken, dayToken, yearToken;
    for (char c : Date) {
        if (c != '"') {
            cleanDate.push_back(c);
        }
    }
    
    // Check if the date uses dashes, e.g., "19-Feb-18"
    if (cleanDate.find('-') != std::string::npos) {
        // Expected format: "dd-MMM-yy"
            size_t firstDash = cleanDate.find('-');
        size_t secondDash = cleanDate.find('-', firstDash + 1);
        if (firstDash != std::string::npos && secondDash != string::npos) {
            dayToken = cleanDate.substr(0, firstDash);
            monthToken = cleanDate.substr(firstDash + 1, secondDash - firstDash - 1);
            yearToken = cleanDate.substr(secondDash + 1);

            // cout <<  dayToken  << monthToken <<  yearToken << endl;
            
            // Convert the tokens to the respective values.
            day = StringToInt(dayToken);
            month = monthToNumber(monthToken);
            year = StringToInt(yearToken);
            
            // If the year is in two-digit format, assume it's 2000+ (adjust as needed).
            if (year < 100) {
                year += 2000;
            }
            return;
        }
    }
    // Otherwise, assume the format is like "January 1 2016" (or "January 1, 2016")
    istringstream ss(cleanDate);
    ss >> monthToken >> dayToken >> yearToken;
    
    // Remove any trailing comma from the day token (e.g., "1,")
    if (!dayToken.empty() && dayToken.back() == ',') {
        dayToken.pop_back();
    }
    
    month = monthToNumber(monthToken);
    day = StringToInt(dayToken);
    year = StringToInt(yearToken);
}
    


bool dataManagement::isEnglishWordCharacter(char c) {
    return isalnum(c) || c == '"' || c == ',' || c==' ' || c=='\'';
}       

int dataManagement::getsize(){
    return size;
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
        cout << " Row Number: " << i <<endl;
        cout << "Title: " << temp -> title <<endl; 
        cout << "Text: " << temp -> content<<endl<<endl; 
        cout << "Subject: " << temp -> category<<endl; 
        cout <<"Year: "<< temp -> year<<endl; 
        cout <<"Month: "<< temp -> month<<endl; 
        cout <<"Day: "<< temp -> day<<endl; 
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




/*
We can add more functions here in this point
*/

int main() {
    dataManagement Data("News Articles");
    Data.ReadData(Data.getFakeData());
    Data.displayArticlesfromFront();
    // Data.tokenizeWords(array);
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


    return 0;   
}
