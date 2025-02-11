// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include "header/Arrays.hpp"
// #include "Algorithms.cpp"

// using namespace std;
// #define TRUEMAX 21418
// #define FALSEMAX 23503
// class dataManagement
// {
//     private:
//         ArraysAlgo algo;
//         NewsArticle* article;
//         ifstream TrueData;
//         ifstream FakeData;
//     public:
//         dataManagement(){
//             // article=new NewsArticle[TRUEMAX];
//             article=new NewsArticle[FALSEMAX];
//             TrueData.open("dataSets/true.csv");
//             FakeData.open("dataSets/fake.csv");
//             if(!TrueData.is_open() || !FakeData.is_open()){
//                 cout << "Error in reading the file";
//             }
//         }



//         // void ReadData(ifstream& file){
//         //     bool QuotedFlag=false;
//         //     string Line, CurrentField, Date;
//         //     int i=0; //To add elements into the 2D array
//         //     while(getline(file, Line)){
//         //         //we create the index to parse the elements inside the file
//         //         int index=0;
//         //         //current field is initially set to none
//         //         CurrentField="";
//         //         //we make a loop to read the data and parse each character
//         //         for(size_t j=0; j < Line.length(); j++){
//         //             char c=Line[j];

//         //             if(c=='"'){
//         //                 //if we found a quote the flag set to True
//         //                 QuotedFlag=!QuotedFlag;
//         //                 CurrentField+=c;//we add the quates to the field
//         //             }else if (!isEnglishWordCharacter(c)){
//         //                 continue;
//         //             }
//         //             else if(c==',' && !QuotedFlag){
//         //                 //if we encouter a comma after the quates then we will specify each field based on the index
//         //                 if(index==0){
//         //                     article[i].title=CurrentField;
//         //                 }else if(index==1){
//         //                     article[i].content=CurrentField;
//         //                 }else if (index==2){
//         //                     article[i].category=CurrentField;
//         //                 }
//         //                 CurrentField=""; //we have to reset the current field
//         //                 index++;
//         //             }else{
//         //                 //if none of the condition were True we reset the index
//         //                 CurrentField+=c;
//         //             }
//         //         } 
//         //         Date= CurrentField;
//         //         // Handle last field (year)
//         //         ParseDate(Date, article[i].publicationYear, article[i].publicationMonth, article[i].publicationDay);
//         //         i++;
//         //         if (i >= TRUEMAX) break; // Prevent overflow
//         //     }
//         // }
//         // bool isEnglishWordCharacter(char c) {
//         //    return isalnum(c) || c == '"' || c == ',' || c==' ';
//         // }       


//         void ReadData(ifstream& file) {
//             // Lambda to read one field from a CSV line using istringstream.
//             // It handles fields enclosed in double quotes, including commas inside quotes.
//             auto readCSVField = [](istringstream &iss) -> string {
//                 string field;
//                 char c;
//                 // Check if the field is quoted.
//                 if (iss.peek() == '"') {
//                     // Consume the opening quote.
//                     iss.get(c);
//                     // Read until the closing quote.
//                     while (iss.get(c)) {
//                         if (c == '"') {
//                             // If the next character is also a quote, this is an escaped quote.
//                             if (iss.peek() == '"') {
//                                 iss.get(c); // consume the extra quote
//                                 field.push_back('"');
//                             } else {
//                                 // End of the quoted field.
//                                 break;
//                             }
//                         } else {
//                             field.push_back(c);
//                         }
//                     }
//                     // After a quoted field, there might be a comma to skip.
//                     if (iss.peek() == ',')
//                         iss.get(c);
//                 } else {
//                     // No quotes: simply get characters up to the next comma.
//                     getline(iss, field, ',');
//                 }
//                 return field;
//             };
        
//             string line;
//             int i = 0; // Index for articles in your array.
//             while(getline(file, line)) {
//                 // Create a string stream from the entire CSV line.
//                 istringstream iss(line);
        
//                 // Read the first three fields: title, content, and category.
//                 string title    = readCSVField(iss);
//                 string content  = readCSVField(iss);
//                 string category = readCSVField(iss);
                
//                 // The remaining part of the line is the date field.
//                 // (Assuming the date field is the last column in the CSV.)
//                 string dateField;
//                 getline(iss, dateField);  // Read to the end of the line.
                
