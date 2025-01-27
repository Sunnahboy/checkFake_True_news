#include "Arrays.hpp"
//bubble sort algorithm by akira
//merge sort ahorithm by ahemed
void Merge(int * arr, int LEFT, int MID, int RIGHT){
    
    int L=MID-LEFT +1;
    int R=RIGHT-MID;
    
    //creating two temporary arrays for sorting the data divided
    int * leftArr=new int[L];
    int * rightArr=new int[R];
    
    //fill the temporary arrays with values for each recursion
    for(int i=0; i<L; i++){
        leftArr[i]=arr[i+LEFT];
    }
    for(int j=0; j<L; j++){
        rightArr[j]=arr[MID+1+j];
    }

    //create three integers to parse each array left and right and the sorted one
    int j=0, i=0, k=LEFT;
    //k value set to LEFT to avoid overwriting elements from the right array to the left array and update the positions
    
    while(i<L && j<R){
        if(leftArr[i]<=rightArr[j]){
            arr[k]=leftArr[i];
            i++;
        }
        else
        {
            arr[k]=rightArr[j];
            j++;    
        }
        k++;
    }

    // add remaining elements to the array
    //remaining elements could be either on the right or the left of the array so have to account for both and create a while loop for both
    while(i<L){
        arr[k]=leftArr[i];
        i++;
        k++;
    }
    while(j < R){
        arr[k]=rightArr[j];
        j++;
        k++;
    }

    //now we delete both temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}

void ArraysAlgo::MergeSort(int* arr, int left, int right){
    if(left==right)return;
    int mid=(left+right)/2;
    MergeSort(arr, left, mid);
    MergeSort(arr,mid+1, right);
    Merge(arr, left, mid, right);
}



//Custom String Comparison Function
bool ArrayAlgo::customStringCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false; // Mismatch found
        }
        i++;
    }
    // Both strings should end at the same position
    return (str1[i] == '\0' && str2[i] == '\0');
}



void ArraysAlgo::sortByYear() {
    // Perform Bubble Sort on the articles array
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (articles[j].publicationYear > articles[j + 1].publicationYear) {
                // Swap articles[j] and articles[j + 1]
                NewsArticle temp = articles[j];
                articles[j] = articles[j + 1];
                articles[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, then the array is sorted
        if (!swapped) {
            break;
        }
    }
}


//Display the Entire List in Ascending Order
void ArraysAlgo::displayArticles() const {
    for (int i = 0; i < size; i++) {
        // Print each article's details
        cout<<("Title: %s\n", articles[i].title);
        cout <<("Content: %s\n", articles[i].content);
        cout<<("Category: %s\n", articles[i].category);
        cout<<("Publication Date: %d-%02d-%02d\n",
            articles[i].publicationYear,
            articles[i].publicationMonth,
            articles[i].publicationDay);
        cout<<("---------------------------------\n");
    }
}


void ArraysAlgo::binarysearchYear(int year) const {
    int left = 0, right = size - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (articles[mid].publicationYear == year) {
            // Match found; display article
            cout("Match Found:\n");
            displayArticle(articles[mid]);
            found = true;

            // Check for duplicates in both directions
            int temp = mid - 1;
            while (temp >= 0 && articles[temp].publicationYear == year) {
                displayArticle(articles[temp]);
                temp--;
            }

            temp = mid + 1;
            while (temp < size && articles[temp].publicationYear == year) {
                displayArticle(articles[temp]);
                temp++;
            }
            break;
        }

        if (articles[mid].publicationYear < year) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("No articles found for the year: %d\n", year);
    }
}


void ArrayAlgo::LinearsearchByCategory(const char* category) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (customStringCompare(articles[i].category, category)) {
            // Match found; display the article
            printf("Match Found:\n");
            displayArticle(articles[i]);
            found = true;

            // Perform transposition to move the article closer to the start
            if (i > 0) {
                NewsArticle temp = articles[i];
                articles[i] = articles[i - 1];
                articles[i - 1] = temp;
            }

            // Continue searching for other matches
        }
    }

    if (!found) {
        cout<<("No articles found in category: %s\n", category);
    }
}



//quick sort algorithm by abu
//insertion sort algorithm by kashave


