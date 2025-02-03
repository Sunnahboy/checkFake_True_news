#include <iostream>
#include <iomanip>


using namespace std;

//Q2. Calculate Fake News % in 2016
void calculateFakeNewsPercentage(string** trueNews, int trueSize, string** fakeNews, int fakeSize) {
    int truePolitical2016 = 0;
    int fakePolitical2016 = 0;

    // Loop through true news stored in 2D array
    for (int i = 0; i < trueSize; i++) {
        if (stoi(trueNews[i][3]) > 2016) break;  // Convert year from string to int
        if (stoi(trueNews[i][3]) == 2016 && trueNews[i][2] == "politicsNews") {
            truePolitical2016++;
        }
    }

    // Loop through fake news stored in 2D array
    for (int i = 0; i < fakeSize; i++) {
        if (stoi(fakeNews[i][3]) > 2016) break;  // Convert year from string to int
        if (stoi(fakeNews[i][3]) == 2016 && fakeNews[i][2] == "politicsNews") {
            fakePolitical2016++;
        }
    }

    int totalPolitical2016 = truePolitical2016 + fakePolitical2016;

    if (totalPolitical2016 == 0) {
        cout << "No political news articles found in 2016!" << endl;
        return;
    }

    double percentage = (static_cast<double>(fakePolitical2016) / totalPolitical2016) * 100;

    cout << "Total Political News Articles in 2016: " << totalPolitical2016 << endl;
    cout << "Fake Political News Articles in 2016: " << fakePolitical2016 << endl;
    cout << "Percentage of Fake Political News in 2016: " << fixed << setprecision(2) << percentage << "%" << endl;
}


//Q7 Percentage of Fake News by Month. Formatted
void displayFakeNewsPercentageByMonth(string** trueNews, int trueSize, string** fakeNews, int fakeSize) {
    int truePolitical2016[12] = {0};  
    int fakePolitical2016[12] = {0};  

    string months[] = { "January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December" };

    // Loop through true news
    for (int i = 0; i < trueSize; i++) {
        int year = stoi(trueNews[i][3]);  
        if (year > 2016) break;  
        if (year == 2016 && trueNews[i][2] == "politicsNews") {
            int month = stoi(trueNews[i][4]);  
            if (month >= 1 && month <= 12) {
                truePolitical2016[month - 1]++;
            }
        }
    }

    // Loop through fake news
    for (int i = 0; i < fakeSize; i++) {
        int year = stoi(fakeNews[i][3]);
        if (year > 2016) break;
        if (year == 2016 && fakeNews[i][2] == "politicsNews") {
            int month = stoi(fakeNews[i][4]);
            if (month >= 1 && month <= 12) {
                fakePolitical2016[month - 1]++;
            }
        }
    }

    // Display formatted results
    cout << "Percentage of Fake Political News Articles in 2016\n\n";

    for (int i = 0; i < 12; i++) {
        int totalPolitical = truePolitical2016[i] + fakePolitical2016[i];

        cout << left << setw(10) << months[i] << " | ";

        if (totalPolitical == 0) {
            cout << "0%\n";
        } else {
            double percentage = (static_cast<double>(fakePolitical2016[i]) / totalPolitical) * 100;
            int stars = static_cast<int>(percentage);  

            for (int j = 0; j < stars; j++) {
                cout << "*";  
            }

            cout << " " << fixed << setprecision(0) << percentage << "%\n";
        }
    }

    cout << "\nNote: Each '*' represents 1% of fake political news articles.\n";
}