//                 // Optionally, trim any leading comma that might remain.
//                 if (!dateField.empty() && dateField[0] == ',')
//                     dateField.erase(0, 1);
        
//                 // Assign the parsed fields to your NewsArticle structure.
//                 article[i].title    = title;
//                 article[i].content  = content;
//                 article[i].category = category;
                
//                 // Parse the date field into year, month, and day.
//                 ParseDate(dateField, article[i].publicationYear, 
//                                      article[i].publicationMonth, 
//                                      article[i].publicationDay);
//                 i++;
//                 if (i >= FALSEMAX) break; // Prevent overflow.
//             }
//         }


//         void ParseDate(std::string& Date, int& year, int& month, int& day) {
//             // Remove any quote characters from the Date string.
//             std::string cleanDate;
//             for (char c : Date) {
//                 if (c != '"') {
//                     cleanDate.push_back(c);
//                 }
//             }
            
//             // Use a string stream to simplify token extraction.
//             std::istringstream ss(cleanDate);
//             std::string monthToken, dayToken, yearToken;
            
//             // Expecting a format like: Month Day, Year
//             ss >> monthToken >> dayToken >> yearToken;
            
//             // Remove a trailing comma from the day token, if present.
//             if (!dayToken.empty() && dayToken.back() == ',') {
//                 dayToken.pop_back();
//             }
            
//             // Convert tokens to numeric values.
//             month = monthToNumber(monthToken);
//             day = StringToInt(dayToken);
//             year = StringToInt(yearToken);
//         }
        
        

//         // void ParseDate(string& Date, int& year, int& month, int& day){

//         //         string field = "", basket="";
//         //         int parseStage = 0;
//         //         // Manual quote removal and parsing
//         //         for (char c : Date) {
//         //             if (c == '"') continue;
//         //             if (c == ' ' || c == ',') {
//         //                 switch(parseStage) {
//         //                     case 0: month = monthToNumber(field);break;
//         //                     case 1: day = StringToInt(field); break;
//         //                     case 2: basket=field; break;// remove leading space from the year field     
//         //                     case 3: while (!field.empty() && field[field.length()-1] == ' ') field.erase(field.length()-1); year = StringToInt(field); break;
//         //                 }
//         //                 field = "";
//         //                 parseStage++;
//         //             } else {
//         //                 field += c;
//         //             }
//         //         }
//         // }


//         string** StoreToArray(int size, int* temp) {
//             // Allocate the array of row pointers.
//             string** arr = new string*[size];
        
//             // Allocate one contiguous block for all rows (size * 6 strings).
//             string* data = new string[size * 6];
        
//             // Set each row pointer to the correct location within the contiguous block.
//             for (int i = 0; i < size; i++) {
//                 arr[i] = data + i * 6;
//             }
            
//             // Fill the contiguous block using the indices provided in temp.
//             for (int i = 0; i < size; i++) {
//                 int index = temp[i];
//                 arr[i][0] = article[index].title;
//                 arr[i][1] = article[index].content;
//                 arr[i][2] = article[index].category;
//                 arr[i][3] = to_string(article[index].publicationYear);
//                 arr[i][4] = to_string(article[index].publicationMonth);
//                 arr[i][5] = to_string(article[index].publicationDay);
//             }
//             return arr;
//             // Assuming arr was returned by StoreToArray:
//             delete[] arr[0];  // Free the contiguous block (data)
//             delete[] arr;     // Free the array of pointers.

//         }
        


//         // string** StoreToArray(int size, int* temp) {
//         //     string** arr = new string*[size];
//         //     for (int i = 0; i < size; i++) {
//         //         arr[i] = new string[6];  // Allocate 6 columns for each row
//         //     }
            
//         //     for (int i = 0; i < size; i++) {
//         //         int index=temp[i];
//         //         arr[i][0] = article[index].title;
//         //         arr[i][1] = article[index].content;
//         //         arr[i][2] = article[index].category;
//         //         arr[i][3] = to_string(article[index].publicationYear);
//         //         arr[i][4] = to_string(article[index].publicationMonth);
//         //         arr[i][5] = to_string(article[index].publicationDay);
//         //     }
//         //     return arr;
//         // }

//         // an integer method that converts the strings to integers
//         int StringToInt(string& str) {
//             int result = 0;
//             for (char c : str) {
//                 result = result * 10 + (c - '0');
//             } 
//             return result;
//         }

