#ifndef NewsArticle_HPP
#define NewsArticle_HPP

#include <iostream>
#include "llhashmap.hpp"
#include "LinkedList.hpp"
#include "LinkedList_Manipulation.hpp"

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
};

#endif 
