#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#ifdef byte
  #undef byte
#endif


// checkFake_True_news\header\PerformanceProfiler.hpp
#include <limits>
#include <fstream>
#include <iostream>
#include <limits>
#include "header/Arrays_Manipulation.hpp"
#include "DataManagement.cpp"
#include "Statistics.cpp"
#include "header/Arrays.hpp"
#include "../../header/PerformanceProfiler.hpp"

using namespace std;
class AppInterface
{   
    private:
        dataManagement True;
        dataManagement Fake;
        

        int trueSize;
        int fakeSize;

        string** trueArticles;
        string** fakeArticles;

        ArraysAlgo algo;

    public:
        AppInterface() {
            // Load data from CSV files
            True.ReadData(True.getTrueData());
            Fake.ReadData(Fake.getFakeData());

            // Get sizes after data is loaded
            trueSize = True.getsize();
            fakeSize = Fake.getsize();

            
            trueArticles = True.StoreToArray(trueSize);
            fakeArticles = Fake.StoreToArray(fakeSize);
        }
                
        string** duplicateArticles(string** original, int size) {
            string** copy = new string*[size];
            for (int i = 0; i < size; i++) {
                copy[i] = new string[6];
                for (int j = 0; j < 6; j++) {
                    copy[i][j] = original[i][j];
                }
            }
            return copy;
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

        bool ValidInput(int value, int max, int min){
            return (value <= max && value >= min);
        }

        void pauseProgram() {
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
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
                case 3: return "ARRAYS MANAGEMENT";
                case 4: return "FAQ";
                default:    return "none";                   
            }
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
                case 1:
                    cout << "Sorting True Articles" << endl;
                    True.ApplySort(trueArticles, trueSize, 3, 4);
                    cout << "Sorting Fake Articles" << endl;
                    Fake.ApplySort(fakeArticles, fakeSize, 3, 4);
                    
                    profileAlgorithm("Calculate Fake News Percentage: %", "O(n)", "O(1)", [&]() {
                        algo.calculateFakeNewsPercentage(trueArticles, trueSize, fakeArticles, fakeSize);
                    });
                    
                    pauseProgram(); 
                    break;

                case 2:
                    cout << "Sorting True Articles" << endl;
                    True.ApplySort(trueArticles, trueSize, 3, 4);
                    cout << "Sorting Fake Articles" << endl;
                    Fake.ApplySort(fakeArticles, fakeSize, 3, 4);                    
                   
                    profileAlgorithm("Calculate Fake News Percentage: %", "O(n)", "O(1)", [&]() {
                        algo.displayFakeNewsPercentageByMonth(trueArticles, trueSize, fakeArticles, fakeSize);
                    });
                   
                    
                    pauseProgram();  
                    break;

                case 3: {
                    string** fakeArticlesCopy = duplicateArticles(fakeArticles, fakeSize);
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
                    // string** fakeArticlesCopy = duplicateArticles(fakeArticles, fakeSize);
                    
                    switch(choice) {
                        case 1:
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Tokenization Words using Hash: ", "O(n)", "O(1)", [&]() {
                                    Fake.tokenizeWordsHash(fakeArticlesCopy, fakeSize);
                                });
                            });
                            
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, 0, " ", 0, 1);
                            pauseProgram();  
                            break;
                        case 2:
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Tokenization Linear", "O(n)", "O(1)", [&]() {
                                    Fake.tokenizeWords(fakeArticlesCopy, fakeSize);
                                });
                            });
                            
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, 0, " ", 0, 1);
                            
                            pauseProgram();  
                            break;
                        case 3:
                            cout << "Returning to FAQ Menu..." << endl;
                            return;
                        default: 
                            cout << "Invalid" << endl;
                            break;
                    }
                    break;
                }
                case 4:
                    cout << "True Data Size: " << trueSize << endl;
                    cout << "Fake Data Size: " << fakeSize << endl;
                    cout << "Total Size of both datasets: " << trueSize + fakeSize << endl;
                    
                    pauseProgram();
                    break;

                case 5:
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }

        }



        void SortData(){
            clearScreen();
            prinTable(1);
            int choice;
            cout << " Select Sorting Algorithm" << endl;
            cout << "1. Insertion Sort" << endl;
            cout << "2. Bubble Sort" << endl;
            cout << "3. Quick Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Return to Arrays Menu" << endl;
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
                string** trueArticlesCopy = duplicateArticles(trueArticles, trueSize);
                string** fakeArticlesCopy = duplicateArticles(fakeArticles, fakeSize);
                
                switch(choice){
                    case 1: 
                        if (field == 1) {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Insertion Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    True.ApplySort(trueArticlesCopy, trueSize, 3, choice);
                                });

                            });
                            
                            cout << "Insertion Sort dataChoice Field: " << field << endl;
                            algo.compareAndDisplayPerformance(trueArticles, trueSize, choice, " ", field, 2);
                            True.DeleteArray(trueArticlesCopy, trueSize);
                        } else {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Insertion Sort for False: ", "O(n^2)", "O(n)", [&]() {
                                    Fake.ApplySort(fakeArticlesCopy, fakeSize, 3, choice);
                                });
                            });
                            
                            
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice, " ", field, 2);
                            Fake.DeleteArray(fakeArticlesCopy, fakeSize);
                        }
                        pauseProgram();  
                        break;
                    case 2: 
                        if (field == 1) {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Bubble Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    True.ApplySort(trueArticlesCopy, trueSize, 3, choice);
                                });
                            });
                            
                        
                            algo.compareAndDisplayPerformance(trueArticles, trueSize, choice, " ", field, 2);
                            True.DeleteArray(trueArticlesCopy, trueSize);
                        } else {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Bubble Sort for False: ", "O(n^2)", "O(n)", [&]() {
                                    Fake.ApplySort(fakeArticlesCopy, fakeSize, 3, choice);
                                });
                            });
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice, " ", field, 2);
                            Fake.DeleteArray(fakeArticlesCopy, fakeSize);
                        }
                        pauseProgram();  
                        break;
                    case 3: 
                        if (field == 1) {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Quick Sort for True: ", "O(n^2)", "O(n)", [&]() {
                                    True.ApplySort(trueArticlesCopy, trueSize, 3, choice);
                                });
                            });
                            algo.compareAndDisplayPerformance(trueArticles, trueSize, choice, " ", field, 2);
                            True.DeleteArray(trueArticlesCopy, trueSize);
                            
                        } else {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Quick Sort for False: ", "O(n^2)", "O(n)", [&]() {
                                    Fake.ApplySort(fakeArticlesCopy, fakeSize, 3, choice);
                                });
                            });
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice, " ", field, 2);
                            Fake.DeleteArray(fakeArticlesCopy, fakeSize);
                        }
                        pauseProgram();  
                        break;
                    case 4: 
                        if (field == 1) {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Bottom Up Merge Sort for True: ", "O(n log n)", "O(n)", [&]() {
                                    True.ApplySort(trueArticlesCopy, trueSize, 3, choice);
                                });
                            });
                            algo.compareAndDisplayPerformance(trueArticles, trueSize, choice, " ", field, 2);
                            True.DeleteArray(trueArticlesCopy, trueSize);
                            
                        } else {
                            runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                                profileAlgorithm("Merge Sort for False: ", "O(nlog(n))", "O(n)", [&]() {
                                    Fake.ApplySort(fakeArticlesCopy, fakeSize, 3, choice);
                                });
                            });
                            algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice, " ", field, 2);
                            Fake.DeleteArray(fakeArticlesCopy, fakeSize);
                        }
                        pauseProgram();  
                        break;
                    case 5: 
                        cout << "Returning to Arrays Menu..." << endl;
                        return;
                    default: cout << "Invalid";
                }
                            
        }

        void SearchData(){
            clearScreen();
            int choice;
            int choice2;
            string field;
            prinTable(2);
            cout << " Select Searching Algorithm" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "3. Return to Arrays Menu" << endl;
            columns();    
            cout << "Please Enter your choice.... ";
            while(!(cin>>choice)|| !ValidInput(choice, 3, 1)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid.. Please Enter your choice again.... ";
            }

            int setChoice;
                cout << "Chose to sort by true or false."<<endl;
                cout << "1. True "<<endl;
                cout << "2. False "<<endl;
                columns();
                cout << "Please enter your choice: ";
                
                while(!(cin >> setChoice)|| !ValidInput(setChoice, 2, 1)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Invalid Input... Enter Your choice Again: ";
                }

            switch(choice){
                case 1:
                    cout << "Chose a field to search for"<<endl;
                    cout << "1. Title "<<endl;
                    cout << "2. Text " << endl;
                    cout << "3. Subject "<<endl;
                    cout << "4. Year "<<endl;
                    cout << "5. Month "<<endl;
                    cout << "Please Enter your choice.... ";
                    while(!(cin>>choice2)|| !ValidInput(choice2, 5, 1)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid.. Please Enter your choice again.... ";
                    }
                    cin.ignore();
                    cout << "Enter the keyword or value to search for: ";
                    getline(cin, field);
                    
                    if (setChoice == 1) {
                        True.ApplySort(trueArticles, trueSize, 3, 2);
                        
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Linear Search", "O(n)", "O(1)", [&]() {
                                algo.LinearSearch(trueArticles, choice2-1, field, trueSize);
                            });
                        });
                        algo.compareAndDisplayPerformance(trueArticles, trueSize, choice2-1, field, setChoice, 3);
                        
                        for (int i = 0; i < trueSize; ++i) {
                            delete[] trueArticles[i];
                        }
                        delete[] trueArticles;
                    } else {
                        Fake.ApplySort(fakeArticles, fakeSize, 3, 2);
                        
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Linear Search", "O(n)", "O(1)", [&]() {
                                algo.LinearSearch(fakeArticles, choice2-1, field, fakeSize);
                            });
                        });
                        algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice2-1, field, setChoice, 3);
                        
                        for (int i = 0; i < fakeSize; ++i) {
                            delete[] fakeArticles[i];
                        }
                        delete[] fakeArticles;
                    }
                    pauseProgram();  
                    break;

                case 2:
                    cout << "Chose a field to search for"<<endl;
                    cout << "1. Title "<<endl;
                    cout << "2. Text "<<endl;
                    cout << "3. Subject "<<endl;
                    cout << "4. Year "<<endl;
                    cout << "5. Month "<<endl;
                    cout << "Please Enter your choice.... ";
                    while(!(cin>>choice2)|| !ValidInput(choice2, 5, 1)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid.. Please Enter your choice again.... ";
                    }
                    cin.ignore();
                    cout << "Enter the keyword or value to search for: ";
                    getline(cin, field);
                    
                    if (setChoice == 1) {
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Binary Search", "O(log n)", "O(1)", [&]() {
                                algo.BinarySearch(trueArticles, choice2-1, field, trueSize);
                            });
                        });
                        algo.compareAndDisplayPerformance(trueArticles, trueSize, choice2-1, field, setChoice, 3);
                        
                        for (int i = 0; i < trueSize; ++i) {
                            delete[] trueArticles[i];
                        }
                        delete[] trueArticles;
                    } else {
                        runWithRedirectedOutput("dataSets/profile_output.txt", [&]() {
                            profileAlgorithm("Binary Search", "O(log n)", "O(1)", [&]() {
                                algo.BinarySearch(fakeArticles, choice2-1, field, fakeSize);
                            });
                        });
                        algo.compareAndDisplayPerformance(fakeArticles, fakeSize, choice2-1, field, setChoice, 3);
                        
                        for (int i = 0; i < fakeSize; ++i) {
                            delete[] fakeArticles[i];
                        }
                        delete[] fakeArticles;
                    }  
                    pauseProgram();   
                    break;

                case 3:
                    cout << "Returning to Arrays Menu..." << endl;
                    return;
                default: cout << "Invalid" << endl;
            }
        }
};



int main(){ 
    AppInterface appInterface;
    int choice;
    bool running = true;

    while(running) {
        appInterface.clearScreen();
        appInterface.prinTable(3);
        cout << "1. Sort Data Comparison" << endl;
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
                break;
            default: cout << "Invalid";
        }
    }
    return 0;
}
