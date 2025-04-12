/**
 * Problem Week 8:
 * 
 * Write a program to sort an array of integers using insertion sort.
 * Print the sorted array.
 * 
 * Challenge: implement a hybrid sorting algorithm that switches from
 * merge sort to insertion sort when the subarray size falls below a
 * threshold (e.g. k=10).
 * Compare its performance with plain merge sort.
 */

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


// returns true if provided array is sorted
bool sorted(const std::vector<int>& array) {
    if (array.empty() || array.size() == 1) { return true; } 

    for (int i = 0; i < array.size() - 1; i++) {
        if (array[i] > array[i+1]) { 
            return false;
        }
    }
    return true;
}


// returns true if array[idx] <= array[idx+1]
// if idx == array.size() - 1, returns true by default
// @throws out_of_range error if idx < 0 or idx > array.size() - 1
bool isOrderedAtIndex(const std::vector<int>& array, int idx) { 
    if (idx < 0 || idx > array.size() - 1) { throw std::out_of_range("Out of range"); }

    if (idx == array.size() - 1) {
        return true;
    }

    return array[idx] <= array[idx + 1];
}


// switches the element at idx with idx - 1
void switchElements(std::vector<int>& array, int idx) {
    if (idx == 0) { throw std::out_of_range("called switchElements with idx 0"); }
    if (idx > array.size() - 1) { throw std::out_of_range("called switchElements with idx > size-1"); }

    int l_tmp = array[idx-1];
    array[idx-1] = array[idx];
    array[idx] = l_tmp;
}


void swapUntilInserted(std::vector<int>& array, int idx) {

    if (isOrderedAtIndex(array, idx - 1)) {
        return;
    }

    int i = idx;
    do {
        switchElements(array, i);
        i--;
    } while (i > 0 && !isOrderedAtIndex(array, i - 1));
}


// implements the insertion sort algorithm
void insertionSort(std::vector<int>& array) {
    if (array.empty()) { return; } // do nothing for an empty array

    for (int idx = 0; idx < array.size() - 1; idx++) {
        if (!isOrderedAtIndex(array, idx)) {
            swapUntilInserted(array, idx + 1);
        }
    }
}


// prints an std::vector
template<typename T>
void printVector(const std::vector<T>& array) {
    std::cout << "[ ";
    for (const auto& element : array) {
        std::cout << element << " "; 
    }
    std::cout << "]\n";
}

int main() {
    
    std::vector<int> a = {8, 5, 7, 2, 1, 9, 3};
    insertionSort(a);

    std::vector<int> b = {};
    insertionSort(b);

    std::vector<int> c = {0};
    insertionSort(c);

    std::vector<int> d = {0, -1};
    insertionSort(d);

    std::vector<int> e = {0, -1, 0};
    insertionSort(e);

    std::vector<int> f = {-1, -1, 0, 0, -1};
    insertionSort(f);

    std::vector<int> g = {1, 2, 3, 2, 2, 2, 5, 3, 6, 7, 9, 3, 4, 0, 1, 0, -4};
    insertionSort(g);


    printVector(a);
    printVector(b);
    printVector(c);
    printVector(d);
    printVector(e);
    printVector(f);
    printVector(g);

}