//         int monthToNumber(string month) {
//             if (month == "January") return 1;
//             if (month == "February") return 2;
//             if (month == "March") return 3;
//             if (month == "April") return 4;
//             if (month == "May") return 5;
//             if (month == "June") return 6;
//             if (month == "July") return 7;
//             if (month == "August") return 8;
//             if (month == "September") return 9;
//             if (month == "October") return 10;
//             if (month == "November") return 11;
//             if (month == "December") return 12;
//             return -1; // Invalid month
//         }

//         ~dataManagement(){
//             delete[] article;
//             if (TrueData.is_open()) {
//                 TrueData.close();
//             }
//             if (FakeData.is_open()) {
//                 FakeData.close();
//             }
//         }
//         ifstream& getTrueData(){
//             return TrueData;
//         }
//         ifstream& getFakeData(){
//             return FakeData;
//         }

//        void head(string ** arr, int rows){
//             for(int i=1; i<rows; i++){
//                 cout << " Row Number: " <<i <<endl;
//                 cout << "Title: " <<arr[i][0]<<endl; 
//                 cout << "Text: " <<arr[i][1]<<endl<<endl; 
//                 cout << "Subject: " <<arr[i][2]<<endl; 
//                 cout <<"Year: "<< arr[i][3]<<endl; 
//                 cout <<"Month: "<< arr[i][4]<<endl; 
//                 cout <<"Day: "<< arr[i][5]<<endl; 
//                 cout << string(166,'=');
//                 cout <<endl;
//             }
//        }
//        //a void to view the contents of the struct created
//        void displayStruct(int rows){
//             for(int i=1; i<rows; i++){
//                 cout << " Row Number: " <<i <<endl;
//                 cout << "Title: " <<article[i].title<<endl; 
//                 cout << "Text: " <<article[i].content<<endl<<endl; 
//                 cout << "Subject: " <<article[i].category<<endl; 
//                 cout <<"Year: "<< article[i].publicationYear<<endl; 
//                 cout <<"Month: "<< article[i].publicationMonth<<endl; 
//                 cout <<"Day: "<< article[i].publicationDay<<endl; 
//                 cout << string(166,'=');
//                 cout <<endl;
//             }
//        }

//         void ApplyMergeSort(int size){
//             int* newYear= new int[size];
//             int* index=new int[size];
//             for (int i=0; i<size; i++){
//                 newYear[i]=article[i].publicationYear;
//                 index[i]=i;
//             }
//             algo.MergeSort(newYear, 0, size-1, index);
            
//             string** arr=StoreToArray(size-1, index);
//             head(arr, 10);
//             for (int i = 0; i < FALSEMAX; i++) {
//                 delete[] arr[i];
//             }
//             delete[] arr;

//         }
        

//         void ApplyInsertionSort(int numArticles) {
//             int* indices = new int[numArticles];
//             for (int i = 0; i < numArticles; i++){
//                 indices[i] = i;
//             }
//             // Create a 2D array (each row has 6 columns as in StoreToArray)
//             string** arr = StoreToArray(numArticles, indices);
            
//             algo.InsertionSort(arr, numArticles);
            
//             head(arr, 10); //numArticles);
            
//             // Free allocated memory
//             for (int i = 0; i < numArticles; i++){
//                 delete[] arr[i];
//             }
//             delete[] arr;
//             delete[] indices;
//         }


//         void ApplyBubbleSort(int numArticles) {
//             int* indices = new int[numArticles];
//             for (int i = 0; i < numArticles; i++){
//                 indices[i] = i;
//             }
//             string** arr = StoreToArray(numArticles, indices);

//             algo.BubbleSort();  // Example: if BubbleSort sorts the internal articles array.
            
//             // Display the sorted articles from your data structure:
//             head(arr, 10); //numArticles);
            
//             delete[] indices;
//             // (Assuming BubbleSort works in place on your internal articles array.)
//         }


//         /*
//         We can add more functions here in this point
//         */
// };



// int main() {
//     dataManagement data;
//     // data.ReadData(data.getTrueData());
//     data.ReadData(data.getFakeData());
//     data.displayStruct(3);

//     cout << "Applying Merge Sort" << endl << endl;

