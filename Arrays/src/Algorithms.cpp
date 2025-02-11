#include <iostream>
#include <limits>
#include "header/Arrays.hpp"

using namespace std;

// Helper function for Merge Sort
void Merge(int*& arr, int LEFT, int MID, int RIGHT, int*& temp) {
    int L = MID - LEFT + 1;
    int R = RIGHT - MID;

    // Creating two temporary arrays for sorting and two for getting the index
    int* leftArr = new int[L];
    int* rightArr = new int[R];
    int* leftindex = new int[L];
    int* rightindex = new int[R];

    // Fill temporary arrays
    for (int i = 0; i < L; i++) {
        leftArr[i] = arr[i + LEFT];
        leftindex[i] = temp[i + LEFT];
    }
    for (int j = 0; j < R; j++) {
        rightArr[j] = arr[MID + 1 + j];
        rightindex[j] = temp[MID + 1 + j];
    }

    // Merge back into the main array
    int i = 0, j = 0, k = LEFT;
    while (i < L && j < R) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            temp[k]=leftindex[i];;
            i++;
        } else {
            arr[k] = rightArr[j];
            temp[k]=rightindex[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < L) {
        arr[k] = leftArr[i];
        temp[k]=leftindex[i];
        i++;
        k++;
    }
    while (j < R) {
        arr[k] = rightArr[j];
        temp[k]=rightindex[j];
        j++;
        k++;
    }

    // Clean up temporary arrays
    delete[] leftArr;
    delete[] rightArr;
    delete[] leftindex;
    delete[] rightindex;
}

// Merge Sort Implementation
void ArraysAlgo::MergeSort(int*& arr, int left, int right,int*& temp) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid, temp);
    MergeSort(arr, mid + 1, right, temp);
    Merge(arr, left, mid, right, temp);
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

// Binary Search by Year
void ArraysAlgo::binarysearchYear(int year) const {
    int left = 0, right = size - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2; //this should be (left+right)/2

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

            //the above portion of code can be ignored if we sort the complete date including the year
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


//Insertion Sort
void ArraysAlgo::InsertionSort(string** arr, int size) {
    for (int i = 1; i < size; i++) {
        string temp[6];
        // Copy the current row to a temporary array for comparison
        for (int j = 0; j < 6; j++) {
            temp[j] = arr[i][j];
        }
           
        int j = i - 1;
            
        // Compare the current row’s date (year, month, day) with previous rows
        while (j >= 0) {
            int year1 = stoi(arr[j][3]);
            int month1 = stoi(arr[j][4]);
            int day1 = stoi(arr[j][5]);
            int year2 = stoi(temp[3]);
            int month2 = stoi(temp[4]);
            int day2 = stoi(temp[5]);

            // Compare dates (year, month, day)
            if (year1 > year2 || (year1 == year2 && (month1 > month2 || (month1 == month2 && day1 > day2)))) {
                // If the previous row’s date is later, shift it right
                for (int k = 0; k < 6; k++) {
                    arr[j + 1][k] = arr[j][k];
                }
            } else {
                break;
            }
            j--;
        }
            
        // Place the current row in its correct position
        for (int k = 0; k < 6; k++) {
            arr[j + 1][k] = temp[k];
        }
    }
}




//the Parameter should be flexible any field can be compared
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

//No need for this code delete it

// Filling Articles Array
// void ArraysAlgo::fillingarrays() {
//     size = 5; // Set the size of articles
//     articles = new NewsArticle[size]; // Allocate memory for articles

//     for (int i = 0; i < size; i++) {
//         articles[i] = {
//             "Title " + to_string(i + 1),
//             "Content " + to_string(i + 1),
//             "Category " + to_string(i % 3 + 1),
//             2025,
//             1,
//             i + 1
//         };
//     }
// }
