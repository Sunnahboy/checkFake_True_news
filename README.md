# News Classification System: Evaluating Search and Sort Algorithms


## 📰 Project Overview

This project implements a comprehensive news classification system that analyzes true and fake news articles using custom data structures and algorithms. The system evaluates the performance of various search and sort algorithms on news data, with a particular focus on distinguishing between true and fake news related to politics, government, and other topics.

### Key Objectives

- Efficiently sort news articles by publication year
- Calculate the percentage of fake political news articles from 2016
- Identify the most frequently used words in fake news related to government
- Compare performance of arrays and linked lists for news data analysis
- Analyze time and space complexity of different algorithms

## 🔍 Features

### Data Analysis Capabilities

- **Year-based Sorting**: Sort all articles by publication year in ascending order
- **Category Filtering**: Filter articles based on subject categories (politics, government, etc.)
- **Word Frequency Analysis**: Extract and rank most common words in specified article types
- **Statistical Analysis**: Calculate percentages of fake vs. true news in different categories
- **Monthly Trend Analysis**: Track fake news trends across months of a specific year

### Technical Implementation

- **Custom Array Implementation**: Complete array-based data structure for news article storage
- **Custom Linked List Implementation**: Self-implemented linked list for news article management
- **Multiple Search Algorithms**: Implementation of various search techniques
- **Multiple Sort Algorithms**: Custom sorting algorithms optimized for different data structures
- **Performance Measurement**: Tools to measure and compare execution time and memory usage

## 🛠️ Technologies

- **Language**: C++ (No STL containers)
- **Data Structure**: Custom array and linked list implementations
- **Input Data**: CSV files (true.csv and fake.csv)
- **Build Tools**: Standard C++ compiler (g++ recommended)



### Analyze Fake Political News Percentage (2016)

### Find Most Common Words in Government Fake News

## 🔍 Algorithm Implementations

### Search Algorithms

- **Linear Search**: O(n) - Implemented for both array and linked list
- **Binary Search**: O(log n) - Implemented for sorted arrays
- 


### Sort Algorithms

- **Bubble Sort**: O(n²) - Baseline implementation for comparison
- **Insertion Sort**: O(n²) - Efficient for small datasets and linked lists
- **Merge Sort**: O(n log n) - Efficient for large datasets
- **Quick Sort**: O(n log n) average case - Implemented for array-based solution

## 📈 Performance Comparison

| Operation             | Array Performance | Linked List Performance | Notes                                      |
|-----------------------|-------------------|-------------------------|-------------------------------------------|
| Memory Allocation     | Static            | Dynamic                 | Linked list more flexible for resizing     |
| Search by Index       | O(1)              | O(n)                    | Array has faster random access             |
| Insert/Delete         | O(n)              | O(1)                    | Linked list better for frequent updates    |
| Sort Performance      | Better            | Worse                   | Arrays have better cache locality          |
| Memory Overhead       | Lower             | Higher                  | Linked list requires pointers              |
| Implementation        | Simpler           | More Complex            | Array implementation generally easier      |

## 👥 Contributors

- [Your Name](https://github.com/yourusername)
- [Team Member 1](Ahmed)
- [Team Member 2](Kashave)
- [Team Member 3](Abdulwahb)

## 📝 License

##For full documentation check here:
### https://docs.google.com/document/d/1zQ6YcDHDv935BJfZMA8ZShav7r7PyKeGN5Wl8cOCnkg/edit?tab=t.0

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

- Asia Pacific University of Technology and Innovation for the project requirements
- Dataset sources for the news articles
- References for algorithm implementations

---

<div align="center">
  <sub>Built for Data Structures and Algorithms (CT077-3-2-DSTR) course</sub>
</div>
