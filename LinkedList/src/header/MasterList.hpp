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
    LinkedListAlgo algo;

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
    
    void displayTopWords() {
        if (!head) {
            return;
        }
    
        cout << "Most frequently used words in government-related fake news:\n";
    
        WordNode* temp = head;
        WordNode* mostFrequent = nullptr;
    
        int countDisplayed = 0;
        const int minWordsToShow = 10; // Ensure at least 10 words are displayed
    
        while (countDisplayed < minWordsToShow) {
            temp = head;
            mostFrequent = nullptr;
    
            // Find the word with the highest frequency
            while (temp) {
                if (!mostFrequent || temp->freqPtr->count > mostFrequent->freqPtr->count) {
                    mostFrequent = temp;
                }
                temp = temp->nextWord;
                // cout << "Found highest Freq word." << endl;
            }
    
            // If no more words are found, break
            if (!mostFrequent) break;
    
            // Display the most frequent word
            cout << mostFrequent->word << " - " << mostFrequent->freqPtr->count << " times\n";
    
            countDisplayed++;
    
            // Mark this word as "used" by setting its frequency to -1 (so it's not picked again)
            mostFrequent->freqPtr->count = -1;
        }
    }
    
    
    
    
    
};
#endif