#include <iostream>
#include <iomanip>
#include "NewsArticle.h"

using namespace std;

void calculateFakeNewsPercentage(NewsArticle* trueNews, int trueSize, NewsArticle* fakeNews, int fakeSize) {
    int truePolitical2016 = 0;
    int fakePolitical2016 = 0;

    // Loop through true news
    for (int i = 0; i < trueSize; i++) {
        if (trueNews[i].publicationYear > 2016) break;
        if (trueNews[i].publicationYear == 2016 && trueNews[i].category == "politics") {
            truePolitical2016++;
        }
    }

    // Loop through fake news
    for (int i = 0; i < fakeSize; i++) {
        if (fakeNews[i].publicationYear > 2016) break;
        if (fakeNews[i].publicationYear == 2016 && fakeNews[i].category == "politics") {
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

