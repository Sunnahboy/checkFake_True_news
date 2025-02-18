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
    
    
};

// Day Node
struct DayNode {
int day;
int count;
DayNode* next;
DayNode(int d) : day(d), count(1), next(nullptr) {}
};

// HashMap for Day-Level Storage
class DayHashMap {
private:
static const int size = 31;  // Max 31 days
DayNode* table[size];

int hashFunction(int day) {
return day % size;
}

public:
DayHashMap() {
for (int i = 0; i < size; i++) table[i] = nullptr;
}

void insert(int day) {
int index = hashFunction(day);
DayNode* temp = table[index];

while (temp != nullptr) {
    if (temp->day == day) {
        temp->count++;
        return;
    }
    temp = temp->next;
}

DayNode* newNode = new DayNode(day);
newNode->next = table[index];
table[index] = newNode;
}

int get(int day) {
int index = hashFunction(day);
DayNode* temp = table[index];
while (temp != nullptr) {
    if (temp->day == day) return temp->count;
    temp = temp->next;
}
return 0;
}
};

// Month Node
struct MonthNode {
int month;
DayHashMap* dayMap;
MonthNode* next;
MonthNode(int m) : month(m), dayMap(new DayHashMap()), next(nullptr) {}
};

// HashMap for Month-Level Storage
class MonthHashMap {
private:
static const int size = 12; // 12 months
MonthNode* table[size];

int hashFunction(int month) {
return month % size;
}

public:
MonthHashMap() {
for (int i = 0; i < size; i++) table[i] = nullptr;
}

void insert(int month, int day) {
int index = hashFunction(month);
MonthNode* temp = table[index];

while (temp != nullptr) {
    if (temp->month == month) {
        temp->dayMap->insert(day);
        return;
    }
    temp = temp->next;
}

MonthNode* newNode = new MonthNode(month);
newNode->next = table[index];
table[index] = newNode;
newNode->dayMap->insert(day);
}

int get(int month, int day) {
int index = hashFunction(month);
MonthNode* temp = table[index];
while (temp != nullptr) {
    if (temp->month == month) return temp->dayMap->get(day);
    temp = temp->next;
}
return 0;
}
};

// Year Node
struct YearNode {
int year;
MonthHashMap* monthMap;
YearNode* next;
YearNode(int y) : year(y), monthMap(new MonthHashMap()), next(nullptr) {}
};

// HashMap for Year-Level Storage
class YearHashMap {
private:
static const int size = 100; // 100 years max
YearNode* table[size];

int hashFunction(int year) {
return year % size;
}

public:
YearHashMap() {
for (int i = 0; i < size; i++) table[i] = nullptr;
}

void insert(int year, int month, int day) {
int index = hashFunction(year);
YearNode* temp = table[index];

while (temp != nullptr) {
    if (temp->year == year) {
        temp->monthMap->insert(month, day);
        return;
    }
    temp = temp->next;
}

YearNode* newNode = new YearNode(year);
newNode->next = table[index];
table[index] = newNode;
newNode->monthMap->insert(month, day);
}

int get(int year, int month, int day) {
int index = hashFunction(year);
YearNode* temp = table[index];
while (temp != nullptr) {
    if (temp->year == year) {
        return temp->monthMap->get(month, day); // Correctly fetch count from MonthHashMap
    }
    temp = temp->next;
}
return 0; // Return 0 if no records found
}

};



#endif