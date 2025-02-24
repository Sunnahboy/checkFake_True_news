#include "header/LinkedList.hpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


// Helper function to check if an article's category indicates political news.
bool isPolitical(string &category) {
    // Check if "politicsNews" appears anywhere in the category.
    return (category.find("politicsNews") != string::npos || category.find("politics") != string::npos);
}

// Function to calculate the percentage of political articles from 2016 fake.
// It takes two linked lists: one for true news and one for fake news.
void dataManagement::calculatePoliticalFakePercentage(article* trueHead, article* fakeHead) {
    int totalPolitical = 0;
    int fakePolitical = 0;
    
    // Process the true news list.
    article* current = trueHead;
    while (current != nullptr) {
        if (current->year == 2016 && isPolitical(current->category)) {
            totalPolitical++;
        }
        current = current->next;
    }
    
    // Process the fake news list.
    current = fakeHead;
    while (current != nullptr) {
        if (current->year == 2016 && isPolitical(current->category)) {
            totalPolitical++;  // Count overall political articles.
            fakePolitical++;   // Count those that are fake.
        }
        current = current->next;
    }
    
    if (totalPolitical == 0) {
        cout << "No political articles from 2016 found." << endl;
        return;
    }
    
    double percentage = (fakePolitical * 100.0) / totalPolitical;
    cout << "Percentage of political news articles from 2016 that are fake: " 
         << percentage << "%" << endl;
    cout << "Total political articles from 2016: " << totalPolitical << endl;
    cout << "Total fake political articles from 2016: " << fakePolitical << endl << endl;
}


void dataManagement::analyzeMonthlyFakePoliticalNews(article* fakeHead, article* trueHead) {
    // Track both fake and true political articles for each month
    int fakePolitical[13] = {0};
    int truePolitical[13] = {0};

    // Count fake political articles
    article* current = fakeHead;
    while (current != nullptr) {
        if (current->year == 2016 && isPolitical(current->category)) {
            fakePolitical[current->month]++;
        }
        current = current->next;
    }

    // Count true political articles
    current = trueHead;
    while (current != nullptr) {
        if (current->year == 2016 && isPolitical(current->category)) {
            truePolitical[current->month]++;
        }
        current = current->next;
    }

    // Array of month names for display (index 1..12)
    static const string MONTHS[13] = {
        "",
        "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October",
        "November", "December"
    };

    cout << "Percentage of Fake Political News Articles in 2016\n\n";

    // For each month, calculate the percentage of fake articles among total articles
    for (int m = 1; m <= 12; m++) {
        int totalPolitical = fakePolitical[m] + truePolitical[m];
        
        cout << setw(12) << left << MONTHS[m] << " | ";

        if (totalPolitical == 0) {
            cout << "0%" << endl;
        } else {
            double percentage = (static_cast<double>(fakePolitical[m]) / totalPolitical) * 100;
            
            // Build the bar string (one '*' per percent)
            int stars = static_cast<int>(percentage);
            for (int i = 0; i < stars; i++) {
                cout << "*";
            }
            
            // Print the percentage
            cout << " " << fixed << setprecision(0) << percentage << "%" << endl;
        }
    }
    
    cout << "\nNote: Each '*' represents 1% of fake political news articles." << endl << endl;
}

