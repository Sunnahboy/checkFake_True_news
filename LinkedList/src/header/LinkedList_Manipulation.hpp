
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

        LinkedListAlgo(std::string name = "DATA") {}

        bool compareDates(article* a, article* b);

        bool compareSubject(article* a, article* b);

        template <typename Comparator>
        article* mergeSortedLists(article* a, article* b, Comparator comp);
        template <typename Comparator>
        article* bottomUpMergeSort(article* head, Comparator comp);
        template <typename Comparator>
        article* insertionSort(article* head, Comparator comp);
        template <typename Comparator>
        article* quickSort(article* head, Comparator comp);
        template <typename Comparator>
        article* bubbleSort(article* head, Comparator comp);


        template <typename Comparator, typename T>
        article* linearSearch(article* head, const T& target, Comparator comp, int* position);
        template <typename Comparator, typename T>
        article* recursiveSearch(article* current, const T& target, Comparator comp, int* position, int pos);
        template <typename Comparator, typename T>
        article* search(article* head, const T& target, Comparator comp, int* position);
        bool compareByTitleKeyword(article* a, const string& keyword);
        bool compareByCategory(article* a, const string& target);
        bool compareByMonth(article* a, int targetMonth);
        bool compareByYear(article* a, int targetYear);
        bool caseInsensitiveCompare(const string& str1, const string& str2);

        article* sortArticles(article* head, int choice, int sortType);

        void userSearchAndSwitch(article* head, int SearchChoice);

        void compareAndDisplayPerformance(article* head, int year, article*& result, int FunctionChoice);
        

};
#endif