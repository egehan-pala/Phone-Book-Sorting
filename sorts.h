// sorting.h


//
//  sorts.h
//  Cs300_hw4
//
//  Created by Mehmet Egehan Pala on 22.05.2024.
//

#ifndef SORTS_H
#define SORTS_H

#include <vector>

using namespace std;

template <class Comparable>
void insertionSort (vector <Comparable> & a);

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right );

inline int leftChild(int i);

template <class Comparable>
void percDown(vector<Comparable> & a, int i, int n);

template <class Comparable>
void heapsort(vector<Comparable> & a);

template <class Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right);

template <class Comparable>
void mergeSort(vector<Comparable>& a);

template <class Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd);

template <class Comparable>
void quicksort(vector<Comparable> & a);

template <class Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right);

template <class Comparable>
void quicksort(vector<Comparable> & a, int left, int right);


#include "sorts.cpp"

#endif // SORTS_H
