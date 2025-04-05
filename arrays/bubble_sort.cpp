/**
 * Implementation of the bubble sort algorithm.
 */

#include <vector>
#include <stdexcept>

template<typename T>
class BubbleSorter {

public:

    // sorts the vector in-place
    static void sort(std::vector<T>& array_to_sort) {
        return bubble_sort(array_to_sort);
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

