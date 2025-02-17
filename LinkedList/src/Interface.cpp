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
            int choice;
            prinTable(1);
            cout << "1. Fake Articles Only" << endl;
            cout << "2. True Articles Only" << endl;
            cout << "3. Both Fake and True Articles Only" << endl;
            cout << "4. Return to Main Menu" << endl;
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
                    cout << "Returning to Linked List Menu..." << endl;
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
                    cout << "Nothing here yet." << endl;
                    break;
                case 2:
                    cout << "Nothing here yet." << endl;
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
                    cout << "Returning to Linked List Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }     
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
            int choice;
            prinTable(3);
            cout << " Select Searching Algorithm" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "3. Return to Main Menu" << endl;
            columns();     
            cout << "Please Enter your choice.... ";
            while(!(cin>>choice)|| !(RegInput2(choice))){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid.. Please Enter your choice again.... ";
            }
            switch(choice) {
                case 1:
                    cout << "Linear Search Functionality here" << endl;
                    break;
                case 2:
                    cout << "Binary Search Functionality here" << endl;
                    break;
                case 3: 
                    cout << "Returning to Linked List Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }
        }

        bool RegInput(int value){
            return (value==3||value==2||value==1);
        }

        bool RegInput2(int value){
            return (value==5 ||value==4||value==3||value==2||value==1);
        }
};
