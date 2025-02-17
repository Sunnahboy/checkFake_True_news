#ifndef LinkedList_Manipulation
#define LinkedList_Manipulation
#include <iostream>
#include "LinkedList.hpp"
#include <string>

class LinkedListAlgo{
    private:
        dataManagement Data;
        article * getMiddle(article* start, article* end){
            if(!start)return nullptr;

            article * slow= start;
            article* fast=start ->next;

            while(fast!=nullptr && fast -> next != nullptr){
                slow=slow->next;
                fast =fast->next->next;
            }
            return slow;
        }
        string getField(article * node, int index){
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
    public:

        LinkedListAlgo(std::string name = "DATA") : Data(name) {}

        void linearSearch(article * head ,int index, string value){
            article *current= head;
            bool found=false;
            while(current != nullptr){
                string ListValue=getField(current, index);
                if(ListValue == value){
                    Data.addArticlefromEnd(current->title, current->content, current->category, current->day, current->month, current->year); 
                    found=true;
                }
                else if(ListValue.find(value)!= string ::npos){
                    Data.addArticlefromEnd(current->title, current->content, current->category, current->day, current->month, current->year); 
                    found=true;
                }
                current=current -> next;
            }
            if(!found) cout << "value: " << value<< " doesn't exist";
            else{
                Data.displayArticlesfromFront();
            }
        }
        
        void BinarySearch(article *head, int index, string value) {
            if (!head) {
                cout << "Linked list is empty!" << endl;
                return;
            }
        
            article *start = head;
            article *end = nullptr;
            bool found = false;
        
            while (start != end && start != nullptr) {
                article *mid = getMiddle(start, end);
                if (!mid) break;
        
                string midValue = getField(mid, index);
        
                if (midValue == value || midValue.find(value) != string::npos) {
                    // Store result if found
                    Data.addArticlefromEnd(mid->title, mid->content, mid->category, mid->day, mid->month, mid->year);
                    found = true;
        
                    // **Check for duplicates in the left direction**
                    article *leftCheck = start;
                    while (leftCheck != mid) {
                        string leftValue = getField(leftCheck, index);
                        if (leftValue == value || leftValue.find(value) != string::npos) {
                            Data.addArticlefromEnd(leftCheck->title, leftCheck->content, leftCheck->category, leftCheck->day, leftCheck->month, leftCheck->year);
                            found = true;
                        }
                        leftCheck = leftCheck->next;
                    }
                    
                    // **Check for duplicates in the right direction**
                    article *rightCheck = mid->next;
                    while (rightCheck) {
                        string rightValue = getField(rightCheck, index);
                        if (rightValue == value || rightValue.find(value) != string::npos) {
                            Data.addArticlefromEnd(rightCheck->title, rightCheck->content, rightCheck->category, rightCheck->day, rightCheck->month, rightCheck->year);
                            found = true;
                        }
                        rightCheck = rightCheck->next;
                    }
        
                    break;  
                } 
                else if (midValue < value) {
                    start = mid->next;  // **Move right**
                } 
                else {
                    end = mid;  // **Move left**
                }
            }
        
            if (!found) 
                cout << "Value: " << value << " doesn't exist" << endl;
            else 
                Data.displayArticlesfromFront();
        }
        
        

};
#endif