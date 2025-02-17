#include <iostream>
#include <limits>
#include "header/Arrays_Manipulation.hpp"
#include "DataManagement.cpp"
#include "header/Arrays.hpp"

#ifndef Interface_HPP
#define Interface_HPP
using namespace std;
class Interface
{   
    private:
        dataManagement Data;
        ArraysAlgo algo;
    
    public:
        void columns(){
            for(int i=0; i<=80; i++){
                cout << "="<<left;
            }
            cout <<endl;
        }
        void prinTable(int o){
            Interface interface;
            string msg=interface.msg(o);
            columns();
            cout <<string(26, ' ') << msg;
            cout <<endl;
            columns();
        }

        string msg(int o){
            switch(o){
                case 1: return "Data Filtering";
                case 2: return "Sort Data";
                case 3: return "Search Data";
                case 4: return "ARRAYS MANAGEMENT";
                case 5: return "FAQ";
                default:    return "none";                   
            }
        }
        void DataFilterting(){
            int choice;
            prinTable(1);
            cout << "1. Fake Articles Only" << endl;
            cout << "2. True Articles Only" << endl;
            cout << "3. Both Fake and True Articles Only" << endl;
            cout << "4. Return to Arrays Menu" << endl;
            columns();
            cout << "Enter choice: ";  
            while(!(cin >> choice) || choice <= 4 || choice >= 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter your choice again: ";
            }
            switch(choice) {
                case 1: 
                    cout << "Display Fake Articles" << endl;
                    break;
                case 2:
                    cout << "Display True Articles" << endl;
                    break;
                case 3:
                    cout << "Display All Articles" << endl;
                    break;
                case 4:
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }
        }

        void FAQ(){
            int FAQchoice;
            prinTable(5);
            cout << "1. What percentage of political news articles from the year of 2016 are fake? " << endl;
            cout << "2. Percentage of fake political news articles for each month in 2016." << endl;
            cout << "3. Which words are most frequently used in fake news articles related to government topics?" << endl;
            cout << "4. What is the total number of articles in both true and fake news datasets?" << endl;
            cout << "5. Search for Specific article." << endl;
            cout << "6. Return to Arrays Menu" << endl;
            columns(); 
            cout << "Enter choice: ";  
            while(!(cin >> FAQchoice) || !(RegInput3(FAQchoice))) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter your choice again: ";
            }

            switch(FAQchoice) {
                case 1:
                    algo.calculateFakeNewsPercentage(trueNews, trueSize, fakeNews, fakeSize);
                    break;
                case 2:
                    algo.displayFakeNewsPercentageByMonth(trueNews, trueSize, fakeNews, fakeSize);
                    break;
                case 3:
                    cout << "Nothing here yet." << endl;
                    break;
                case 4:
                    cout << "Nothing here yet." << endl;
                    break;
                case 5:
                    cout << "Nothing here yet." << endl;
                    break;
                case 6:
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }

        }



        void SortData(){
            prinTable(2);
            int choice;
            cout << " Select Sorting Algorithm" << endl;
            cout << "1. Insertion Sort" << endl;
            cout << "2. Bubble Sort" << endl;
            cout << "3. Quick Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Return to Arrays Menu" << endl;
            columns(); 
            while(!(cin >> choice)|| !(RegInput(choice))){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid Input... Enter Your choice Again: ";
                }
                switch(choice){
                    case 1: 
                        Data.ApplySortH(string**& array, int size, int field, 3);
                        break;
                    case 2: 
                        Data.ApplySortH(string**& array, int size, int field, 2);
                        break;
                    case 3: 
                        Data.ApplySortH(string**& array, int size, int field, int sortType);
                        break;
                    case 4: 
                        Data.ApplySortH(string**& array, int size, int field, 1);
                        break;
                    case 5: 
                        cout << "Returning to Arrays Menu..." << endl;
                        return;
                    default: cout << "Invalid";
                }
                            
        }

        void SearchData(){           
            Data.ReadData(Data.getTrueData());
            string** arr=Data.StoreToArray(Data.getsize());
            int choice;
            int choice2;
            string field;
            prinTable(3);
            cout << " Select Searching Algorithm" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "3. Return to Arrays Menu" << endl;
            columns();    
            cout << "Please Enter your choice.... ";
            while(!(cin>>choice)|| !(RegInput(choice))){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid.. Please Enter your choice again.... ";
            }
            switch(choice){
                case 1:
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
        
                    algo.LinearSearch(arr, choice2, field, Data.getsize());
                    for (int i = 0; i < Data.getsize(); ++i) {
                        delete[] arr[i];
                    }
                    delete[] arr;
                    break;
                case 2:
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
        
                    algo.BinarySearch(arr, choice2, field, Data.getsize());
                    for (int i = 0; i < Data.getsize(); ++i) {
                        delete[] arr[i];
                    }
                    delete[] arr;
                    break;
                case 3:
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default:
            }

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
};
#endif