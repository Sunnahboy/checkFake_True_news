#ifndef llhashmap_HPP
#define llhashmap_HPP
#include <iostream>
using namespace std;
struct Node
{
    string key;
    int value;
    Node * next;
    Node(string keyValue){
        key=keyValue;
        value=1;
        next=nullptr;
        //this insert from the front
    }
};

struct FreqTextWords{
    string word;
    int freq;
    FreqTextWords* next;
    FreqTextWords(string w){
        word=w;
        freq=1;
        next=nullptr;
    }
};

class HashMap
{
private:
    static const int size=1000; //size of the array of the HashMap
    Node * table[size];
    FreqTextWords* TokenNode=nullptr;

    int hashFunction(string key){
        int hash=0;
        for(char c :key){
            hash=(hash * 131 + c) % size; //hashing function to return the index from 0 999
        }
        return hash;
    }

public:
    HashMap() { // Missing constructor
        for(int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }
    void insert(string newkey){
        int index= hashFunction(newkey);
        Node* temp= table[index];

        while(temp != nullptr){
            if(temp -> key == newkey){
                temp -> value ++;
                return;
            }
            temp= temp -> next;
        }
        Node * newNode=new Node(newkey);
        newNode -> next=table[index];
        table[index]=newNode;
    }

    int getCount(){
        int count=0;
        for(int i=0; i <size; i++){
            Node *temp=table[i];
            while(temp != nullptr){
                count++;
                temp=temp -> next;
            }
        }
        return count;
    }

    FreqTextWords* getKeysAndFrequencies() {
        int count = getCount();
        if (count == 0) return nullptr; // No elements, return null
    
        FreqTextWords* FreqOfWord = nullptr;  // Head of linked list
        FreqTextWords* tail = nullptr;  // Tail for efficient insertion
    
        for (int i = 0; i < size; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                // Create a new node for FreqTextWords
                FreqTextWords* newNode = new FreqTextWords(temp->key);
                newNode->freq = temp->value; // Store frequency
    
                // Insert at the end of the list
                if (!FreqOfWord) {
                    FreqOfWord = newNode; // First node becomes head
                    tail = newNode; // Tail points to the first node
                } else {
                    tail->next = newNode; // Append to the list
                    tail = newNode; // Move tail forward
                }
    
                temp = temp->next;
            }
        }
        return FreqOfWord; // Return the head of the linked list
    }
    
    
    
    FreqTextWords* partition(FreqTextWords* low, FreqTextWords* high) {
        int pivot = high->freq; // Use last element as pivot
        FreqTextWords* i = low; // Pointer for greater elements
        
        for (FreqTextWords* j = low; j != high; j = j->next) {
            if (j->freq >= pivot) { // Sort in descending order
                swap(i->word, j->word);
                swap(i->freq, j->freq);
                i = i->next;
            }
        }
        swap(i->word, high->word);
        swap(i->freq, high->freq);
        return i;
    }
    
    void quickSort(FreqTextWords* low, FreqTextWords* high) {
        if (low != nullptr && high != nullptr && low != high && low != high->next) {
            FreqTextWords* p = partition(low, high);
            FreqTextWords* prevNode = low;
            while (prevNode && prevNode->next != p) {
                prevNode = prevNode->next;
            }
            quickSort(low, prevNode);
            quickSort(p->next, high); 
        }
    }
    
    void sortAndPrintTop10(FreqTextWords* head) {
        if (!head) return;
        
        FreqTextWords* tail = head;
        while (tail->next) tail = tail->next; // Find last node
        
        quickSort(head, tail);
        
        cout << "\nTop 10 Most Frequent Words:\n";
        FreqTextWords* temp = head;
        int count = 0;
        while (temp && count < 10) {
            cout << temp->word << " - " << temp->freq << " times\n";
            temp = temp->next;
            count++;
        }
    }
    
};

#endif