//     data.ApplyMergeSort(FALSEMAX);
//     data.displayStruct(3);

//     return 0;
// }




#include <iostream>
#include <fstream>
#include <sstream>
#include "header/Arrays.hpp"
#include "Algorithms.cpp"

using namespace std;

class dataManagement
{
    private:
        ArraysAlgo algo;
        NewsArticle* article;
        ifstream TrueData;
        ifstream FakeData;
        int currentSize;
        int capacity;

    public:
        dataManagement() : currentSize(0), capacity(10) {
            article = new NewsArticle[capacity];
            TrueData.open("dataSets/true.csv");
            FakeData.open("dataSets/fake.csv");
            if(!TrueData.is_open() || !FakeData.is_open()){
                cout << "Error in reading the file";
            }
        }

        void resizeArray() {
            capacity *= 2;
            NewsArticle* newArticle = new NewsArticle[capacity];
            for(int i = 0; i < currentSize; i++) {
                newArticle[i] = article[i];
            }
            delete[] article;
            article = newArticle;
        }

        void ReadData(ifstream& file) {
            auto readCSVField = [](istringstream &iss) -> string {
                string field;
                char c;
                if (iss.peek() == '"') {
                    iss.get(c);
                    while (iss.get(c)) {
                        if (c == '"') {
                            if (iss.peek() == '"') {
                                iss.get(c);
                                field.push_back('"');
                            } else {
                                break;
                            }
                        } else {
                            field.push_back(c);
                        }
                    }
                    if (iss.peek() == ',')
                        iss.get(c);
                } else {
                    getline(iss, field, ',');
                }
                return field;
            };
        
            // Skip the header row
            string header;
            getline(file, header);
            string line;
            int i = 0;
            while (getline(file, line)) {
                // Trim leading and trailing whitespace
                size_t start = line.find_first_not_of(" \t\r\n");
                if (start == string::npos) { 
                    // Line is completely whitespace; skip it
                    continue;
                }
                size_t end = line.find_last_not_of(" \t\r\n");
                string trimmedLine = line.substr(start, end - start + 1);
        
                // Skip if the trimmed line is empty (safety check)
                if (trimmedLine.empty()) {
                    continue;
                }
        
                // If we have too many articles, resize the array
                if (currentSize >= capacity) {
                    resizeArray();
                }
        
                istringstream iss(trimmedLine);
        
                string title    = readCSVField(iss);
                string content  = readCSVField(iss);
                string category = readCSVField(iss);
                
                string dateField;
                getline(iss, dateField);
                
                // Remove any leading comma if present in the date field
                if (!dateField.empty() && dateField[0] == ',') {
                    dateField.erase(0, 1);
                }

                if (title.empty() || content.empty() || category.empty() || dateField.empty()) {
                    // Skip empty or incomplete lines
                    continue;
                }
                
                article[currentSize].title    = title;
                article[currentSize].content  = content;
                article[currentSize].category = category;
                
                ParseDate(dateField, 
                          article[currentSize].publicationYear, 
                          article[currentSize].publicationMonth, 
                          article[currentSize].publicationDay);
                currentSize++;
                i++;
                if (i == 15840) {
                    break;
                }
            }
        }
        


        // void ReadData(ifstream& file) {
        //     auto readCSVField = [](istringstream &iss) -> string {
        //         string field;
        //         char c;
        //         if (iss.peek() == '"') {
        //             iss.get(c);
        //             while (iss.get(c)) {
        //                 if (c == '"') {
        //                     if (iss.peek() == '"') {
        //                         iss.get(c);
        //                         field.push_back('"');
        //                     } else {
        //                         break;
        //                     }
        //                 } else {
        //                     field.push_back(c);
        //                 }
        //             }
        //             if (iss.peek() == ',')
        //                 iss.get(c);
        //         } else {
        //             getline(iss, field, ',');
        //         }
        //         return field;
        //     };

        //     // Skip the header row
        //     string header;
        //     getline(file, header);
        
        //     string line;
        //     while(getline(file, line)) {
        //         // Skip empty or whitespace-only lines
        //         if (line.empty()) {
        //             continue;
        //         }
                
        //         if (currentSize >= capacity) {
        //             resizeArray();
        //         }

        //         istringstream iss(line);
        
        //         string title    = readCSVField(iss);
        //         string content  = readCSVField(iss);
        //         string category = readCSVField(iss);
                
