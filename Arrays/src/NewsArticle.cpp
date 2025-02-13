// #include <iostream>
// #include "header/HashMap.hpp"
// #include "header/Arrays_Manipulation.hpp"
// using namespace std;

// class NewsArticleProcessor {
// private:
//     YearHashMap articleData;

// public:
//     void processArticles(string** articles, int size) {
//         for (int i = 0; i < size; i++) {
//             int year = stoi(articles[i][3]);
//             int month = stoi(articles[i][4]);
//             int day = stoi(articles[i][5]);
//             articleData.insert(year, month, day);
//         }
//     }

//     void displaySummary(int year, int month, int day) {
//         int count = articleData.get(year, month, day);
//         cout << "Articles published on " << day << "/" << month << "/" << year << ": " << count << endl;
//     }
// };

// int main() {
//     dataManagement data;
//     string choice;

//     // Ask the user whether to process True News or Fake News dataset
//     cout << "Select dataset to process (true/fake): ";
//     cin >> choice;

//     if (choice == "true") {
//         data.ReadData(data.getTrueData()); // Load True News dataset
//     } else if (choice == "fake") {
//         data.ReadData(data.getFakeData()); // Load Fake News dataset
//     } else {
//         cout << "Invalid choice. Exiting program." << endl;
//         return 1;
//     }

//     int size = data.getsize();
//     string** articles = data.StoreToArray(size);

//     NewsArticleProcessor processor;
//     processor.processArticles(articles, size);

//     // Display analytics for all years, months, and days
//     cout << "\n=== Article Count by Date ===\n";
//     for (int year = 2016; year <= 2018; ++year) {  // Adjust based on dataset
//         for (int month = 1; month <= 12; ++month) {
//             for (int day = 1; day <= 31; ++day) {
//                 processor.displaySummary(year, month, day);
//             }
//         }
//     }

//     // Cleanup memory
//     for (int i = 0; i < size; ++i) {
//         delete[] articles[i];
//     }
//     delete[] articles;

//     return 0;
// }


#include <iostream>
#include "header/HashMap.hpp"
#include "header/Arrays_Manipulation.hpp"
using namespace std;

class NewsArticleProcessor {
private:
    YearHashMap articleData;

public:
    void processArticles(string** articles, int size) {
        for (int i = 0; i < size; i++) {
            int year = stoi(articles[i][3]);
            int month = stoi(articles[i][4]);
            int day = stoi(articles[i][5]);
            articleData.insert(year, month, day);
        }
    }

    int getArticleCount(int year, int month = -1, int day = -1) {
        if (month == -1) {  // Yearly count
            int total = 0;
            for (int m = 1; m <= 12; ++m) {
                for (int d = 1; d <= 31; ++d) {
                    total += articleData.get(year, m, d);
                }
            }
            return total;
        }
        if (day == -1) {  // Monthly count
            int total = 0;
            for (int d = 1; d <= 31; ++d) {
                total += articleData.get(year, month, d);
            }
            return total;
        }
        return articleData.get(year, month, day);  // Daily count
    }
};

// ✅ Function to validate year input
bool isValidYear(int year, string dataset) {
    if (dataset == "true") return (year >= 2016 && year <= 2017);
    return (year >= 2015 && year <= 2017);
}

// ✅ Function to validate month input
bool isValidMonth(int month) {
    return month >= 1 && month <= 12;
}

// ✅ Function to validate day input based on month
bool isValidDay(int year, int month, int day) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && (year % 4 == 0)) daysInMonth[1] = 29;  // Leap year check
    return day >= 1 && day <= daysInMonth[month - 1];
}

// ✅ Function to display a table
void displayTable(string title, int value) {
    cout << "\n=====================================\n";
    cout << "         " << title << "\n";
    cout << "=====================================\n";
    cout << "|     Category     |   Articles   |\n";
    cout << "-------------------------------------\n";
    cout << "| " << title << "  |     " << value << "    |\n";
    cout << "=====================================\n";
}

int main() {
    dataManagement data;
    string datasetChoice;

    // ✅ Step 1: Ask the user to choose a dataset
    while (true) {
        cout << "Select dataset to process (true/fake): ";
        cin >> datasetChoice;

        if (datasetChoice == "true") {
            data.ReadData(data.getTrueData());
            break;
        } else if (datasetChoice == "fake") {
            data.ReadData(data.getFakeData());
            break;
        } else {
            cout << "Invalid choice. Please enter 'true' or 'fake'." << endl;
        }
    }

    // ✅ Step 2: Store data in an array and process it
    int size = data.getsize();
    string** articles = data.StoreToArray(size);
    
    NewsArticleProcessor processor;
    processor.processArticles(articles, size);

    // ✅ Step 3: Display menu and allow user interaction
    while (true) {
        int option;
        cout << "\nSelect analysis type:\n";
        cout << "1. View articles per year\n";
        cout << "2. View articles per month\n";
        cout << "3. View articles per day\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            // ✅ Yearly Analysis
            int year;
            while (true) {
                cout << "Enter year: ";
                cin >> year;
                if (isValidYear(year, datasetChoice)) break;
                cout << "Invalid year. Please enter a valid year for this dataset.\n";
            }

            int total = processor.getArticleCount(year);
            displayTable("Articles in " + to_string(year), total);
            cout << "Average articles per year: " << total / 1 << endl;  // Placeholder for median/mode

        } else if (option == 2) {
            // ✅ Monthly Analysis
            int year, month;
            while (true) {
                cout << "Enter year: ";
                cin >> year;
                if (isValidYear(year, datasetChoice)) break;
                cout << "Invalid year. Try again.\n";
            }

            while (true) {
                cout << "Enter month (1-12): ";
                cin >> month;
                if (isValidMonth(month)) break;
                cout << "Invalid month. Try again.\n";
            }

            int total = processor.getArticleCount(year, month);
            displayTable("Articles in " + to_string(year) + " - Month " + to_string(month), total);
            cout << "Average articles per month: " << total / 1 << endl;  // Placeholder for median/mode

        } else if (option == 3) {
            // ✅ Daily Analysis
            int year, month, day;
            while (true) {
                cout << "Enter year: ";
                cin >> year;
                if (isValidYear(year, datasetChoice)) break;
                cout << "Invalid year. Try again.\n";
            }

            while (true) {
                cout << "Enter month (1-12): ";
                cin >> month;
                if (isValidMonth(month)) break;
                cout << "Invalid month. Try again.\n";
            }

            while (true) {
                cout << "Enter day: ";
                cin >> day;
                if (isValidDay(year, month, day)) break;
                cout << "Invalid day. Try again.\n";
            }

            int total = processor.getArticleCount(year, month, day);
            displayTable("Articles on " + to_string(year) + "-" + to_string(month) + "-" + to_string(day), total);

        } else if (option == 4) {
            // ✅ Exit the program
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    // ✅ Step 4: Cleanup memory
    for (int i = 0; i < size; ++i) {
        delete[] articles[i];
    }
    delete[] articles;

    return 0;
}
