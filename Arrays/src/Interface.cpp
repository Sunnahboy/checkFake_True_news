#include <iostream>
#include <limits>
#include "header/Arrays_Manipulation.hpp"
#include "DataManagement.cpp"
#include "Algorithms.cpp"
#include "header/Arrays.hpp"
using namespace std;
#define TRUEMAX 21418
class Interface
{   
    private:
        dataManagement Data;
    
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
            prinTable(1);
            cout << "1. Fake Articles Only" << endl;
            cout << "2. True Articles Only" << endl;
            cout << "3. Both Fake and True Articles Only" << endl;
            cout << "4. Return to Arrays Menu" << endl;
            columns();
            
        }
        void FAQ(){
            prinTable(5);
            cout << "1. What is the difference between fake and true articles?" << endl;
            cout << "2. What algorithms are used for sorting and searching?" << endl;
            cout << "3. How do I filter articles by date or country?" << endl;
            cout << "4. How do I export data to a CSV file" << endl;
            cout << "5. Return to Arrays Menu" << endl;
            columns();     
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
                    cout << "Invaliad Input... Enter Your choice Again: ";
                }
                switch(choice){
                    case 1: 
                        cout << "Nothing here yet";
                        break;
                    case 2: 
                        cout << "Nothing here yet";
                        break;
                    case 3: 
                        cout << "Nothing here yet";
                        break;
                    case 4: 
                        cout << "Nothing here yet";
                        break;
                    case 5: 
                        cout <<"Existing the program. GoodBye!";
                        return;
                    default: cout << "Invalid";
                }
                            
        }

        void SearchData(){           
            Data.ReadData(Data.getTrueData());
            string** arr=Data.StoreToArray(TRUEMAX);
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
            cout << "Enter the keyword or value to search for: ";
            cin >> field;

            Data.LinearSearch(arr, choice2, field);
            for (int i = 0; i < TRUEMAX; ++i) {
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
};