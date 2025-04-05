/**
 * Implementation of the quicksort algorithm.
 */

#include <vector>
#include <iostream>
#include <string>


template<typename T>
class QuickSorter {

public:
    static void sort(std::vector<T> array) {
        quicksort(array);
    }

    // @returns true if the vector is sorted, false otherwise
    static bool isSorted(const std::vector<T>& array) {
        if (array.empty() || array.size() == 1) {
            return true;
        }

        for (int i = 0; i < array.size() - 1; i++) {
            if (array[i] > array[i+1]) {
                return false;
            }
        }
        return true;
    }

private:

    static void quicksort(std::vector<T>& array) {

        // if array is empty, or has one single element, it is sorted 
        if (array.empty() || array.size() == 1) {
            return;
        }

        // choose a pivot 
        int pivot = array.size() / 2;

        


    }




};