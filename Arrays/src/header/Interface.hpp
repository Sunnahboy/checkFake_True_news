// #include <iostream>
// #include <limits>
// #include "Arrays_Manipulation.hpp"
// #include "../DataManagement.cpp"
// #include "../Statistics.cpp"
// #include "Arrays.hpp"

// #ifndef Interface_HPP
// #define Interface_HPP
// using namespace std;
// class Interface
// {   
//     private:
//         dataManagement True;
//         dataManagement Fake;

//         int trueSize;
//         int fakeSize;

//         string** trueArticles;
//         string** fakeArticles;

//         ArraysAlgo algo;

//     public:
//         Interface() {
//             // Load data from CSV files
//             True.ReadData(True.getTrueData());
//             Fake.ReadData(Fake.getFakeData());

//             // Get sizes after data is loaded
//             trueSize = True.getsize();
//             fakeSize = Fake.getsize();

            
//             trueArticles = True.StoreToArray(trueSize);
//             fakeArticles = Fake.StoreToArray(fakeSize);
//         }
        

//         void columns(){
//             for(int i=0; i<=80; i++){
//                 cout << "="<<left;
//             }
//             cout <<endl;
//         }
//         void prinTable(int o){
//             Interface AppInterface;
//             string msg=AppInterface.msg(o);
//             columns();
//             cout <<string(26, ' ') << msg;
//             cout <<endl;
//             columns();
//         }

//         string msg(int o){
//             switch(o){
//                 case 1: return "Data Filtering";
//                 case 2: return "Sort Data";
//                 case 3: return "Search Data";
//                 case 4: return "ARRAYS MANAGEMENT";
//                 case 5: return "FAQ";
//                 default:    return "none";                   
//             }
//         }

//         void FAQ(){
//             int FAQchoice;
//             prinTable(5);
//             cout << "1. What percentage of political news articles from the year of 2016 are fake? " << endl;
//             cout << "2. Percentage of fake political news articles for each month in 2016." << endl;
//             cout << "3. Which words are most frequently used in fake news articles related to government topics?" << endl;
//             cout << "4. What is the total number of articles in both true and fake news datasets?" << endl;
//             cout << "5. Return to Arrays Menu" << endl;
//             columns(); 
//             cout << "Enter choice: ";  
//             while(!(cin >> FAQchoice) || !(RegInput2(FAQchoice))) {
//                 cin.clear();
//                 cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                 cout << "Invalid Input... Enter your choice again: ";
//             }

//             switch(FAQchoice) {
//                 case 1:
//                     cout << "Sorting True Articles" << endl;
//                     True.ApplySort(trueArticles, trueSize, 3, 4);
//                     cout << "Sorting Fake Articles" << endl;
//                     Fake.ApplySort(fakeArticles, fakeSize, 3, 4);
//                     algo.calculateFakeNewsPercentage(trueArticles, trueSize, fakeArticles, fakeSize);
//                     break;

//                 case 2:
//                     cout << "Sorting True Articles" << endl;
//                     True.ApplySort(trueArticles, trueSize, 3, 4);
//                     cout << "Sorting Fake Articles" << endl;
//                     Fake.ApplySort(fakeArticles, fakeSize, 3, 4);
//                     algo.displayFakeNewsPercentageByMonth(trueArticles, trueSize, fakeArticles, fakeSize);
//                     break;

//                 case 3:
//                     cout << "Word Frequency: " << endl;
//                     cout << "1. Hashmap" << endl;
//                     cout << "2. Linear Search." << endl;
//                     cout << "3. Return to FAQ Menu" << endl;
//                     columns();
//                     cout << "Enter choice: ";
//                     int choice;
//                     while(!(cin >> choice) || !(RegInput(choice))) {
//                         cin.clear();
//                         cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                         cout << "Invalid Input... Enter your choice again: ";
//                     }
//                     switch(choice) {
//                         case 1:
//                             Fake.tokenizeWordsHash(fakeArticles);
//                             break;
//                         case 2:
//                             Fake.tokenizeWords(fakeArticles);
//                             break;
//                         case 3:
//                             cout << "Returning to FAQ Menu..." << endl;
//                             return;
//                         default: cout << "Invalid" << endl;
//                     }
//                     break;

//                 case 4:
//                     cout << "Nothing here yet." << endl;
//                     break;

//                 case 5:
//                     cout << "Returning to Arrays Menu..." << endl;
//                     return;
//                 default: cout << "Invalid" << endl;
//             }

//         }



//         void SortData(){
//             prinTable(2);
//             int choice;
//             cout << " Select Sorting Algorithm" << endl;
//             cout << "1. Insertion Sort" << endl;
//             cout << "2. Bubble Sort" << endl;
//             cout << "3. Quick Sort" << endl;
//             cout << "4. Merge Sort" << endl;
//             cout << "5. Return to Arrays Menu" << endl;
//             cout << "Please Enter your choice: ";
//             columns(); 
//             while(!(cin >> choice)|| choice > 5 || choice < 1){
//                     cin.clear();
//                     cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                     cout << "Invalid Input... Enter Your choice Again: ";
//                 }

//                 int field;
//                 cout << "Chose to sort by true or false."<<endl;
//                 cout << "1. True "<<endl;
//                 cout << "2. False "<<endl;
//                 cout << "Please enter your choice: ";
//                 columns();
//                 while(!(cin >> field)|| !field == 1 || !field == 2){
//                     cin.clear();
//                     cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                     cout << "Invalid Input... Enter Your choice Again: ";
//                 }

