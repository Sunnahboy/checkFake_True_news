

#include "header/PerformanceProfiler.hpp"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include "header/Arrays.hpp"
#include "Algorithms.cpp"
#include <chrono>
#include <string>


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

        //     while (getline(file, line)) {
        //         // Trim leading and trailing whitespace
        //         size_t start = line.find_first_not_of(" \t\r\n");
        //         if (start == string::npos) { 
        //             // Line is completely whitespace; skip it
        //             continue;
        //         }
        //         size_t end = line.find_last_not_of(" \t\r\n");
        //         string trimmedLine = line.substr(start, end - start + 1);
        
        //         // Skip if the trimmed line is empty (safety check)
        //         if (trimmedLine.empty()) {
        //             continue;
        //         }
        
        //         // If we have too many articles, resize the array
        //         if (currentSize >= capacity) {
        //             resizeArray();
        //         }
        
        //         istringstream iss(trimmedLine);
        
        //         string title    = readCSVField(iss);
        //         string content  = readCSVField(iss);
        //         string category = readCSVField(iss);
                
        //         string dateField;
        //         getline(iss, dateField);
                
        //         // Remove any leading comma if present in the date field
        //         if (!dateField.empty() && dateField[0] == ',') {
        //             dateField.erase(0, 1);
        //         }

        //         if (title.empty() || content.empty() || category.empty() || dateField.empty()) {
        //             // Skip empty or incomplete lines
        //             continue;
        //         }
                
        //         article[currentSize].title    = title;
        //         article[currentSize].content  = content;
        //         article[currentSize].category = category;
                
        //         ParseDate(dateField, 
        //                   article[currentSize].publicationYear, 
        //                   article[currentSize].publicationMonth, 
        //                   article[currentSize].publicationDay);
        //         currentSize++;
        //     }
        // }
        


        void ReadData(ifstream& file) {
            auto readCSVField = [](istringstream &iss) -> string {
                string field;
                if (iss.peek() == '"') { 
                    iss.get(); // Consume the opening quote
                    getline(iss, field, '"'); // Read until closing quote
                    iss.get(); // Consume the closing quote
                    if (iss.peek() == ',') iss.get(); // Consume the comma if present
                } else {
                    getline(iss, field, ','); // Read until comma for unquoted fields
                }
                return field;
            };
        
            // Skip the header row
            string header;
            getline(file, header);
            string line;
        
            while (getline(file, line)) {
                // Trim leading and trailing whitespace
                size_t start = line.find_first_not_of(" \t\r\n");
                if (start == string::npos) continue; // Skip empty or whitespace-only lines
                size_t end = line.find_last_not_of(" \t\r\n");
                string trimmedLine = line.substr(start, end - start + 1);
                
                if (trimmedLine.empty()) continue; // Double check for empty lines
                
                // Resize array if needed
                if (currentSize >= capacity) resizeArray();
        
                istringstream iss(trimmedLine);
        
                // Read CSV fields efficiently
                string title    = readCSVField(iss);
                string content  = readCSVField(iss);
                string category = readCSVField(iss);
                string dateField;
                getline(iss, dateField); // Read remaining date field
        
                // Remove leading comma if present in the date field
                if (!dateField.empty() && dateField[0] == ',') {
                    dateField.erase(0, 1);
                }
        
                if (title.empty() || content.empty() || category.empty() || dateField.empty()) continue;
        
                // Store parsed data
                article[currentSize].title    = title;
                article[currentSize].content  = content;
                article[currentSize].category = category;
        
                // Parse and store date
                ParseDate(dateField, 
                          article[currentSize].publicationYear, 
                          article[currentSize].publicationMonth, 
                          article[currentSize].publicationDay);
        
                currentSize++;
            }
        }
        

        void ParseDate(std::string& Date, int& year, int& month, int& day) {
            // Remove any extraneous quotation marks from the Date string.
            string cleanDate;
            string monthToken, dayToken, yearToken;
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
                if (firstDash != std::string::npos && secondDash != string::npos) {
                    dayToken = cleanDate.substr(0, firstDash);
                    monthToken = cleanDate.substr(firstDash + 1, secondDash - firstDash - 1);
                    yearToken = cleanDate.substr(secondDash + 1);

                    // cout <<  dayToken  << monthToken <<  yearToken << endl;
                    
                    // Convert the tokens to the respective values.
                    day = StringToInt(dayToken);
                    month = monthToNumber(monthToken);
                    year = StringToInt(yearToken);
                    
                    // If the year is in two-digit format, assume it's 2000+ (adjust as needed).
                    if (year < 100) {
                        year += 2000;
                    }
                    return;
                }
            }
            
            // Otherwise, assume the format is like "January 1 2016" (or "January 1, 2016")
            istringstream ss(cleanDate);
            
            
            ss >> monthToken >> dayToken >> yearToken;
            
            // Remove any trailing comma from the day token (e.g., "1,")
            if (!dayToken.empty() && dayToken.back() == ',') {
                dayToken.pop_back();
            }

           
            
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
                //cout << "Text: " <<arr[i][1]<<endl<<endl; 
                //cout << "Subject: " <<arr[i][2]<<endl; 
                cout <<"Year: "<< arr[i][3]<<endl; 
                cout <<"Month: "<< arr[i][4]<<endl; 
                cout <<"Day: "<< arr[i][5]<<endl; 
                //cout << string(166,'=');
                cout <<endl;
            }
       }

       void displayStruct(int rows){
            for(int i=1; i<=rows; i++){ 
                cout << " Row Number: " <<i <<endl;
                cout << "Title: " <<article[i].title<<endl; 
                cout << "Text: " <<article[i].content<<endl<<endl; 
                cout << "Subject: " <<article[i].category<<endl; 
                cout << "Date: " << article[i].publicationDay << "-" << article[i].publicationMonth << "-" << article[i].publicationYear << endl;
                // cout <<"Year: "<< article[i].publicationYear<<endl; 
                // cout <<"Month: "<< article[i].publicationMonth<<endl; 
                // cout <<"Day: "<< article[i].publicationDay<<endl; 
                cout << string(166,'=');
                cout <<endl;
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
            for (int i = 0; i < 20; i++) {
                sortedArticles[i] = article[index[i]];
                // cout << "Index: " << index[i] <<endl;
            }
            
            
            // Copy sorted articles back to original array
            for (int i = 0; i < 10; i++) {
                article[i] = sortedArticles[i];
            }
            
            // Clean up temporary arrays
            delete[] newYear;
            delete[] index;
            delete[] sortedArticles;
            
            // Uncomment to display sorted articles
            // displayStruct(20);
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

        //void ApplyBubbleSort(int numArticles) {
        //    int* indices = new int[numArticles];
        //    for (int i = 0; i < numArticles; i++){
        //        indices[i] = i;
        //    }
        //    string** arr = StoreToArray(numArticles, indices);
//
        //    algo.BubbleSort();
        //    
        //    head(arr, 10);
        //    
        //    delete[] indices;
        //}
//

void ApplyBubbleSort(int numArticles) {
    int* indices = new int[numArticles];
    for (int i = 0; i < numArticles; i++) {
        indices[i] = i;
        
    }

    string** arr = StoreToArray(numArticles, indices);

    ArraysAlgo algo;
    cout << "Before Bubble Sort:" << endl;
    head(arr, 10);
    algo.BubbleSort(arr, numArticles);  // Use arr, not data
    cout << "After Bubble Sort:" << endl;
    head(arr, 10);


    delete[] arr[0];
    delete[] arr;
    delete[] indices;
}



        int getCurrentSize() const {
            return currentSize;
        }
           
};

int main() {
    dataManagement data;
    //data.ReadData(data.getFakeData());
    data.ReadData(data.getFakeData());
    //data.ApplyInsertionSort(data.getCurrentSize());
    // data.displayStruct(3);
    data.ApplyBubbleSort(10);
    //const int numAlgorithms = 1;

    // Use the nested type by qualifying with the class name.
    //dataManagement::PerformanceMetrics metricsArray[numAlgorithms];

    // Wrap the sort call in a lambda to defer execution.
    //metricsArray[0] = data.profileAlgorithm(
    //    "Process merge sort",
    //    "O(n log n)",
    //    "O(n)",
    //    [&data]() { 
    //        data.ApplyMergeSort(data.getCurrentSize());
    //    }
    //);
    //
//
    //cout << "\nSummary of Performance Metrics (stored in array):\n";
    //for (int i = 0; i < numAlgorithms; ++i) {
    //    cout << "Result " << i << ": Time = " << metricsArray[i].timeSeconds
    //            << " sec, Memory Change = " << metricsArray[i].memoryKB << " KB\n";
    //}
    profileAlgorithm(&data,"Bubble Sort", "O(n)", "O(1)", &data.ApplyMergeSort, data.getCurrentSize());
    return 0;
}
