#include <iostream>
#include <fstream>
using namespace std;
#define MAX 100000
class dataManagement
{
    private:
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
                arr[i][0]=Title;
                arr[i][1]=Text;
                arr[i][2]=Subject;
                arr[i][3]=Date;
                i++;
            }
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
            for(int i=1; i<=rows; i++){
                cout << i << " Row"<<endl;
                cout << "Title: " <<arr[i][0]<<endl; 
                cout << "Text: " <<arr[i][1]<<endl<<endl; 
                cout << "Subject: " <<arr[i][2]<<endl; 
                cout << "Date: " <<arr[i][3]<<endl; 
                cout << string(180,'=');
                cout <<endl;
            }
       }
        /*
        We can add more functions here in this point
        */
};

int main(){
    dataManagement data;
    string** array=new string*[MAX];
    
    for(int i=0; i< MAX; i++){
        array[i]=new string[4];
    }
    //a crucial step to set the columns of the array to 4 
    //the loop goes to every line of the 2D array and set the memory to 4
    
    int row=20;//you can set the number of rows as you want
    data.ReadToArray(array, data.getTrueData());
    data.head(array, row);
    

    return 0;
}