//                 switch(choice){
//                     case 1: 
//                         if (field == 1) {
//                             True.DisplayArray(trueArticles, trueSize);
//                             True.ApplySort(trueArticles, trueSize, 4, 3);
//                             cout << "After sort" << endl;
//                             True.DisplayArray(trueArticles, trueSize);
//                         } else {
//                             // Fake.displayStruct(5);
//                             Fake.ApplySort(fakeArticles, fakeSize, 4, 3);
//                             cout << "After sort" << endl;
//                             // Fake.displayStruct(5);
//                         }
//                         break;
//                     case 2: 
//                         if (field == 1) {
//                             True.ApplySort(trueArticles, trueSize, 3, 2);
//                         } else {
//                             Fake.ApplySort(fakeArticles, fakeSize, 3, 2);
//                         }
//                         break;
//                     case 3: 
//                         if (field == 1) {
//                             True.ApplySort(trueArticles, trueSize, 3, 4);
//                         } else {
//                             Fake.ApplySort(fakeArticles, fakeSize, 3, 4);
//                         }
//                         break;
//                     case 4: 
//                         if (field == 1) {
//                             // True.displayStruct(5);
//                             True.ApplySort(trueArticles, trueSize, 3, 1);
//                             // True.displayStruct(5);
//                         } else {
//                             Fake.ApplySort(fakeArticles, fakeSize, 3, 1);
//                         }
//                         break;
//                     case 5: 
//                         cout << "Returning to Arrays Menu..." << endl;
//                         return;
//                     default: cout << "Invalid";
//                 }
                            
//         }

//         void SearchData(){
//             int choice;
//             int choice2;
//             string field;
//             prinTable(3);
//             cout << " Select Searching Algorithm" << endl;
//             cout << "1. Linear Search" << endl;
//             cout << "2. Binary Search" << endl;
//             cout << "3. Return to Arrays Menu" << endl;
//             columns();    
//             cout << "Please Enter your choice.... ";
//             while(!(cin>>choice)|| !(RegInput(choice))){
//                 cin.clear();
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "Invalid.. Please Enter your choice again.... ";
//             }

//             int setChoice;
//                 cout << "Chose to sort by true or false."<<endl;
//                 cout << "1. True "<<endl;
//                 cout << "2. False "<<endl;
//                 cout << "Please enter your choice: ";
//                 columns();
//                 while(!(cin >> setChoice)|| !setChoice == 1 || !setChoice == 2){
//                     cin.clear();
//                     cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                     cout << "Invalid Input... Enter Your choice Again: ";
//                 }

//             switch(choice){
//                 case 1:
//                     cout << "Chose a field to search for"<<endl;
//                     cout << "1. Title "<<endl;
//                     cout << "2. Text "<<endl;
//                     cout << "3. Subject "<<endl;
//                     cout << "4. Year "<<endl;
//                     cout << "5. Month "<<endl;
//                     cout << "Please Enter your choice.... ";
//                     while(!(cin>>choice2)|| !(RegInput2(choice))){
//                         cin.clear();
//                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                         cout << "Invalid.. Please Enter your choice again.... ";
//                     }
//                     cin.ignore();
//                     cout << "Enter the keyword or value to search for: ";
//                     getline(cin, field);
                    
//                     if (setChoice == 1) {
//                         algo.LinearSearch(trueArticles, choice2-1, field, trueSize);
//                         for (int i = 0; i < trueSize; ++i) {
//                             delete[] trueArticles[i];
//                         }
//                         delete[] trueArticles;
//                     } else {
//                         algo.LinearSearch(fakeArticles, choice2-1, field, fakeSize);
//                         for (int i = 0; i < fakeSize; ++i) {
//                             delete[] fakeArticles[i];
//                         }
//                         delete[] fakeArticles;
//                     }
//                     break;

//                 case 2:
//                     cout << "Chose a field to search for"<<endl;
//                     cout << "1. Title "<<endl;
//                     cout << "2. Text "<<endl;
//                     cout << "3. Subject "<<endl;
//                     cout << "4. Year "<<endl;
//                     cout << "5. Month "<<endl;
//                     cout << "Please Enter your choice.... ";
//                     while(!(cin>>choice2)|| !(RegInput2(choice))){
//                         cin.clear();
//                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                         cout << "Invalid.. Please Enter your choice again.... ";
//                     }
//                     cin.ignore();
//                     cout << "Enter the keyword or value to search for: ";
//                     getline(cin, field);
                    
//                     if (setChoice == 1) {
//                         algo.BinarySearch(trueArticles, choice2-1, field, trueSize);
//                         for (int i = 0; i < trueSize; ++i) {
//                             delete[] trueArticles[i];
//                         }
//                         delete[] trueArticles;
//                     } else {
//                         algo.BinarySearch(fakeArticles, choice2-1, field, fakeSize);
//                         for (int i = 0; i < fakeSize; ++i) {
//                             delete[] fakeArticles[i];
//                         }
//                         delete[] fakeArticles;
//                     }   
//                     break;

//                 case 3:
//                     cout << "Returning to Arrays Menu..." << endl;
//                     return;
//                 default: cout << "Invalid" << endl;
//             }
//         }

//         bool RegInput(int value){
//             return (value==3||value==2||value==1);
//         }

//         bool RegInput2(int value){
//             return (value==5 ||value==4||value==3||value==2||value==1);
//         }

//         bool RegInput3(int value){
//             return (value==6||value==5 ||value==4||value==3||value==2||value==1);
//         }
// };
// #endif