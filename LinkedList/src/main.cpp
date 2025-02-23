#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#ifdef byte
  #undef byte
#endif

#include <iostream>
#include <limits>
#include "header/LinkedList_Manipulation.hpp"
#include "header/LinkedList.hpp"
#include "DataManagement.cpp"
#include "Statistics.cpp"
#include "../../header/PerformanceProfiler.hpp"

using namespace std;
article* result = nullptr;

class AppInterface
{   
    private:
        dataManagement True;
        dataManagement Fake;

        int trueSize;
        int fakeSize;

        LinkedListAlgo algo;

    public:
        AppInterface() {
            True.ReadData(True.getTrueData());
            Fake.ReadData(Fake.getFakeData());

            trueSize = True.getsize();
            fakeSize = Fake.getsize();
        }

        void clearScreen() {
            cout << "\033[2J\033[1;1H";  // ANSI escape code to clear screen and move cursor to top-left
        }

        void columns(){
            for(int i=0; i<=80; i++){
                cout << "="<<left;
            }
            cout <<endl;
        }
        void prinTable(int o){
            string msg = this->msg(o);  // Use the current object
            columns();
            cout << string(26, ' ') << msg << endl;
            columns();
        }
        
        string msg(int o){
            switch(o){
                case 1: return "Sort Data";
                case 2: return "Search Data";
                case 3: return "Linked List Management";
                case 4: return "FAQ";
                default: return "none";                   
            }
        }

