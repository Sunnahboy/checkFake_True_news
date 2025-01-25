#include <iostream>
#include <limits>
#include <fstream>
#include "Interface.cpp"

using namespace std;
int main(){ 
//     Interface interface;
//     int choice;
//     interface.prinTable(4);
//     cout << "1. Data Filtering" << endl;
//     cout << "2. Sort Data" << endl;
//     cout << "3. Search Data" << endl;
//     cout << "4. FAQ" << endl;
//     cout << "5. End the Program" << endl;
//     interface.columns();
//     cout << "Enter Your choice: ";
//     while(!(cin >> choice)|| !(interface.RegInput(choice))){
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(),'\n');
//         cout << "Invaliad Input... Enter Your choice Again: ";
//     }
//     switch(choice){
//         case 1: 
//             interface.DataFilterting();
//             break;
//         case 2: 
//             interface.SortData();
//             break;
//         case 3: 
//             interface.SearchData();
//             break;
//         case 4: 
//             interface.FAQ();
//             break;
//         case 5: 
//             cout <<"Existing the program. GoodBye!";
//             return 0;
//         default: cout << "Invalid";
//     }
//     return 0;

    ifstream file("dataSets/true.csv");
    if(!file.is_open()){
        cout << "File does't exist";
        return 1;
    }

	string title, text, subject, date, line;
    bool insideQuotes = false;
    string currentField;

    // Read the file line by line
    while (getline(file, line)) {
        int fieldIndex = 0;  // To track which field we are parsing
        currentField = "";  // To build each field character by character

        // Parse the line character by character
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];

            if (c == '"') {
                // Toggle the insideQuotes flag if we encounter a quote
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                // If we encounter a comma outside quotes, the field ends
                if (fieldIndex == 0) {
                    title = currentField;
                } else if (fieldIndex == 1) {
                    text = currentField;
                } else if (fieldIndex == 2) {
                    subject = currentField;
                }
                currentField = "";  // Reset for the next field
                fieldIndex++;
            } else {
                // Otherwise, add the character to the current field
                currentField += c;
            }
        }

        // The last field (date) is handled after the loop
    }
        date = currentField;

        // Output the parsed fields
        cout << "Title: " << title << endl;
        cout << "Text: " << text << endl;
        cout << "Subject: " << subject << endl;
        cout << "Date: " << date << endl;
        cout << "---------------------------------------" << endl;

return 0;
}



