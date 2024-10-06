//
//  main.cpp
//  Cs300_hw4
//
//  Created by Mehmet Egehan Pala on 22.05.2024.
//


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include "sorts.h"



using namespace std;


// Function to convert a string to lowercase
string capitalise(string& str) {
    string temp;
    for(int i=0; i<str.length(); i++){
        if(i=0){
            temp += toupper(str[i]);
        }
        else{
            temp += tolower(str[i]);
        }
    }
    return temp;
}
// Function to convert a string to lowercase
string toUpper(string& str) {
    string temp;
    for(int i=0; i<str.length(); i++){
            temp += toupper(str[i]);
    }
    return temp;
}


// Function to split a line of strings into single strings
vector<string> split(const string& str) {
    vector<string> queryWords;
    stringstream ss(str);
    string word;
    
    while (ss >> word) { // if there are empty spaces between strings split them and add to the vector
        queryWords.push_back(word);
    }
    
    return queryWords;
}

template <class Comparable>
vector<Comparable> readFile(const string& filename) {
    vector<Comparable> book;
    ifstream file(filename);

    if (file.is_open()) {

        Comparable person;
        while (file >> person.name >> person.surname >> person.telNo >> person.city) { //add the person information to struct

            person.fullName = person.name + " " + person.surname;  //store the fullname to use it later on sorting
            book.push_back(person);
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to open file " << filename << endl;
    }
    return book;
}




//binary search
template <class Comparable>
vector<Comparable> binarySearch(const vector<Comparable>& a, const string& query) {
    vector<Comparable> results;
    int min = 0;
    int max = a.size() - 1;
    bool check = false;
    if (query.find(' ') != string::npos)
        check = true;
    
    while (min <= max) {
        int middle = min + (max - min) / 2;
        if (check) {
            if (a[middle].fullName == query) {
                // Exact full name match found
                results.push_back(a[middle]);
                return results;
            }
            else if (a[middle].fullName < query) {
                min = middle + 1;
            }
            else {
                max = middle - 1;
            }
        }
        else {
            if (a[middle].name.substr(0, query.length()) == query) {
                // Partial name match found
                results.push_back(a[middle]);
            }
            // Check which direction to search next
            if (a[middle].fullName < query) {
                min = middle + 1;
            }
            else {
                max = middle - 1;
            }
        }
    }
    return results; // Return empty vector if no matches found
}



// Sequential search function
template <class Comparable>
vector<Comparable> sequentialSearch(const vector<Comparable>& a, const string& query) {

    vector<Comparable> results;

    bool check = false;
    if (query.find(' ') != string::npos)
        check = true;


    for (int i = 0; i<a.size(); i++) {
        if (check) {
            if (a[i].fullName == query) {
                results.push_back(a[i]);
                break; // Break out of the loop after finding the first match
            }
        }
        else {
            if (a[i].name.substr(0, query.length()) == query) {
                results.push_back(a[i]);
            }
        }
    }
    return results;
}

//Sequential search algorithm for printing the results of the search
template <class Comparable>
vector<Comparable> outputs(const vector<Comparable>& a, const string& query) {
    vector<Comparable> results;
    bool check = false;


    if (query.find(' ') != string::npos)
        check = true;
    

    for (int i = 0; i<a.size(); i++) {
        if (check) {
            if (a[i].fullName == query) {
                results.push_back(a[i]);
            }
        }
        else {
            if (a[i].name.substr(0, query.length()) == query) {
                results.push_back(a[i]);
            }
        }
    }
    return results;
}





int main(){ 

    string fileName;
    cout << "Please enter the contact file name: "; cin>>fileName;
    vector<info> book = readFile<info>(fileName);
    

    string query;
    cout << "Enter the search query: ";
    cin.ignore(); // Clear input buffer
    getline(cin, query);
    



    vector<info> bookInsertionSort = book;
    // Measure insertion sort time
    auto start = chrono::high_resolution_clock::now();
    insertionSort(bookInsertionSort);
    auto insertionSortTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);


    vector<info> bookHeapSort = book;
    // Measure heap sort time
    start = chrono::high_resolution_clock::now();
    heapsort(bookHeapSort);
    auto heapSortTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);


    vector<info> bookMergeSort = book;
    // Measure merge sort time
    start = chrono::high_resolution_clock::now();
    mergeSort(bookMergeSort);
    auto mergeSortTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);

    vector<info> bookQuickSort = book;
    // Measure quick sort (median) time
    start = chrono::high_resolution_clock::now();
    quicksort(bookQuickSort);
    auto quickSortTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);
    cout << endl;
    cout << "Sorting the vector copies" << endl;
    cout << "======================================" << endl;
    // Print the execution times with the desired format
    cout << "Quick Sort Time: " << quickSortTime.count() << " Nanoseconds" << endl;
    cout << "Insertion Sort Time: " << insertionSortTime.count() << " Nanoseconds" << endl;
    cout << "Merge Sort Time: " << mergeSortTime.count() << " Nanoseconds" << endl;
    cout << "Heap Sort Time: " << heapSortTime.count() << " Nanoseconds" << endl;
    cout << endl;
    cout<<"Searching for "<<query<<endl;
    cout << "======================================" << endl;


    int N = 100; // Number of iterations
    string upperCaseQuery = toUpper(query);

    // Binary search
    auto binaryStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        binarySearch(book, query);
    }
    auto binaryEnd = chrono::high_resolution_clock::now();
    auto binaryTotalTime = chrono::duration_cast<chrono::nanoseconds>(binaryEnd - binaryStart).count() / static_cast<double>(N);

    // since we are comparing the search times for the binary search and sequential serch in the functions, program encounters a break statement on first found
    // so we are printing outputs on normal sequential search function named outputs
    vector<info> result = outputs(bookQuickSort, query);
    if (result.empty()) {
        cout << upperCaseQuery << " does NOT exist in the dataset" << endl;
    }



    for (int k = 0; k<result.size(); k++) {
        string upperCaseName = toUpper(result[k].fullName);
        // Convert full name to uppercase

        cout << upperCaseName << " " << result[k].telNo << " " << result[k].city << endl;
    }

    cout << "Binary Search Time: " << binaryTotalTime << " Nanoseconds" << endl;
    
    
    
    cout << endl;
    cout << "Search results for Sequential Search:" << endl;
    // Sequential search
    auto sequentialStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sequentialSearch(book, query);
    }

    
    auto sequentialEnd = chrono::high_resolution_clock::now();
    auto sequentialTotalTime = chrono::duration_cast<chrono::nanoseconds>(sequentialEnd - sequentialStart).count() / static_cast<double>(N);
    if (result.empty()) {
        cout << upperCaseQuery << " does NOT exist in the dataset" << endl<<endl;
    }

    for (int k = 0; k<result.size(); k++) {
        string upperCaseName = toUpper(result[k].fullName);
        // Convert full name to uppercase

        cout << upperCaseName << " " << result[k].telNo << " " << result[k].city << endl;
    }

    cout << "Sequential Search Time: " << sequentialTotalTime << " Nanoseconds" << endl << endl;
    
    
    
    cout << "SpeedUp between Search Algorithms" << endl;
    cout << "======================================" << endl;
    if (sequentialTotalTime < binaryTotalTime) {
        cout << "Binary Search/Sequantial Search Speedup = " << binaryTotalTime /sequentialTotalTime;
    }
    else {
        cout << "(Sequential Search/ Binary Search) SpeedUp = " << sequentialTotalTime / binaryTotalTime;
    }
    cout << endl;
    cout << endl;
    cout << "SpeedUps between Sorting Algorithms" << endl;
    cout << "======================================" << endl;
    // Find the minimum time

    cout << "\n(Insertion Sort/Quick Sort) Speed Up : " << double(insertionSortTime.count()) / double(quickSortTime.count());
    cout << "\n(Merge Sort/Quick Sort) Speed Up : " << double(mergeSortTime.count()) / double(quickSortTime.count());
    cout << "\n(Heap Sort/Quick Sort) Speed Up : " << double(heapSortTime.count()) / double(quickSortTime.count()) << endl;



    return 0;
}


