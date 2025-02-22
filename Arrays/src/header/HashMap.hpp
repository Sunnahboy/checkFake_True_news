#ifndef HashMap_HPP
#define HashMap_HPP
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

class HashMap
{
private:
    static const int size=1000; //size of the array of the HashMap
    Node * table[size];

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

    pair<string*, int*> getKeysAndFrequencies() {
        int count = getCount();
        if (count == 0) return {nullptr, nullptr};
    
        string* keys = new string[count];
        int* freqs = new int[count];
    
        int index = 0;
        for (int i = 0; i < size; i++) {
            Node* temp = table[i];
            while (temp != nullptr) {
                keys[index] = temp->key;
                freqs[index] = temp->value; // Directly store frequency
                index++;
                temp = temp->next;
            }
        }
        return {keys, freqs};
    }
    
};

#endif