        void pauseProgram() {
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

        bool ValidInput(int value, int max, int min){
            return (value <= max && value >= min);
        }


        void FAQ(){
            int FAQchoice;
            clearScreen();
            prinTable(4);
            cout << "1. What percentage of political news articles from the year of 2016 are fake? " << endl;
            cout << "2. Percentage of fake political news articles for each month in 2016." << endl;
            cout << "3. Which words are most frequently used in fake news articles related to government topics?" << endl;
            cout << "4. What is the total number of articles in both true and fake news datasets?" << endl;
            cout << "5. Return to Arrays Menu" << endl;
            columns(); 
            cout << "Enter choice: ";  
            while(!(cin >> FAQchoice) || !ValidInput(FAQchoice, 5, 1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter your choice again: ";
            }

            switch(FAQchoice) {
                case 1: {
                    profileAlgorithm("Calculate Fake News Percentage: ", "O(n)", "O(1)", [&]() {
                        True.calculatePoliticalFakePercentage(True.gethead(), Fake.gethead());
                    });
                    
                    pauseProgram(); 
                    break;}

                case 2:
                    profileAlgorithm("Calculate Fake News Precentage Monthly: ", "O(n)", "O(1)", [&]() {
                        True.analyzeMonthlyFakePoliticalNews(Fake.gethead());
                    });
                    
                    pauseProgram(); 
                    break;

                case 3:
                    cout << "Word Frequency: " << endl;
                    cout << "1. Hashmap" << endl;
                    cout << "2. Linear Search." << endl;
                    cout << "3. Return to FAQ Menu" << endl;
                    columns();
                    cout << "Enter choice: ";
                    int choice;
                    while(!(cin >> choice) || !ValidInput(choice, 3, 1)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "Invalid Input... Enter your choice again: ";
                    }
                    
                    switch(choice) {
                        case 1:
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Tokenization Words using Hash: ", "O(n)", "O(1)", [&]() {
                                    Fake.tokenizeWordsHash(Fake.gethead());
                                });
                            });
                            
                            algo.compareAndDisplayPerformance(Fake.gethead(), 0, "0", result, 1);
                            pauseProgram();  
                            break;

                        case 2:
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Tokenization Words using Linear: ", "O(n)", "O(1)", [&]() {
                                    Fake.tokenizeWords(Fake.gethead());
                                });
                            });
                            
                            algo.compareAndDisplayPerformance(Fake.gethead(), 0, "0", result, 1);
                            // Fake.tokenizeWords(Fake.gethead());
                            pauseProgram();  
                            break;

                        case 3:
                            cout << "Returning to FAQ Menu..." << endl;
                            return;
                        default: cout << "Invalid" << endl;
                    }
                    break;
                case 4:
                    cout << "True Data Size: " << trueSize << endl;
                    cout << "Fake Data Size: " << fakeSize << endl;
                    cout << "Total Size of both datasets: " << trueSize + fakeSize << endl;
                    break;

                case 5:
                    cout << "Returning to Linked List Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }     
        }

        void SortData(){
            int choice, sortType;
            // article* result = nullptr;
            clearScreen();
            prinTable(1);
            cout << " Select Sorting Algorithm" << endl;
            cout << "1. Insertion Sort" << endl;
            cout << "2. Bubble Sort" << endl;
            cout << "3. Quick Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Return to Main Menu" << endl;
            columns();    
            
            cout << "Please Enter your choice: ";
            
            while(!(cin >> choice)|| !ValidInput(choice, 5, 1)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid Input... Enter Your choice Again: ";
            }

            int field;
            cout << "Chose to sort by true or false."<<endl;
            cout << "1. True "<<endl;
            cout << "2. False "<<endl;
            columns();
            cout << "Please enter your choice: ";
            
            while(!(cin >> field)|| !ValidInput(field, 2, 1)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter Your choice Again: ";
            }

            cout << "Sort by:" << endl;
            cout << "1. Subject" << endl;
            cout << "2. Date" << endl;
            cout << "Enter your choice: ";
            while(!(cin >> sortType)|| !ValidInput(sortType, 2, 1)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter Your choice Again: ";
            }
            article* TrueUnsortedCopy = True.copyList(True.gethead());
            article* FakeUnsortedCopy = Fake.copyList(Fake.gethead());
            
            switch(choice){
                case 1: 
                    if (field == 1) {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Insertion Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                sortedHead = algo.sortArticles(TrueUnsortedCopy, choice, sortType);
                            });
                        });
                        True.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(True.gethead(), sortType, IntToString(field), result, 2);
                    } else {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("insertion Sort for Fake: ", "O(n^2)",  "O(n)", [&]() {
                                sortedHead = algo.sortArticles(FakeUnsortedCopy, choice, sortType);
                            });
                        });
                        Fake.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(Fake.gethead(), sortType, IntToString(field), result, 2);
                    }
                    
                    
                    pauseProgram();  
                    break;
                case 2: 
                    if (field == 1) {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Bubble Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                sortedHead = algo.sortArticles(TrueUnsortedCopy, choice, sortType);
                            });
                        });
                        True.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(True.gethead(), sortType, IntToString(field), result, 2);
                    }   else {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Bubble Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                sortedHead = algo.sortArticles(FakeUnsortedCopy, choice, sortType);
                            });
                        });
                        Fake.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(Fake.gethead(), sortType, IntToString(field), result, 2);
                    }

                    pauseProgram();  
                    break;
                case 3: 
                    if (field == 1) {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Quick Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                sortedHead = algo.sortArticles(TrueUnsortedCopy, choice, sortType);
                            });
                        });
                        True.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(True.gethead(), sortType, IntToString(field), result, 2);
                    } else {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Quick Sort for Fake: ", "O(n^2)", "O(n)", [&]() {
                                sortedHead = algo.sortArticles(FakeUnsortedCopy, choice, sortType);
                            });
                        });
                        Fake.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(Fake.gethead(), sortType, IntToString(field), result, 2);
                    }
                    pauseProgram();  
                    break;
                case 4: {
                    if (field == 1) {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Bottom Up Merge Sort for True: ", "O(n log n)", "O(1)", [&]() {
                                sortedHead = algo.sortArticles(TrueUnsortedCopy, choice, sortType);
                            });
                        });
                        True.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(True.gethead(), sortType, IntToString(field), result, 2);
                    } else {
                        article* sortedHead = nullptr;
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Bottom Up Merge Sort for Fake: ", "O(n log n)", "O(1)", [&]() {
                                sortedHead = algo.sortArticles(FakeUnsortedCopy, choice, sortType);
                            });
                        });
                        Fake.DisplayArticles(sortedHead);
                        algo.compareAndDisplayPerformance(Fake.gethead(), sortType, IntToString(field), result, 2);
                    }
                    pauseProgram();  
                    break;
                }
                case 5: 
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default: cout << "Invalid";
            }
            // delete temp;
        }


        void SearchData() {
            int choice;
            clearScreen();
            prinTable(2);
            cout << "Select Searching Algorithm" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Recursive Search" << endl;
            cout << "3. Return to Main Menu" << endl;
            columns();     
            cout << "Please Enter your choice.... ";
        
            while (!(cin >> choice) || !ValidInput(choice, 3, 1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid.. Please Enter your choice again.... ";
            }

            int field;
            cout << "Chose to sort by true or false."<<endl;
            cout << "1. True "<<endl;
            cout << "2. False "<<endl;
            columns();
            cout << "Please enter your choice: ";
            
            while(!(cin >> field)|| !ValidInput(field, 2, 1)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid Input... Enter Your choice Again: ";
            }


            switch(choice) {
                case 1: 
                    if (field == 1) {
                        algo.userSearchAndSwitch(True.gethead(), choice);
                        
                    } else {
                        algo.userSearchAndSwitch(Fake.gethead(), choice);
                    }
                    pauseProgram(); 
                    break;
                case 2:
                    if (field == 1) {
                        algo.userSearchAndSwitch(True.gethead(), choice);
                    } else {
                        algo.userSearchAndSwitch(Fake.gethead(), choice);
                    }
                    pauseProgram(); 
                    break;
                case 3:
                    cout << "Returning to Linked List Menu..." << endl;
                break;
                default: 
                    cout << "Invalid input choose correct options" << endl;
                    break;
            }
        }
};



using namespace std;
int main(){ 
    AppInterface appInterface;
    
    int choice;
    bool running = true;

    while(running) {
        appInterface.clearScreen();
        appInterface.prinTable(3);
        cout << "1. Sort Data" << endl;
        cout << "2. Search Data" << endl;
        cout << "3. FAQ" << endl;
        cout << "4. End the Program" << endl;
        appInterface.columns();
        cout << "Enter Your choice: ";
        while(!(cin >> choice)|| !appInterface.ValidInput(choice, 4, 1)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid Input... Enter Your choice Again: ";
        }
        switch(choice){
            case 1: 
                appInterface.SortData();
                break;
            case 2: 
                appInterface.SearchData();
                break;
            case 3: 
                appInterface.FAQ();
                break;
            case 4: 
                cout <<"Existing the program. GoodBye!";
                running = false;
                return 0;
            default: cout << "Invalid";
        }

    }
    return 0;
}