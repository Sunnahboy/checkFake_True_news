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
}
