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
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
    public:
        dataManagement(){
            article=new NewsArticle[TRUEMAX];
            TrueData.open("dataSets/true.csv");
            FakeData.open("dataSets/fake.csv");
            if(!TrueData.is_open() || !FakeData.is_open()){
                cout << "Error in reading the file";
            }
        }

        void ReadData(ifstream& file){
            bool QuotedFlag=false;
            string Line, CurrentField, Date;
            int i=0; //To add elements into the 2D array
            while(getline(file, Line)){
                //we create the index to parse the elements inside the file
                int index=0;
                //current field is initially set to none
                CurrentField="";
                //we make a loop to read the data and parse each character
                for(size_t j=0; j < Line.length(); j++){
                    char c=Line[j];

                    if(c=='"'){
                        //if we found a quote the flag set to True
                        QuotedFlag=!QuotedFlag;
                        CurrentField+=c;//we add the quates to the field
                    }else if (!isEnglishWordCharacter(c)){
                        continue;
                    }
                    else if(c==',' && !QuotedFlag){
                        //if we encouter a comma after the quates then we will specify each field based on the index
                        if(index==0){
                            article[i].title=CurrentField;
                        }else if(index==1){
                            article[i].content=CurrentField;
                        }else if (index==2){
                            article[i].category=CurrentField;
                        }
                        CurrentField=""; //we have to reset the current field
                        index++;
                    }else{
                        //if none of the condition were True we reset the index
                        CurrentField+=c;
                    }
                } 
                Date= CurrentField;
                // Handle last field (year)
                ParseDate(Date, article[i].publicationYear, article[i].publicationMonth, article[i].publicationDay);
                i++;
                if (i >= TRUEMAX) break; // Prevent overflow
            }
        }
        bool isEnglishWordCharacter(char c) {
           return isalnum(c) || c == '"' || c == ',' || c==' ';
        }       

        void ParseDate(string& Date, int& year, int& month, int& day){

                string field = "", basket="";
                int parseStage = 0;
                // Manual quote removal and parsing
                for (char c : Date) {
                    if (c == '"') continue;
                    if (c == ' ' || c == ',') {
                        switch(parseStage) {
                            case 0: month = monthToNumber(field);break;
                            case 1: day = StringToInt(field); break;
                            case 2: basket=field; break;// remove leading space from the year field     
                            case 3: while (!field.empty() && field[field.length()-1] == ' ') field.erase(field.length()-1); year = StringToInt(field); break;
                        }
                        field = "";
                        parseStage++;
                    } else {
                        field += c;
                    }
                }
        }


        string** StoreToArray(int size, int* temp) {
            string** arr = new string*[size];
            for (int i = 0; i < size; i++) {
                arr[i] = new string[6];  // Allocate 6 columns for each row
            }
            
            for (int i = 0; i < size; i++) {
                int index=temp[i];
                arr[i][0] = article[index].title;
                arr[i][1] = article[index].content;
                arr[i][2] = article[index].category;
                arr[i][3] = to_string(article[index].publicationYear);
                arr[i][4] = to_string(article[index].publicationMonth);
                arr[i][5] = to_string(article[index].publicationDay);
            }
            return arr;
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

        ~dataManagement(){
            delete[] article;
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
                cout << " Row Number: " <<i <<endl;
                cout << "Title: " <<arr[i][0]<<endl; 
                cout << "Text: " <<arr[i][1]<<endl<<endl; 
                cout << "Subject: " <<arr[i][2]<<endl; 
                cout <<"Year: "<< arr[i][3]<<endl; 
                cout <<"Month: "<< arr[i][4]<<endl; 
                cout <<"Day: "<< arr[i][5]<<endl; 
                cout << string(166,'=');
                cout <<endl;
            }
       }
       //a void to view the contents of the struct created
       void displayStruct(int rows){
            for(int i=1; i<rows; i++){
                cout << " Row Number: " <<i <<endl;
                cout << "Title: " <<article[i].title<<endl; 
                cout << "Text: " <<article[i].content<<endl<<endl; 
                cout << "Subject: " <<article[i].category<<endl; 
                cout <<"Year: "<< article[i].publicationYear<<endl; 
                cout <<"Month: "<< article[i].publicationMonth<<endl; 
                cout <<"Day: "<< article[i].publicationDay<<endl; 
                cout << string(166,'=');
                cout <<endl;
            }
       }

        void ApplySort(int size){
            int* newYear= new int[size];
            int* index=new int[size];
            for (int i=0; i<size; i++){
                newYear[i]=article[i].publicationYear;
                index[i]=i;
            }
            algo.MergeSort(newYear, 0, size-1, index);
            // for (int i=0; i<size; i++){
            //     cout << index[i]<<endl;
            // }
            string** arr=StoreToArray(size-1, index);
            head(arr, 10);
            for (int i = 0; i < TRUEMAX; i++) {
                delete[] arr[i];
            }
            delete[] arr;

        }
        /*
        We can add more functions here in this point
        */
};

int main() {
    dataManagement data;
    data.ReadData(data.getTrueData());
    data.displayStruct(46);

    // data.ApplySort(TRUEMAX);


    return 0;
}
