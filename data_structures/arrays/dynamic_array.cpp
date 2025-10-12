/**
 * An implementation of a dynamic, heap-allocated array.
 * Dynamic contiguous memory. 
 */

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

// computes the smallest power of two not less than n for 32-bit unsigned integers
constexpr unsigned int bit_ceil(unsigned int n) {
    if (n <= 1) { return 1; }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}


template<typename T>
class Vec {
private:
    size_t m_size;
    size_t m_capacity;
    T* m_data;
    static const size_t MIN_CAPACITY = 1;
    static const unsigned int GROWTH_FACTOR = 2;
    static const unsigned int SHRINK_FACTOR = 2;
    static const unsigned int CONTRACTION_THRESHOLD = 4;

    // checks whether a shrink of the allocated memory is necessary, and performs it if it is
    void shrink_if_necessary() {
        if (m_capacity > MIN_CAPACITY && m_size <= m_capacity / CONTRACTION_THRESHOLD) {
            size_t new_capacity = m_capacity / 2;

            T* new_data = new T[new_capacity];
            for (size_t i = 0 ; i < m_size ; i++) {
                new_data[i] = std::move(m_data[i]);
            }
    
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
    }

public:
    Vec() : m_size(0), m_capacity(MIN_CAPACITY) {
        m_data = new T[m_capacity];
    }

    Vec(size_t initial_size, const T& initial_val)
        : m_size(initial_size), m_capacity(bit_ceil(initial_size)) {
        m_data = new T[m_capacity];
        for (size_t i = 0 ; i < initial_size ; i++) {
            m_data[i] = initial_val;
        }
    }

    ~Vec() {
        delete[] m_data;
    }

    // copy constructor for deep copy
    Vec(const Vec& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_data = new T[m_capacity];
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }

    // assignment operator
    Vec& operator=(const Vec& other) {
        // check for self-assignment
        if (this == &other) {
            return *this;
        }

        Vec tmp(other); // create a copy using the copy constructor
        std::swap(m_size, tmp.m_size);
        std::swap(m_capacity, tmp.m_capacity);
        std::swap(m_data, tmp.m_data);
        return *this;
    }

    // Check if the vector contains a value
    // @returns Returns true if an element with value val exists in the vector
    // @returns Returns false otherwise
    bool contains(const T& val) const {
        for (size_t i = 0 ; i < m_size ; i++) {
            if (m_data[i] == val) { return true; }
        }
        return false;
    }

    // Finds the index of a value in the vector 
    // @returns Returns the index of the first occurrence of val
    // @returns Returns -1 if val does not exist in the vector
    int find_first(const T& val) const {
        for (size_t i = 0 ; i < m_size ; i++) {
            if (m_data[i] == val) { return i; }
        }
        return -1;
    }

    // Finds all indices of a value in the vector
    // @returns Returns an std::vector with the indices of the val
    // @returns Returns an empty array if the val does not occur in the vector
    std::vector<size_t> find_all(const T& val) const {
        std::vector<size_t> idxs = {};
        for (size_t i = 0 ; i < m_size ; i++) {
            if (m_data[i] == val) { idxs.push_back(i); } 
        }
        return idxs;
    }

    // Appends an element to the back of the array
    void push_back(const T& val) {
        if (m_size == m_capacity) {
            m_capacity = m_capacity * GROWTH_FACTOR;
            T* tmp = new T[m_capacity];
            for (size_t i = 0; i < m_size ; i++) {
                tmp[i] = m_data[i];
            }
            delete[] m_data;
            m_data = tmp;
        }

        m_data[m_size] = val;
        m_size++;
    }

    // deletes the element at the given index
    // @throws out_of_range if provided idx is out of range
    void delete_at_index(size_t idx) {
        if (idx >= m_size) { throw std::out_of_range("Index out of range for deletion"); }
        for (size_t ptr = idx ; ptr < m_size - 1 ; ptr++) {
            m_data[ptr] = m_data[ptr+1];
        }
        m_size--;
        shrink_if_necessary();
    }

    // deletes the first instance of the value val, if it exists
    // @returns Returns true if a deletion occurred
    // @returns false otherwise.
    bool delete_first_instance(const T& val) {
        for (size_t idx = 0 ; idx < m_size ; idx++) {
            if (m_data[idx] == val) {
                delete_at_index(idx);
                return true;
            }
        }
        return false;
    }

    // deletes all instances of the value val, if it exists
    // @returns Returns the number of deletions which occurred
    int delete_all_instances(const T& val) {
        int deletionCounter = 0;
        for (size_t idx = 0 ; idx < m_size; ) {
            if (m_data[idx] == val) {
                delete_at_index(idx);
                deletionCounter++;
            }
            else { idx++; } // increment only if no deletion occurred
        }
        return deletionCounter;
    }

    // @overload Overload for the stream insertion operator, to print the contents of vec object
    friend std::ostream& operator<<(std::ostream& os, const Vec<T>& vec) {
        os << "******** VEC ********\n";
        os << "m_size = " << vec.m_size << " | m_capacity = " << vec.m_capacity << std::endl;
        if (vec.m_size <= 0) {
            os << "[]\n" << std::endl;
            return os;
        }
        if (vec.m_size == 1) {
            os << "[" << vec.m_data[0] << "]\n" << std::endl;
            return os;
        }
        os << "[";
        for (size_t i = 0; i < vec.m_size - 1; i++) {
            os << vec.m_data[i] << ", ";
        }
        os << vec.m_data[vec.m_size - 1];
        os << "]\n" << std::endl;
        return os;
    }

};




int main() {
    Vec<int> v(14, 5);
    std::cout << v;

    v.push_back(2);
    v.push_back(3);
    std::cout << v;

    v.push_back(4);
    std::cout << v;

    Vec<int> vCopy = v;

    v.delete_at_index(2);
    std::cout << v;

    v.delete_at_index(15);
    std::cout << v;

    v.delete_at_index(13);
    std::cout << v;

    for (int i = 0 ; i < 10 ; i++) {
        v.delete_at_index(0);
        std::cout << "Deleting iter = " << i + 1 << std::endl;
        std::cout << v;
    }

    std::cout << vCopy;
}