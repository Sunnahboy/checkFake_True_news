// #include "LinkedList_Manipulation.hpp"
#include "header/LinkedList.hpp"
#include "header/LinkedList_Manipulation.hpp"

// Compare the dates of two articles
bool LinkedListAlgo::compareDates(article* a, article* b) {
    if (a->year != b->year) return a->year < b->year;
    if (a->month != b->month) return a->month < b->month;
    return a->day < b->day;
}

bool LinkedListAlgo::compareSubject(article* a, article* b) {
    return a->category < b->category;
}



template <typename Comparator>
article* LinkedListAlgo::mergeSortedLists(article* a, article* b, Comparator comp) {
    article* head = nullptr;
    article* tail = nullptr;

    auto appendNode = [&](article*& node) {
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        node = node->next;
    };

    while (a && b) {
        if ((this->*comp)(a, b)) {
            appendNode(a);
        } else {
            appendNode(b);
        }
    }

    tail->next = (a ? a : b);
    return head;
}

// Bottom-up merge sort with comparator
template <typename Comparator>
article* LinkedListAlgo::bottomUpMergeSort(article* head, Comparator comp) {
    if (!head || !head->next) return head;

    int length = 0;
    for (article* node = head; node; node = node->next) length++;

    string empty = "";
    article dummy(empty, empty, empty, 0, 0, 0); // Dummy node to simplify merging
    dummy.next = head;

    for (int size = 1; size < length; size *= 2) {
        article* current = dummy.next;
        article* tail = &dummy;

        while (current) {
            article* left = current;
            article* right = nullptr;
            article* nextSegment = nullptr;

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
                break;
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
            
            tail->next = mergeSortedLists(left, right, comp);

            while (tail->next) tail = tail->next;

            current = nextSegment;
        }
        head = dummy.next;
    }

    return head;
}


