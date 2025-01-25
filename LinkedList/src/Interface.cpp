#include <iostream>
#include <limits>

using namespace std;
class Interface
{   
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
                case 4: return "Linked List Management";
                case 5: return "FAQ";
                default: return "none";                   
            }
        }
        void DataFilterting(){
            prinTable(1);
            cout << "1. Fake Articles Only" << endl;
            cout << "2. True Articles Only" << endl;
            cout << "3. Both Fake and True Articles Only" << endl;
            cout << "4. Return to Main Menu" << endl;
            columns();
            
        }
        void FAQ(){
            prinTable(5);
            cout << "1. What is the difference between fake and true articles?" << endl;
            cout << "2. What algorithms are used for sorting and searching?" << endl;
            cout << "3. How do I filter articles by date or country?" << endl;
            cout << "4. How do I export data to a CSV file" << endl;
            cout << "5. Return to Main Menu" << endl;
            columns();     
        }
        void SortData(){
            prinTable(2);
            cout << " Select Sorting Algorithm" << endl;
            cout << "1.  Sort" << endl;
            cout << "2.  Sort" << endl;
            cout << "3.  Sort" << endl;
            cout << "4. Sort" << endl;
            cout << "5. Return to Main Menu" << endl;
            columns();     
        }

        void SearchData(){
            prinTable(3);
            cout << " Select Searching Algorithm" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "3. Return to Main Menu" << endl;
            columns();     
        }

        bool RegInput(int value){
            return (value==5 ||value==4||value==3||value==2||value==1);
        }
};
