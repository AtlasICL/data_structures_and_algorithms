/**
 * Week 3 Problem:
 * 
 * Write a function to compute the number of comparisons in
 * bubble sort for a given array size.
 */

#include <vector>
#include <stdexcept>
#include <iostream>
#include <random>

template<typename T>
class BubbleSorter {

public:

    // sorts the vector in-place
    static void sort(std::vector<T>& array_to_sort) {
        return bubble_sort(array_to_sort);
    }

    static int sortWithPerfCounter(std::vector<T>& array_to_sort) {
        return bubble_sort_with_perf_counter(array_to_sort);
    }

private:

    // private method implementation
    static void bubble_sort(std::vector<T>& array) {
        bool swapped;

        do {
            swapped = false;
            for (int i = 0; i < array.size() - 1; i++) {
                if (array[i] > array[i+1]) {
                    swapElements(array, i, i+1);
                    swapped = true;
                }
            }
        } while (swapped);

    }

    static int bubble_sort_with_perf_counter(std::vector<T>& array) {
        bool swapped;
        int perf_counter = 0;

        do {
            swapped = false;
            for (int i = 0; i < array.size() - 1; i++) {
                if (array[i] > array[i+1]) {
                    perf_counter++;
                    swapElements(array, i, i+1);
                    swapped = true;
                }
            }
        } while (swapped);

        return perf_counter;
    }

    // returns true if the array is sorted, false otherwise
    static bool isSorted(const std::vector<T>& array) {
        for (int i = 0; i < array.size() - 1; i++) {
            if (array[i] > array[i+1]) {
                return false;
            }
        }
        return true;
    }

    // swaps the elements at indices idxa and idxb
    // @throws out_of_range error if idxa or idxb are not within the bounds of the array
    static void swapElements(std::vector<T>& array, int idxa, int idxb) {

        if (idxa < 0 || idxa >= array.size() || idxb < 0 || idxb >= array.size()) {
            throw std::out_of_range("invalid index passed into swapElements");
        }

        T tmp = array[idxa];
        array[idxa] = array[idxb];
        array[idxb] = tmp;
    }

    // prevent instantiation
    BubbleSorter() = delete;

};

template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << "]" << std::endl;
}


int main() {
    std::vector<int> vec(20);

    // generate 100 random integers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 250);

    for (int i = 0; i < vec.size(); i++) {
        vec[i] = dist(gen);
    }

    std::cout << "-- Before sorting: --" << std::endl;
    printVector(vec);
    
    // sort, and record comparisons
    int perfCounter = BubbleSorter<int>::sortWithPerfCounter(vec);

    std::cout << "-- After sorting: -- " << std::endl;
    printVector(vec);
    std::cout << "Number of comparisons: " << perfCounter << std::endl;

}