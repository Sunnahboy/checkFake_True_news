#include <iostream>
#include <string>

class Node {
public:
    std::string key;  // Word
    int value;        // Frequency
    Node* next;       // Pointer to next node

    Node(std::string k) {
        key = k;
        value = 1;   // First occurrence
        next = nullptr;
    }
};].

class HashMap {
private:
    static const int SIZE = 10; // Table size
    Node* table[SIZE];          // Array of linked lists

    // Hash Function: Simple string hash
    int hashFunction(std::string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % SIZE; // Prime multiplier
        }
        return hash;
    }

public:
    HashMap() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr; // Initialize all buckets to null
        }
    }

    // Insert or update word frequency
    void insert(std::string key) {
        int index = hashFunction(key);
        Node* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value++;  // Increase count if word exists
                return;
            }
            temp = temp->next;
        }

        // If not found, insert new node at head (chaining)
        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Print HashMap contents
    void display() {
        std::cout << "\nHashMap Contents:\n";
        for (int i = 0; i < SIZE; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                std::cout << temp->key << ": " << temp->value << std::endl;
                temp = temp->next;
            }
        }
    }
};

int main() {
    HashMap wordMap;

    // Dummy word array
    std::string words[] = {"apple", "banana", "apple", "cherry", "banana",
                           "apple", "date", "cherry", "banana", "apple"};
    int wordCount = sizeof(words) / sizeof(words[0]);

    // Insert words into HashMap
    for (int i = 0; i < wordCount; i++) {
        wordMap.insert(words[i]);
    }

    // Display HashMap contents
    wordMap.display();

    return 0;
}