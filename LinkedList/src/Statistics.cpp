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

// Function to calculate the percentage of political articles from 2016 that are fake.
// It takes two linked lists: one for true news and one for fake news.
void dataManagement::calculatePoliticalFakePercentage(article* trueHead, article* fakeHead) {
    int totalPolitical = 0;
    int fakePolitical = 0;
    
    // Process the true news list.
    article* current = trueHead;
    while (current != nullptr) {
        if (current->year == 2016 && isPolitical(current->category)) {
            totalPolitical++;
            cout << "Debug here..." <<endl;
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
    cout << "Total fake political articles from 2016: " << fakePolitical << endl;
}


// This function calculates, for each month in 2016, 
// the percentage of fake political articles (among the total fake political articles in 2016).
void dataManagement::analyzeMonthlyFakePoliticalNews(article* fakeHead) {
    // Track fake political articles for each month.
    int monthlyCount[13] = {0};  
    int totalFakePolitical2016 = 0;  
    

    // Traverse the fake news linked list.
    article* current = fakeHead;
    while (current != nullptr) {
        // Check if the article is from 2016 and is political.
        if (current->year == 2016 && isPolitical(current->category)) {
            monthlyCount[current->month]++;
            totalFakePolitical2016++;
        }

        current = current->next;
    }

    // If we found no fake political articles in 2016, report and exit.
    if (totalFakePolitical2016 == 0) {
        cout << "No fake political articles found in 2016.\n";
        return;
    }

    // Array of month names for display (index 1..12).
    static const string MONTHS[13] = {
        "",
        "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October",
        "November", "December"
    };

    cout << "Percentage of Fake Political News Articles in 2016\n\n";

    // For each month, calculate the percentage of totalFakePolitical2016.
    for (int m = 1; m <= 12; m++) {
        double percentage = (monthlyCount[m] * 100.0) / totalFakePolitical2016;
        
        // Build the bar string (one '*' per percent, integer part only).
        string bar;
        int starCount = static_cast<int>(percentage);
        for (int i = 0; i < starCount; i++) {
            bar.push_back('*');
        }
        
        // Print the output in a single, well-aligned line.
        cout << setw(12) << left << MONTHS[m] << " | " << bar;
        // Print a space only if there are asterisks.
        if (!bar.empty())
            cout << " ";
            
        // Print the percentage immediately following the asterisks (or the bar if empty).
        cout << fixed << setprecision(0) << percentage << "%" << endl;
    }
    cout << "\nNote: Each '*' represents 1% of fake political news articles.\n";
}