        //         string dateField;
        //         getline(iss, dateField);
                
        //         if (!dateField.empty() && dateField[0] == ',')
        //             dateField.erase(0, 1);
        
        //         article[currentSize].title    = title;
        //         article[currentSize].content  = content;
        //         article[currentSize].category = category;
                
        //         ParseDate(dateField, article[currentSize].publicationYear, 
        //                               article[currentSize].publicationMonth, 
        //                               article[currentSize].publicationDay);
        //         currentSize++;
        //     }
        // }

        // void ParseDate(std::string& Date, int& year, int& month, int& day) {
        //     std::string cleanDate;
        //     for (char c : Date) {
        //         if (c != '"') {
        //             cleanDate.push_back(c);
        //         }
        //     }
            
        //     std::istringstream ss(cleanDate);
        //     std::string monthToken, dayToken, yearToken;
            
        //     ss >> monthToken >> dayToken >> yearToken;
            
        //     if (!dayToken.empty() && dayToken.back() == ',') {
        //         dayToken.pop_back();
        //     }
            
        //     month = monthToNumber(monthToken);
        //     day = StringToInt(dayToken);
        //     year = StringToInt(yearToken);
        // }

        void ParseDate(std::string& Date, int& year, int& month, int& day) {
            // Remove any extraneous quotation marks from the Date string.
            std::string cleanDate;
            for (char c : Date) {
                if (c != '"') {
                    cleanDate.push_back(c);
                }
            }
            
            // Check if the date uses dashes, e.g., "19-Feb-18"
            if (cleanDate.find('-') != std::string::npos) {
                // Expected format: "dd-MMM-yy"
                size_t firstDash = cleanDate.find('-');
                size_t secondDash = cleanDate.find('-', firstDash + 1);
                if (firstDash != std::string::npos && secondDash != std::string::npos) {
                    std::string dayToken = cleanDate.substr(0, firstDash);
                    std::string monthToken = cleanDate.substr(firstDash + 1, secondDash - firstDash - 1);
                    std::string yearToken = cleanDate.substr(secondDash + 1);

                    // cout <<  dayToken  << monthToken <<  yearToken << endl;
                    
                    // Convert the tokens to the respective values.
                    // day = StringToInt(dayToken);
                    // month = monthToNumber(monthToken);
                    // year = StringToInt(yearToken);
                    
                    // If the year is in two-digit format, assume it's 2000+ (adjust as needed).
                    if (year < 100) {
                        year += 2000;
                    }
                    return;
                }
            }
            
            // Otherwise, assume the format is like "January 1 2016" (or "January 1, 2016")
            std::istringstream ss(cleanDate);
            std::string monthToken, dayToken, yearToken;
            
            ss >> monthToken >> dayToken >> yearToken;
            
            // Remove any trailing comma from the day token (e.g., "1,")
            if (!dayToken.empty() && dayToken.back() == ',') {
                dayToken.pop_back();
            }

            // cout <<  dayToken  << monthToken <<  yearToken << endl;
            
            month = monthToNumber(monthToken);
            day = StringToInt(dayToken);
            year = StringToInt(yearToken);
        }
        

        string** StoreToArray(int size, int* temp) {
            string** arr = new string*[size];
            string* data = new string[size * 6];
        
            for (int i = 0; i < size; i++) {
                arr[i] = data + i * 6;
            }
            
            for (int i = 0; i < size; i++) {
                int index = temp[i];
                arr[i][0] = article[index].title;
                arr[i][1] = article[index].content;
                arr[i][2] = article[index].category;
                arr[i][3] = to_string(article[index].publicationYear);
                arr[i][4] = to_string(article[index].publicationMonth);
                arr[i][5] = to_string(article[index].publicationDay);
            }
            return arr;
        }

        int StringToInt(string& str) {
            int result = 0;
            for (char c : str) {
                result = result * 10 + (c - '0');
            } 
            return result;
        }

        // int monthToNumber(string month) {
        //     if (month == "January") return 1;
        //     if (month == "February") return 2;
        //     if (month == "March") return 3;
        //     if (month == "April") return 4;
        //     if (month == "May") return 5;
        //     if (month == "June") return 6;
        //     if (month == "July") return 7;
        //     if (month == "August") return 8;
        //     if (month == "September") return 9;
        //     if (month == "October") return 10;
        //     if (month == "November") return 11;
        //     if (month == "December") return 12;
        //     return -1;
        // }

