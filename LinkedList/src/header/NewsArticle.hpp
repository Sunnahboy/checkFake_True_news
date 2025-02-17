#ifndef NewsArticle_HPP
#define NewsArticle_HPP

#include <iostream>
#include "header/llhashmap.hpp"
#include "header/LinkedList.hpp"
#include "header/LinkedList_Manipulation.hpp"

using namespace std;

class NewsArticleProcessor {
private:
    YearHashMap articleData;

public:
    // Process linked list instead of 2D array
    void processArticles(article* head) {
        article* current = head;
        while (current != nullptr) {
            int year = current->year;
            int month = current->month;
            int day = current->day;
            articleData.insert(year, month, day);
            current = current->next; // Move to next article
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

// Helper functions
bool isValidYear(int year, string dataset) {
    if (dataset == "true") return (year >= 2016 && year <= 2017);
    return (year >= 2015 && year <= 2017);
}

bool isValidMonth(int month) {
    return month >= 1 && month <= 12;
}

bool isValidDay(int year, int month, int day) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && (year % 4 == 0)) daysInMonth[1] = 29;  // Leap year check
    return day >= 1 && day <= daysInMonth[month - 1];
}

void displayTable(string title, int value) {
    cout << "\n=====================================\n";
    cout << "         " << title << "\n";
    cout << "=====================================\n";
    cout << "|     Category     |   Articles   |\n";
    cout << "-------------------------------------\n";
    cout << "| " << title << "  |     " << value << "    |\n";
    cout << "=====================================\n";
}

// Callable function instead of `main()`
void runNewsProcessor() {
    dataManagement data("News Articles");
    string datasetChoice;

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

    // Use linked list head directly
    article* head = data.gethead();
    
    NewsArticleProcessor processor;
    processor.processArticles(head); // Pass the linked list to process

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
            int year;
            while (true) {
                cout << "Enter year: ";
                cin >> year;
                if (isValidYear(year, datasetChoice)) break;
                cout << "Invalid year. Please enter a valid year for this dataset.\n";
            }

            int total = processor.getArticleCount(year);
            displayTable("Articles in " + to_string(year), total);

        } else if (option == 2) {
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

        } else if (option == 3) {
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
            break;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }
}

#endif 
