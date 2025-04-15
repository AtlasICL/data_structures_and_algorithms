/**
 * Problem Week 5: 
 * 
 * Implement a program to rotate a 1D array to the right
 * by k positions using extra memory.
 * 
 * Challenge: Implement a dynamic 2D matrix with operations for
 * insertion, deletion, resizing rows and columns, and 
 * accessing elements efficiently.
 */

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

// rotates the vector right by k positions, returns a new (rotated) vector
// @throws invalid_argument if vector is empty or k is negative
template<typename T>
std::vector<T> rotateRight(const std::vector<T>& vec, int k) {

    if (vec.empty()) { throw std::invalid_argument("Cannot call rotate with empty vector"); }
    
    if (k < 0) { throw std::invalid_argument("Cannot call rotate with negative k"); }

    // instantiate the vector `rotated` with the same size as original vector 
    std::vector<T> rotated(vec.size());

    for (size_t i = 0; i < vec.size(); i++) {
        rotated[(i + k) % vec.size()] = vec[i];
    }

    return rotated;
} 

int main() {

    std::vector<std::string> myVec = {"a", "b", "c", "d", "e"}; // initial vector
    
    // print initial vector
    auto printVec = [](const auto& vec) {
        for (int i = 0 ; i < vec.size() ; i++) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    };
    printVec(myVec);

    myVec = rotateRight(myVec, 2); // rotate right by 2 places
    // print rotated vector:
    printVec(myVec);
}