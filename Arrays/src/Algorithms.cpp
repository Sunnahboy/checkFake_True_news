#include <iostream>
#include <limits>
#include "header/Arrays.hpp"

using namespace std;

// Helper function for Merge Sort
void Merge(int*& arr, int LEFT, int MID, int RIGHT) {
    int L = MID - LEFT + 1;
    int R = RIGHT - MID;

    // Creating two temporary arrays for sorting
    int* leftArr = new int[L];
    int* rightArr = new int[R];

    // Fill temporary arrays
    for (int i = 0; i < L; i++) {
        leftArr[i] = arr[i + LEFT];
    }
    for (int j = 0; j < R; j++) {
        rightArr[j] = arr[MID + 1 + j];
    }

    // Merge back into the main array
    int i = 0, j = 0, k = LEFT;
    while (i < L && j < R) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy remaining elements
    while (i < L) {
        arr[k++] = leftArr[i++];
    }
    while (j < R) {
        arr[k++] = rightArr[j++];
    }

    // Clean up temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}

// Merge Sort Implementation
void ArraysAlgo::MergeSort(int*& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}

// Custom String Comparison Function
bool customStringCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false; // Mismatch found
        }
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0'); // Ensure both strings end at the same position
}

// Bubble Sort Implementation
void ArraysAlgo::BubbleSort() {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (articles[j].publicationYear > articles[j + 1].publicationYear) {
                swap(articles[j], articles[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // If no swaps, array is sorted
    }
}

// Display All Articles
void ArraysAlgo::displayarrays() {
    for (int i = 0; i < size; i++) {
        cout << "Title: " << articles[i].title << endl;
        cout << "Content: " << articles[i].content << endl;
        cout << "Category: " << articles[i].category << endl;
        cout << "Publication Date: "
             << articles[i].publicationYear << "-"
             << articles[i].publicationMonth << "-"
             << articles[i].publicationDay << endl;
        cout << "---------------------------------" << endl;
    }
}

// Binary Search by Year
void ArraysAlgo::binarysearchYear(int year) const {
    int left = 0, right = size - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (articles[mid].publicationYear == year) {
            // Match found; display article
            cout << "Match Found:\n";
            cout << "Title: " << articles[mid].title << endl;
            found = true;

            // Check for duplicates in both directions
            int temp = mid - 1;
            while (temp >= 0 && articles[temp].publicationYear == year) {
                cout << "Title: " << articles[temp].title << endl;
                temp--;
            }

            temp = mid + 1;
            while (temp < size && articles[temp].publicationYear == year) {
                cout << "Title: " << articles[temp].title << endl;
                temp++;
            }
            break;
        }

        if (articles[mid].publicationYear < year) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "No articles found for the year: " << year << endl;
    }
}

// Linear Search by Category
// void LinearsearchByCategory(const char* category) {
//     bool found = false;
//     ArraysAlgo algo;
//     for (int i = 0; i < algo.getsize(); i++) {
//         if (customStringCompare(articles[i].category.c_str(), category)) {
//             // Match found; display the article
//             cout << "Match Found:\n";
//             cout << "Title: " << articles[i].title << endl;
//             found = true;

//             // Perform transposition to move the article closer to the start
//             if (i > 0) {
//                 NewsArticle temp = articles[i];
//                 articles[i] = articles[i - 1];
//                 articles[i - 1] = temp;
//             }
//         }
//     }

//     if (!found) {
//         cout << "No articles found in category: " << category << endl;
//     }
// }

// Filling Articles Array
void ArraysAlgo::fillingarrays() {
    size = 5; // Set the size of articles
    articles = new NewsArticle[size]; // Allocate memory for articles

    for (int i = 0; i < size; i++) {
        articles[i] = {
            "Title " + to_string(i + 1),
            "Content " + to_string(i + 1),
            "Category " + to_string(i % 3 + 1),
            2025,
            1,
            i + 1
        };
    }
}
