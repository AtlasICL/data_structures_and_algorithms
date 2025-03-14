/**
 * An implementation of insertion sort.
 */

#include <vector>
#include <string>
#include <stdexcept>

// returns true if provided array is sorted
// @throws runtime_error if called with empty array
bool sorted(const std::vector<int>& array) {
    if (array.empty()) { throw std::runtime_error("called sorted() on empty array"); }

    if (array.size() == 1) { return true; } 

    for (int i = 0; i < array.size() - 1; i++) {
        if (array[i] > array[i+1]) { 
            return false;
        }
    }
    return true;
}


// returns true if array[idx] < array[idx+1]
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
// @throws invalid_argument if array is empty
void insertionSort(std::vector<int>& array) {
    if (array.empty()) { throw std::invalid_argument("Empty array"); }

    int idx = 0;

    while (idx < array.size() - 1) {
        if (!isOrderedAtIndex(array, idx)) {
            swapUntilInserted(array, idx + 1);
        }
        idx++;
    }
}