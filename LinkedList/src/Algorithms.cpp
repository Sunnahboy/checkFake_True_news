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


// Merges two sorted linked lists efficiently
Node* LinkedList::mergeSortedLists(Node* a, Node* b) {
    Node* head = nullptr;
    Node* tail = nullptr;

    auto appendNode = [&](Node*& node) {
        if (!head) {
            head = tail = node;
            //cout << "Appending node: " << node->title << endl; 
        } else {
            tail->next = node;
            tail = node;
            //cout << "Appending node: " << node->title << endl;
        }
        node = node->next;
    };

    while (a && b) {
        if (a->publicationYear < b->publicationYear || 
            (a->publicationYear == b->publicationYear && (a->publicationMonth < b->publicationMonth || 
            (a->publicationMonth == b->publicationMonth && a->publicationDay <= b->publicationDay)))) {
            appendNode(a);
        } else {
            appendNode(b);
            
        }
    }

    tail->next = (a ? a : b);
    return head;
}

// Bottom-up merge sort implementation
Node* LinkedList::bottomUpMergeSort(Node* head) {
    if (!head || !head->next) return head;

    int length = 0;
    for (Node* node = head; node; node = node->next) length++;

    Node dummy("", "", "", 0, 0, 0); // Dummy node to simplify merging
    dummy.next = head;

    for (int size = 1; size < length; size *= 2) {
        Node* current = dummy.next;
        Node* tail = &dummy;

        while (current) {
            Node* left = current;
            Node* right = nullptr;
            Node* nextSegment = nullptr;

            int count = 1;
            while (count < size && current->next) {
                current = current->next;
                count++;
            }

            if (current->next) {
                right = current->next;
                current->next = nullptr;
                current = right;
            } else {
                break; // Stop if we've reached the end
            }

            count = 1;
            while (count < size && current->next) {
                current = current->next;
                count++;
            }

            if (current->next) {
                nextSegment = current->next;
                current->next = nullptr;
            }
            //cout << "Merging segments..." << endl; // Debugging line
            tail->next = mergeSortedLists(left, right);

            while (tail->next) tail = tail->next;

            current = nextSegment;
        }
        head = dummy.next;
    }

    return head;
}


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
}
