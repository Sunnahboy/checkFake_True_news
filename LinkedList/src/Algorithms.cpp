<<<<<<< HEAD
// #include "LinkedList_Manipulation.hpp"
#include "header/LinkedList.hpp"

// Compare the dates of two articles
bool dataManagement::compareDates(article* a, article* b) {
    if (a->year != b->year) return a->year < b->year;
    if (a->month != b->month) return a->month < b->month;
    return a->day < b->day;
}

// Insertion Sort to sort articles by date
void dataManagement::insertionSortByDate() {
    if (!head || !head->next) return;  // If the list is empty or has one node, no sorting needed.

    article* sorted = nullptr;  // Start with an empty sorted list.
    article* current = head;    // Start from the head of the original list.

    while (current) {
        article* next = current->next;  // Save the next node.
        
        // Insert current node into the sorted portion of the list.
        if (!sorted || compareDates(current, sorted)) {
            current->next = sorted;
            sorted = current;
        } else {
            article* temp = sorted;
            while (temp->next && !compareDates(current, temp->next)) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;  // Move to the next node in the original list.
    }

    head = sorted;  // Update head to point to the sorted list.
=======
#include <iostream>
#include "../header/LinkedList.hpp"
using namespace std;

// Constructor
LinkedList::LinkedList() {
    head = nullptr;
}

// Destructor
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}


// --- HELPER FUNCTIONS FOR DATE COMPARISONS ---

// Returns true if the date in node 'a' is later than in node 'b'
bool dateGreater(Node* a, Node* b) {
    if (a->publicationYear != b->publicationYear)
        return a->publicationYear > b->publicationYear;
    if (a->publicationMonth != b->publicationMonth)
        return a->publicationMonth > b->publicationMonth;
    return a->publicationDay > b->publicationDay;
}

// Returns true if the date in node 'a' is earlier than in node 'b'
bool dateLess(Node* a, Node* b) {
    if (a->publicationYear != b->publicationYear)
        return a->publicationYear < b->publicationYear;
    if (a->publicationMonth != b->publicationMonth)
        return a->publicationMonth < b->publicationMonth;
    return a->publicationDay < b->publicationDay;
}

// --- END HELPER FUNCTIONS ---

// Search for an article by title
Node* LinkedList::searchByTitle(string& title) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->title == title) {
            return temp; // Found the article
        }
        temp = temp->next;
    }
    return nullptr; // Article not found
    delete temp;
}

// Sort articles by publication date using Bubble Sort
void LinkedList::sortArticles() {
    if (head == nullptr || head->next == nullptr) return; // List is empty or has one node

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        Node* prev = nullptr;

        while (current->next != nullptr) {
            // Compare the dates using the separate date parts
            if (dateGreater(current, current->next)) {
                // Swap nodes
                Node* nextNode = current->next;
                current->next = nextNode->next;
                nextNode->next = current;

                if (prev == nullptr) {
                    head = nextNode; // Update head if swapping the first node
                } else {
                    prev->next = nextNode;
                }

                prev = nextNode;
                swapped = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Helper function to convert string to lowercase for case-insensitive comparison
string toLowerCase(string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return result;
}


// Optimized Linear Search
void LinkedList::linearSearch(string& searchTerm, string& searchType) {
    Node* current = head;
    int matchCount = 0;
    string searchTermLower = toLowerCase(searchTerm);

    if (head == nullptr) {
        cout << "The list is empty\n";
        return;
    }

    cout << "\n=== Linear Search Results ===\n";

    while (current != nullptr) {
        string fieldToSearch;
        if (searchType == "category")
            fieldToSearch = toLowerCase(current->category);
        else if (searchType == "title")
            fieldToSearch = toLowerCase(current->title);
        else {
            cout << "Invalid search type\n";
            return;
        }

        if (fieldToSearch.find(searchTermLower) != string::npos) {
            cout << "\nMatch found:\n";
            cout << "Title: " << current->title << "\n";
            cout << "Category: " << current->category << "\n";
            cout << "Date: " << current->publicationYear << "-"
                 << (current->publicationMonth < 10 ? "0" : "") << current->publicationMonth << "-"
                 << (current->publicationDay < 10 ? "0" : "") << current->publicationDay << "\n";
            matchCount++;
        }

        current = current->next;
    }

    cout << "\nTotal matches found for Linear Search: " << matchCount << "\n";
}



// Binary Search for dates (searches by year)
// This function creates a temporary sorted linked list using the new date format.
void LinkedList::binarySearchByYear(string& targetYear) {
    // Convert targetYear string to integer
    int targetYr = stoi(targetYear);

    // First, create a sorted temporary linked list of nodes by date
    Node* sortedHead = nullptr;
    Node* current = head;
    
    // Copy nodes and insert them in sorted order based on their date
    while (current != nullptr) {
        // Create a new node with all date parts (year, month, day)
        Node* newNode = new Node(
            current->title, 
            current->content, 
            current->category, 
            current->publicationYear, 
            current->publicationMonth, 
            current->publicationDay
        );
        
        // Insert in sorted order (using dateLess helper)
        if (sortedHead == nullptr || dateLess(newNode, sortedHead)) {
            newNode->next = sortedHead;
            sortedHead = newNode;
        } else {
            Node* temp = sortedHead;
            while (temp->next != nullptr && dateLess(temp->next, newNode)) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        
        current = current->next;
    }
    
    // Perform search by year on the sorted list
    int matchCount = 0;
    cout << "\n=== Binary Search Results for Year " << targetYear << " ===\n";
    
    current = sortedHead;
    while (current != nullptr) {
        if (current->publicationYear == targetYr) {
            cout << "\nMatch found:\n";
            cout << "Title: " << current->title << "\n";
            cout << "Category: " << current->category << "\n";
            cout << "Date: " 
                 << current->publicationYear << "-"
                 << (current->publicationMonth < 10 ? "0" : "") << current->publicationMonth << "-"
                 << (current->publicationDay < 10 ? "0" : "") << current->publicationDay << "\n";
            matchCount++;
        }
        current = current->next;
    }
    
    cout << "\nTotal matches found for Binary Search: " << matchCount << "\n";
    
    // Clean up temporary sorted list
    while (sortedHead != nullptr) {
        Node* temp = sortedHead;
        sortedHead = sortedHead->next;
        delete temp;
    }
>>>>>>> 3b64d3a65cf0da24851784b9a3cd3a20ec39b2d6
}
