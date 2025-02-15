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
        void BinarySearch();

};
#endif