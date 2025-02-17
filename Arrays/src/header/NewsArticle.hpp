#ifndef NEWS_ARTICLE_HPP
#define NEWS_ARTICLE_HPP

#include <iostream>
#include "HashMap.hpp"

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

    bool isValidYear(int year, const string& dataset) {
        return (dataset == "true") ? (year >= 2016 && year <= 2017) : (year >= 2015 && year <= 2017);
    }

    bool isValidMonth(int month) {
        return month >= 1 && month <= 12;
    }

    bool isValidDay(int year, int month, int day) {
        static int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && (year % 4 == 0)) daysInMonth[1] = 29;  // Leap year check
        return day >= 1 && day <= daysInMonth[month - 1];
    }

    void displayTable(const string& title, int value) {
        cout << "\n=====================================\n";
        cout << "         " << title << "\n";
        cout << "=====================================\n";
        cout << "|     Category     |   Articles   |\n";
        cout << "-------------------------------------\n";
        cout << "| " << title << "  |     " << value << "    |\n";
        cout << "=====================================\n";
    }
};

#endif // NEWS_ARTICLE_HPP