        int monthToNumber(std::string month) {
            if (month == "January" || month == "Jan") return 1;
            if (month == "February" || month == "Feb") return 2;
            if (month == "March" || month == "Mar") return 3;
            if (month == "April" || month == "Apr") return 4;
            if (month == "May") return 5;
            if (month == "June" || month == "Jun") return 6;
            if (month == "July" || month == "Jul") return 7;
            if (month == "August" || month == "Aug") return 8;
            if (month == "September" || month == "Sep") return 9;
            if (month == "October" || month == "Oct") return 10;
            if (month == "November" || month == "Nov") return 11;
            if (month == "December" || month == "Dec") return 12;
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

       void displayStruct(int rows){
            for(int i=1; i<rows; i++){
                if (article[i].publicationYear == 0) {
                    cout << "Zero year found at index: " << i << endl;
                
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
                // if (i == 9050) {
                //     cout << "Index 9050" << endl;
                //     cout << "Title: " << article[i].title << endl;
                //     cout << "Content: " << article[i].content << endl;
                //     cout << "Category: " << article[i].category << endl;
                //     cout << "Year: " << article[i].publicationYear << endl;
                //     cout << "Month: " << article[i].publicationMonth << endl;
                //     cout << "Day: " << article[i].publicationDay << endl;
                // }
            }
       }

        // void ApplyMergeSort(int size){
        //     int* newYear= new int[size];
        //     int* index=new int[size];
        //     for (int i=0; i<size; i++){
        //         newYear[i]=article[i].publicationYear;
        //         index[i]=i;
        //     }
        //     algo.MergeSort(newYear, 0, size-1, index);
            
        //     string** arr=StoreToArray(size-1, index);
        //     head(arr, 10);
        //     delete[] arr[0];
        //     delete[] arr;
        // }

        void ApplyMergeSort(int size) {
            // Create arrays to track original years and indices
            int* newYear = new int[size];
            int* index = new int[size];
            
            // Populate initial arrays with years and original indices
            for (int i = 0; i < size; i++) {
                newYear[i] = article[i].publicationYear;
                index[i] = i;
                // if (newYear[i] == 0) {
                //     cout << "Zero year found at index: " << i << endl;
                // }
                // cout << newYear[i] << endl;
            }

            
            
            // Perform merge sort
            algo.MergeSort(newYear, 0, size - 1, index);
            
            // Create a new temporary array to store sorted articles
            NewsArticle* sortedArticles = new NewsArticle[size];
            
            // Remap articles based on sorted indices
            for (int i = 0; i < size; i++) {
                sortedArticles[i] = article[index[i]];
            }
            
            // Copy sorted articles back to original array
            for (int i = 0; i < size; i++) {
                article[i] = sortedArticles[i];
            }
            
            // Clean up temporary arrays
            delete[] newYear;
            delete[] index;
            delete[] sortedArticles;
            
            // Uncomment to display sorted articles
            displayStruct(20);
        }
        
        void ApplyInsertionSort(int numArticles) {
            int* indices = new int[numArticles];
            for (int i = 0; i < numArticles; i++){
                indices[i] = i;
            }
            string** arr = StoreToArray(numArticles, indices);
            
            algo.InsertionSort(arr, numArticles);
            
            head(arr, 10);
            
            delete[] arr[0];
            delete[] arr;
            delete[] indices;
        }

        void ApplyBubbleSort(int numArticles) {
            int* indices = new int[numArticles];
            for (int i = 0; i < numArticles; i++){
                indices[i] = i;
            }
            string** arr = StoreToArray(numArticles, indices);

            algo.BubbleSort();
            
            head(arr, 10);
            
            delete[] indices;
        }

        int getCurrentSize() const {
            return currentSize;
        }
};

int main() {
    dataManagement data;
    data.ReadData(data.getFakeData());
    // data.ReadData(data.getTrueData());
    data.displayStruct(15840);//data.getCurrentSize());

    // cout << "Applying Merge Sort" << endl << endl;

    // data.ApplyMergeSort(data.getCurrentSize());
    // data.ApplyInsertionSort(data.getCurrentSize());
    // data.displayStruct(3);

    return 0;
}