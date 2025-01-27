#include <iostream>
#include <fstream>
#include "header/Arrays.hpp"
#include "Algorithms.cpp"
using namespace std;
#define TRUEMAX 21418
#define FALSEMAX 23503
class dataManagement
{
    private:
        ArraysAlgo algo;
        ifstream TrueData;
        ifstream FakeData;
    public:
        dataManagement(){
            TrueData.open("dataSets/true.csv");
            FakeData.open("dataSets/fake.csv");
            if(!TrueData.is_open() || !FakeData.is_open()){
                cout << "Error in reading the file";
            }
        }

        void ReadToArray(string** arr, ifstream& file){
            bool QuotedFlag=false;
            string CurrentField, Title, Text, Date, Subject, Line;
            int i=0; //To add elements into the 2D array
            while(getline(file, Line)){
                //we create the index to parse the elements inside the file
                int index=0;
                //current field is initially set to none
                CurrentField="";
                //we make a loop to read the data and parse each character
                for(size_t i=0; i < Line.length(); i++){
                    char c=Line[i];

                    if(c=='"'){
                        //if we found a quote the flag set to True
                        QuotedFlag=!QuotedFlag;
                        CurrentField+=c;//we add the quates to the field
                    }else if(c==',' && !QuotedFlag){
                        //if we encouter a comma after the quates then we will specify each field based on the index
                        if(index==0){
                            Title=CurrentField;
                        }else if(index==1){
                            Text=CurrentField;
                        }else if (index==2){
                            Subject=CurrentField;
                        }
                        CurrentField=""; //we have to reset the current field
                        index++;
                    }else{
                        //if none of the condition were True we reset the index
                        CurrentField+=c;
                    }
                } 
                Date=CurrentField;
                string field = "";
                int month = 0, day = 0, year = 0;
                int parseStage = 0;

                // Manual quote removal and parsing
                for (char c : Date) {
                    if (c == '"') continue;
                    
                    if (c == ' ' || c == ',') {
                        switch(parseStage) {
                            case 0: 
                                month = monthToNumber(field);
                                break;
                        case 1:
                            day = StringToInt(field);
                            break;
                        case 2:
                                cleanDate=field; //to get the space leading the year
                                break;     
                        case 3:
                            while (!field.empty() && field[field.length()-1] == ' ') 
                                field.erase(field.length()-1);
                            year = StringToInt(field);
                            break;
                        }
                        field = "";
                        parseStage++;
                    } else {
                        field += c;
                    }
                }
                // Handle last field (year)
                int finaldate = year * 10000 + month * 100 + day;
                arr[i][0]=Title;
                arr[i][1]=Text;
                arr[i][2]=Subject;
                arr[i][3]=to_string(finaldate);
                i++;
            }
        }

        // an integer method that converts the strings to integers
        int StringToInt(string& str) {
            int result = 0;
            for (char c : str) {
                result = result * 10 + (c - '0');
            }
            return result;
        }

        int monthToNumber(string month) {
            if (month == "January") return 1;
            if (month == "February") return 2;
            if (month == "March") return 3;
            if (month == "April") return 4;
            if (month == "May") return 5;
            if (month == "June") return 6;
            if (month == "July") return 7;
            if (month == "August") return 8;
            if (month == "September") return 9;
            if (month == "October") return 10;
            if (month == "November") return 11;
            if (month == "December") return 12;
            return -1; // Invalid month
        }

        void DataTransformation(string** arr) {
            for(size_t i = 1; i < TRUEMAX; i++) {
                string date = arr[i][3];
                string cleanDate = "";
                string field = "";
                int month = 0, day = 0, year = 0;
                int parseStage = 0;

                // Manual quote removal and parsing
                for (char c : date) {
                    if (c == '"') continue;
                    
                    if (c == ' ' || c == ',') {
                        switch(parseStage) {
                            case 0: 
                                month = monthToNumber(field);
                                break;
                        case 1:
                            day = StringToInt(field);
                            break;
                        case 2:
                                cleanDate=field; //to get the space leading the year
                                break;     
                        case 3:
                            while (!field.empty() && field[field.length()-1] == ' ') 
                                field.erase(field.length()-1);
                            year = StringToInt(field);
                            break;
                        }
                        field = "";
                        parseStage++;
                    } else {
                        field += c;
                    }
                }
                // Handle last field (year)
                int finaldate = year * 10000 + month * 100 + day;
                arr[i][3]=to_string(finaldate);
            }
        }

        // A method to convert the 2D array to 1D array
        int* ArrayConversion(string** arr){
            int * array1D= new int[TRUEMAX];
            for (int i=0; i<TRUEMAX; i++){
                array1D[i]= StringToInt(arr[i][3]);
            }
            algo.MergeSort(array1D, 0, TRUEMAX-1);
            return array1D;
        }

        ~dataManagement(){
            if (TrueData.is_open()) {
                TrueData.close();
            }
            if (FakeData.is_open()) {
                FakeData.close();
            }
        }
        ifstream& getTrueData(){
            return TrueData;
        }
        ifstream& getFakeData(){
            return FakeData;
        }

       void head(string ** arr, int rows){
            for(int i=1; i<rows; i++){
                // cout << i << " Row"<<endl;
                // cout << "Title: " <<arr[i][0]<<endl; 
                // cout << "Text: " <<arr[i][1]<<endl<<endl; 
                // cout << "Subject: " <<arr[i][2]<<endl; 
                cout <<arr[i][3]<<endl; 
                cout << string(166,'=');
                cout <<endl;
            }
       }
        // void ApplySort(string** array){ 
        // }

        /*
        We can add more functions here in this point
        */
};

int main() {
    dataManagement data;
    string** array = new string*[TRUEMAX];

    // Allocate memory for the 2D array
    for (int i = 0; i < TRUEMAX; i++) {
        array[i] = new string[4];
    }

    // Read data into the array
    data.ReadToArray(array, data.getTrueData());
    data.head(array, 10);
    // data.DataTransformation(array);

    int *arr=data.ArrayConversion(array);
    for(int i=0; i< TRUEMAX; i++){
        cout << arr[i] <<endl;
    }

    // data.ApplySort(array);

    for (int i = 0; i < TRUEMAX; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}
