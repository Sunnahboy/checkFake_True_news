#ifndef MasterList_HPP
#define MasterList_HPP
#include <iostream>
using namespace std;

struct FrequencyNode {
    int count;
    FrequencyNode* nextFreq; // For future scaling if needed

    FrequencyNode() {
        count = 1;
        nextFreq = nullptr;
    }
};

struct WordNode {
    string word;
    int index;     
    WordNode* nextWord;  
    WordNode* prevWord;  
    FrequencyNode* freqPtr; 

    WordNode(string w) {
        word = w;
        nextWord = nullptr;
        freqPtr = new FrequencyNode(); // Create frequency node initially with count = 1
    }
};

// Word frequency list using a two-layered linked list
class MasterList{
private:
    WordNode* head;
    WordNode* tail;

public:
    MasterList() {
        head = nullptr;
        tail = nullptr;
    }

    // Insert a new word or update frequency
    void insertOrUpdate(string word) {
        WordNode* temp = head;

        // Check if word already exists in the main list
        while (temp) {
            if (temp->word == word) {
                temp->freqPtr->count++;
                return;
            }
            temp = temp->nextWord;
        }

        // If word not found, create a new node
        WordNode* newNode = new WordNode(word);
        
        // Add to main linked list
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->nextWord = newNode;
            newNode->prevWord = tail;
            tail = newNode;
        }
    }
    // Display words and their frequencies
    void displayWords() {
        WordNode* temp = head;
        cout << "Words and their Frequencies:";
        int i=0;
        while (temp) {
            cout << temp->word << " - " << temp->freqPtr->count << " times\n";
            temp = temp->nextWord;
            i++;
            if(i==20)break;
        }
    }
};
#endif