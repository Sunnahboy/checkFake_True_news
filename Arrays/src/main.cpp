#include <iostream>
#include <limits>
#include <fstream>
#include "Interface.hpp"


using namespace std;
int main(){ 
    Interface interface;
    int choice;
    bool running = true;

    while(running) {
        interface.prinTable(4);
        cout << "1. Data Filtering" << endl;
        cout << "2. Sort Data" << endl;
        cout << "3. Search Data" << endl;
        cout << "4. FAQ" << endl;
        cout << "5. End the Program" << endl;
        interface.columns();
        cout << "Enter Your choice: ";
        while(!(cin >> choice)|| !(interface.RegInput(choice))){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invaliad Input... Enter Your choice Again: ";
        }
        switch(choice){
            case 1: 
                interface.DataFilterting();
                break;
            case 2: 
                interface.SortData();
                break;
            case 3: 
                interface.SearchData();
                break;
            case 4: 
                interface.FAQ();
                break;
            case 5: 
                cout <<"Existing the program. GoodBye!";
                running = false;
                break;
            default: cout << "Invalid";
        }
    }

    return 0;
}



