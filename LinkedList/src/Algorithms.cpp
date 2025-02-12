
#include "header/LinkedList.hpp"

// to be reviewd Search for an article by title
Node* LinkedList::searchByTitle(const string& title) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->title == title) {
            return temp; // Found the article
        }
        temp = temp->next;
    }
    return nullptr; // Article not found
}

// to be reviewed Sort articles by publication date (Bubble Sort)
void LinkedList::sortArticles() {
    if (head == nullptr || head->next == nullptr) return; // List is empty or has one node

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        Node* prev = nullptr;

        while (current->next != nullptr) {
            if (current->publicationDate > current->next->publicationDate) {
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

// Optimized Linear Search
void linearSearch(const string& searchTerm, const string& searchType) {
    Node* current = head;
    int matchCount = 0;
    string searchTermLower = toLowerCase(searchTerm);
                
    cout << "\n=== Linear Search Results ===\n";
                
    while (current != nullptr) {
        bool match = false;
        string fieldToSearch;
                    
        if (searchType == "category") {
            fieldToSearch = toLowerCase(current->category);
        } else if (searchType == "title") {
            fieldToSearch = toLowerCase(current->title);
        } else {
            cout << "Invalid search type\n";
            return;
        }
                    
        // Check if searchTerm is a substring of the field
        if (fieldToSearch.find(searchTermLower) != string::npos) {
            cout << "\nMatch found:\n";
            cout << "Title: " << current->title << "\n";
            cout << "Category: " << current->category << "\n";
                    cout << "Date: " << current->publicationDate << "\n";
                    matchCount++;
                }
                
                current = current->next;
    }
            
    cout << "\nTotal matches found: " << matchCount << "\n";
}


//Binary Search NOT WORKING!!! Fix it
// Binary Search for dates (searches by year)
void binarySearchByYear(const string& targetYear) {
    // First, create a sorted temporary linked list of nodes by year
    Node* sortedHead = nullptr;
    Node* current = head;
    
    // Copy nodes and insert them in sorted order by year
    while (current != nullptr) {
        string currentYear = current->publicationDate.substr(0, 4);
        Node* newNode = new Node(current->title, current->content, 
                            current->category, current->publicationDate);
        
        // Insert in sorted order
        if (sortedHead == nullptr || currentYear < sortedHead->publicationDate.substr(0, 4)) {
            newNode->next = sortedHead;
            sortedHead = newNode;
        } else {
            Node* temp = sortedHead;
            while (temp->next != nullptr && 
                temp->next->publicationDate.substr(0, 4) < currentYear) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        
        current = current->next;
    }
    
    // Perform binary search
    int matchCount = 0;
    cout << "\n=== Binary Search Results for Year " << targetYear << " ===\n";
    
    // Convert linked list to array of pointers for binary search
    int count = 0;
    current = sortedHead;
    while (current != nullptr) {
        if (current->publicationDate.substr(0, 4) == targetYear) {
            cout << "\nMatch found:\n";
            cout << "Title: " << current->title << "\n";
            cout << "Category: " << current->category << "\n";
            cout << "Date: " << current->publicationDate << "\n";
            matchCount++;
        }
        current = current->next;
    }
    
    cout << "\nTotal matches found: " << matchCount << "\n";
    
    // Clean up temporary sorted list
    while (sortedHead != nullptr) {
        Node* temp = sortedHead;
        sortedHead = sortedHead->next;
        delete temp;
    }
}