// Template-based insertion sort
template <typename Comparator>
article* LinkedListAlgo::insertionSort(article* head, Comparator comp) {
    if (!head || !head->next) return head;  // If the list is empty or has one node, no sorting needed.

    article* sorted = nullptr;  // Start with an empty sorted list.
    article* current = head;    // Start from the head of the original list.

    while (current) {
        article* next = current->next;  // Save the next node.
        
        // Insert current node into the sorted portion of the list.
        if (!sorted || (this->*comp)(current, sorted)) {
            current->next = sorted;
            sorted = current;
        } else {
            article* temp = sorted;
            while (temp->next && !(this->*comp)(current, temp->next)) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;  // Move to the next node in the original list.
    }

    return sorted;  // Return the sorted list head.
}

// Template-based QuickSort
template <typename Comparator>
article* LinkedListAlgo::quickSort(article* head, Comparator comp) {
    if (!head || !head->next) return head;  // Base case: empty list or single node.

    // Partition the list
    article* pivot = head;
    article* lesserHead = nullptr, * lesserTail = nullptr;
    article* greaterHead = nullptr, * greaterTail = nullptr;
    article* equalHead = nullptr, * equalTail = nullptr;

    article* current = head;
    while (current) {
        article* next = current->next;
        current->next = nullptr;  // Disconnect the node.

        if ((this->*comp)(current, pivot)) {  // Lesser
            if (!lesserHead) lesserHead = lesserTail = current;
            else {
                lesserTail->next = current;
                lesserTail = current;
            }
        } else if ((this->*comp)(pivot, current)) {  // Greater
            if (!greaterHead) greaterHead = greaterTail = current;
            else {
                greaterTail->next = current;
                greaterTail = current;
            }
        } else {  // Equal
            if (!equalHead) equalHead = equalTail = current;
            else {
                equalTail->next = current;
                equalTail = current;
            }
        }
        current = next;
    }

    // Recursively sort lesser and greater lists
    lesserHead = quickSort(lesserHead, comp);
    greaterHead = quickSort(greaterHead, comp);

    // Combine lesser, equal, and greater parts
    article* sortedHead = (lesserHead) ? lesserHead : equalHead;
    article* sortedTail = lesserTail ? lesserTail : equalTail;

    if (sortedTail) sortedTail->next = equalHead;
    if (equalTail) equalTail->next = greaterHead;

    return sortedHead;
}


template <typename Comparator>
article* LinkedListAlgo::bubbleSort(article* head, Comparator comp) {
    // If the list is empty or has one node, it is already sorted.
    if (!head || !head->next) return head;
    
    // Create a dummy node to simplify pointer manipulation.
    string empty = "";
    article dummy(empty, empty, empty, 0, 0, 0);
    dummy.next = head;
    
    bool swapped;
    do {
        swapped = false;
        // Start each pass from the beginning using the dummy node.
        article* prev = &dummy;
        article* curr = dummy.next;
        
        while (curr && curr->next) {
            // If the next node should come before the current node,
            // swap them by rearranging pointers.
            if ((this->*comp)(curr->next, curr)) {
                // Perform the swap of adjacent nodes.
                article* temp = curr->next;
                curr->next = temp->next;
                temp->next = curr;
                prev->next = temp;
                
                // Mark that we performed a swap.
                swapped = true;
                
                // Update the 'prev' pointer to the new node that is now before 'curr'.
                prev = temp;
            } else {
                // Move forward if no swap is needed.
                prev = curr;
                curr = curr->next;
            }
        }
    } while (swapped);
    
    return dummy.next;
}

string LinkedListAlgo::getFieldForlinearSearch(article * node, int index){
    if(!node) return " ";
    if(index==0) return node -> title;
    if(index==1) return node -> content;
    if(index==2) return node -> category;
    if(index==3) return to_string(node -> year);
    if(index==4) return to_string(node -> month);
    if(index==5) return to_string(node -> day);
    else{
        return "";
    }
}

// void LinkedListAlgo::linearSearch2(article * head ,int index, string value){
//     article *current= head;
//     bool found=false;
//     while(current != nullptr){
//         string ListValue=getFieldForlinearSearch(current, index);
//         if(ListValue == value){
//             Data.addArticlefromEnd(current->title, current->content, current->category, current->day, current->month, current->year); 
//             found=true;
//         }
//         else if(ListValue.find(value)!= string ::npos){
//             Data.addArticlefromEnd(current->title, current->content, current->category, current->day, current->month, current->year); 
//             found=true;
//         }
//         current=current -> next;
//     }
//     if(!found) cout << "value: " << value<< " doesn't exist";
//     else{
//         article* temp=head;
//         int count=0;
//         while (temp != nullptr) {
//             cout << "\n--- Article " << count + 1 << " ---\n";
//             cout << "Title: " << temp->title << "\n";
//             // cout << "Content: " << temp->content << "\n";
//             cout << "Category: " << temp->category << "\n";
//             cout << "Date: " 
//                  << temp->year << "-" 
//                  << (temp->month < 10 ? "0" : "") << temp->month << "-" 
//                  << (temp->day < 10 ? "0" : "") << temp->day << "\n";
//             temp = temp->next;
//             count++;
//         }
//         cout << "Full count: " << count;
//     }
// }


template <typename Comparator, typename T>
article* LinkedListAlgo::linearSearch(article* head, const T& target, Comparator comp, int* position) {
    if (!head) {
        cerr << "Error: The article list is empty.\n";
        if (position) *position = -1;
        return nullptr;
    }

    article* current = head;
    article* matches = nullptr;  // First match
    article* lastMatch = nullptr;  // Last match found
    int pos = 0;
    bool foundFirst = false;

    while (current) {
        //if ((this->*comp)(current, target)) {
        //    if (!foundFirst) {
        //        matches = current;
        //        if (position) *position = pos;
        //        foundFirst = true;
        //        lastMatch = current;
        //    } else {
        //        lastMatch->next = current;
        //        lastMatch = current;
        //    }
        //}
        if (comp(current, target)) { 
            if (!foundFirst) {
                matches = current;
                if (position) *position = pos;
                foundFirst = true;
                lastMatch = current;
            } else {
                lastMatch->next = current;
                lastMatch = current;
            }
        }
        
        current = current->next;
        pos++;
    }
    
    if (lastMatch) {
        lastMatch->next = nullptr;  // Terminate the list of matches
    }

    if (!matches) {
        if (position) *position = -1;
    }

    return matches;
}

//  template <typename Comparator, typename T>
//  article* LinkedListAlgo::recursiveSearch(article* current, const T& target, Comparator comp, int* position, int pos) {
//     //cout<<"Recursive Search" << pos <<endl;
//     // Base case: if the current node is null, return nullptr (no match found)
    
    
//     if (!current) {
//         if (position) {
//             *position = -1;}
//             cout << "Reached end of list. No match found." << endl;
//         return nullptr;    
//     }

//     cout << "Checking node at position " << pos << " with address " << current <<endl;
    
//     // Check if the current node matches the target
//     if ((this->*comp)(current, target)) {
//         if (position) *position = pos;
//         cout << "Match found at position: " << pos << endl;
//         return current; // Found the first match, return it 
//     }

//     // Recursive call to the next node
//     return recursiveSearch(current->next, target, comp, position, pos + 1);
//  }

/*template <typename Comparator, typename T>
article* LinkedListAlgo::recursiveSearch(article* current, const T& target, Comparator comp, int* position, int pos) {
    const int batchSize = 2;
    int count = 0;
    
    // If we've reached the end of the list during the batch, no match was found.
    if (!current) {
        if (position) {
            *position = -1;
        }
        cout << "Reached end of list. No match found." << endl;
        return nullptr;
    }
    
    // Process up to batchSize nodes iteratively
    while (current && count < batchSize) {
        // cout << "Checking node at position " << pos << " with address " << current << endl;
        // cout <<"Starting to check nodes" << endl;
       //if ((this->*comp)(current, target)) {
       //    if (position) {
       //        *position = pos;
       //    }
       //    cout << "Match found at position: " << pos << endl;
       //    return current;  // Return the first matching node found in this batch
       //}
       if (comp(current, target)) {  
        if (position) {
            *position = pos;
        }
        cout << "Match found at position: " << pos << " with year: " << current->year << endl;
        return current;
    }


        current = current->next;
        pos++;
        count++;
    }
    
    // Process the next batch recursively.
    return recursiveSearch(current, target, comp, position, pos);
}*/

template <typename Comparator, typename T>
article* LinkedListAlgo::iterativeSearch(article* current, const T& target, Comparator comp, int* position, int pos) {
    if (!current) {
        if (position) *position = -1;
        return nullptr;
    }

    article* matchedHead = nullptr;
    article* matchedTail = nullptr;
    bool foundFirst = false;

    while (current) {
        if (comp(current, target)) {
            article* newNode = new article(*current);  
            newNode->next = nullptr;

            if (!foundFirst) {
                matchedHead = newNode;
                if (position) *position = pos;
                foundFirst = true;
            } else {
                matchedTail->next = newNode;
            }

            matchedTail = newNode;
        }
        
        current = current->next;
        pos++;
    }
    
    return matchedHead;
}



template <typename Comparator, typename T>
article* LinkedListAlgo::search(article* head, const T& target, Comparator comp, int* position) {
    // Start the recursive search from the head of the list
    return iterativeSearch(head, target, comp, position, 0);
}


// Case-Insensitive String Matching (Manual, No STL)
bool LinkedListAlgo::caseInsensitiveCompare(const string& str1, const string& str2) {
    int i = 0;
    while (str1[i] && str2[i]) {
        char c1 = (str1[i] >= 'A' && str1[i] <= 'Z') ? str1[i] + 32 : str1[i]; // Convert to lowercase
        char c2 = (str2[i] >= 'A' && str2[i] <= 'Z') ? str2[i] + 32 : str2[i];

        if (c1 != c2) return false;
        i++;
    }
    return str1[i] == str2[i]; // Ensure full match
}

//SEARCHING comparators
// Comparator: Search by Year
bool LinkedListAlgo::compareByYear(article* a, int targetYear) {
    if (a == nullptr) return false; 
    return a->year == targetYear;
}
// Comparator: Search by Month
bool LinkedListAlgo::compareByMonth(article* a, int targetMonth) {
    return a->month == targetMonth;
}

// Comparator: Search by Category (Case-Insensitive)
bool LinkedListAlgo::compareByCategory(article* a, const string& target) {
   return caseInsensitiveCompare(a->category, target);
}


// Comparator: Search for a Matching Word in the Title (Case-Insensitive, No STL)
bool LinkedListAlgo::compareByTitleKeyword(article* a, const string& keyword) {
    int titleLen = a->title.length();
    int keyLen = keyword.length();

    if (keyLen > titleLen) return false;

    for (int i = 0; i <= titleLen - keyLen; i++) {
        int j = 0;
        while (j < keyLen) {
            char c1 = (a->title[i + j] >= 'A' && a->title[i + j] <= 'Z') ? a->title[i + j] + 32 : a->title[i + j];
            char c2 = (keyword[j] >= 'A' && keyword[j] <= 'Z') ? keyword[j] + 32 : keyword[j];

            if (c1 != c2) break;
            j++;
        }
        if (j == keyLen) return true; // Found keyword in title
    }
    return false;
}
