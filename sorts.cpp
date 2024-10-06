
//
//  sorts.cpp
//  Cs300_hw4
//
//  Created by Mehmet Egehan Pala on 22.05.2024.
//





#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <algorithm>



using namespace std;

struct info {
    string name; // Separate name and surname
    string surname;
    string telNo;
    string city;
    string fullName; // Combined name and surname


    info(){}
    info(string &n, string &s, string &t, string &c): name(n), surname(s), telNo(t), city(c)
    {
        fullName = (name + " " + surname);
    }
    bool operator<(const info& rhs) const {
        return (fullName < rhs.fullName);
    }
    bool operator>(const info& rhs) const {
        return (fullName > rhs.fullName);
    }
};


//--------------------------------------------- INSERTION SORT: FROM THE DATA STRUCTURES BOOK AND LECTURE SLIDES  ------------------------------------------------------

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
	for (int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 &&  tmp < a[j - 1]; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}


//--------------------------------------------- HEAP SORT: FROM THE DATA STRUCTURES BOOK AND LECTURE SLIDES  ------------------------------------------------------

inline int leftChild(int i)
{
    return 2 * i + 1;
}

template <class Comparable>
void percDown(vector<Comparable> & a, int i, int n)
{
    int child;
    Comparable tmp;

    for(tmp = move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if(child != n - 1 && a[child] < a[child + 1])
            ++child;
        if(tmp < a[child])
            a[i] = move(a[child]);
        else
            break;
    }
    a[i] = move(tmp);
}


template <class Comparable>
void heapsort(vector<Comparable> & a)
{
    for(int i = a.size() / 2 - 1; i >= 0; --i) /* buildHeap */
        percDown(a, i, a.size());
    for(int j = a.size() - 1; j > 0; --j)
    {
        swap(a[0], a[j]); /* deleteMax */
        percDown(a, 0, j);
    }
}

//--------------------------------------------- MERGE SORT: FROM THE DATA STRUCTURES BOOK AND LECTURE SLIDES  ------------------------------------------------------

template <class Comparable>
void mergeSort(vector<Comparable>& a) {
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}

/**
 * Internal method that makes recursive calls.
 * a is a vector of Comparable items.
 * tmpArray is a vector to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is a vector of Comparable items.
 * tmpArray is a vector to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <class Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos].fullName <= a[rightPos].fullName)
            tmpArray[tmpPos++] = move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = move(a[rightPos++]);
    }

    // Copy rest of first half
    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = move(a[leftPos++]);

    // Copy rest of right half
    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = move(tmpArray[rightEnd]);
}

//--------------------------------------------- QUICK SORT: FROM THE DATA STRUCTURES BOOK AND LECTURE SLIDES  ------------------------------------------------------
/*
template <class Comparable>
inline void swap( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}
*/

template <class Comparable>
void quicksort(vector<Comparable> & a)
{
    quicksort(a, 0, a.size() - 1);
}

template <class Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
    int center = (left + right) / 2;

    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    // Place pivot at position right - 1
    swap(a[center], a[right - 1]);
    return a[right - 1];
}

template <class Comparable>
void quicksort(vector<Comparable> & a, int left, int right)
{
    if (left + 10 <= right)
    {
        const Comparable & pivot = median3(a, left, right);

        // Begin partitioning
        int i = left + 1, j = right - 2;
        for (;;)
        {
            while (a[i] < pivot)
                i++;
            while (a[j] > pivot)
                j--;
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }


        swap(a[i], a[right - 1]); // Restore pivot

        quicksort(a, left, i - 1);  // Sort small elements
        quicksort(a, i + 1, right); // Sort large elements
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}
