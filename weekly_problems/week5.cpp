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

// CHALLENGE
// 2D Matrix class
template<typename T>
class Matrix {
private: 
    std::vector<std::vector<T>> m_data;

public: 
    Matrix() : m_data({{}}) {}

    Matrix(size_t y, size_t x) : m_data(y, std::vector(x)) {}

    Matrix(size_t y, size_t x, const T& defaultVal) 
        : m_data(y, std::vector(x, defaultVal)) {}

    // Returns the number of rows in the matrix
    size_t rows() const {
        return m_data.size();
    }

    // Returns the number of columns in the matrix
    size_t cols() const {
        return m_data[0].size();
    }

    // Returns the last row 
    size_t maxRow() const {
        return std::max(0, rows() - 1);
    }

    // Returns the last column
    size_t maxCol() const {
        return std::max(static_cast<size_t>(0), cols() - 1);
    }

    // Returns the element at coordinates (y, x)
    T getElement(size_t y, size_t x) const {
        if (y > maxRow() || x > maxCol()) {
            throw std::invalid_argument("Invalid coordinates for getElement()");
        }
        return m_data[y][x];
    }

    void printRow(size_t y) const {
        if (m_data[y].size() == 0) {
            std::cout << "[]" << std::endl;
            return;
        }
        std::cout << "[";
        for (size_t x = 0 ; x < m_data[y].size() - 1 ; x++) {
            std::cout << m_data[y][x] << ", ";
        }
        std::cout << m_data[y][m_data[y].size()-1] << "]" << std::endl;
    }

    void print() const {
        std::cout << "**MATRIX** \n";
        for (size_t y = 0 ; y < rows() ; y++) {
            printRow(y);
        }
    }

};


int main() {
    Matrix<int> m(5, 3, 2);

    m.print();
}
