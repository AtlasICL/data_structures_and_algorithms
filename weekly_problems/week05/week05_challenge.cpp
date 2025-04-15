#include <iostream>
#include <vector>

// CHALLENGE
// 2D Matrix class
template<typename T>
class Matrix {
private: 
    std::vector<std::vector<T>> m_data;

    // Returns the last row 
    size_t maxRow() const {
        return rows() == 0 ? 0 : rows() - 1;
    }

    // Returns the last column
    size_t maxCol() const {
        return cols() == 0 ? 0 : cols() - 1;
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
        std::cout << m_data[y][maxCol()] << "]" << std::endl;
    }

public: 
    Matrix(size_t y, size_t x) : m_data(y, std::vector<T>(x)) {}

    Matrix(size_t y, size_t x, const T& defaultVal) 
        : m_data(y, std::vector<T>(x, defaultVal)) {}

    // Returns the number of rows in the matrix
    size_t rows() const {
        return m_data.size();
    }

    // Returns the number of columns in the matrix
    size_t cols() const {
        return m_data.empty() ? 0 : m_data[0].size();
    }

    // Returns the element at coordinates (y, x)
    T getElement(size_t y, size_t x) const {
        if (y > maxRow() || x > maxCol()) {
            throw std::invalid_argument("Invalid coordinates for getElement()");
        }
        return m_data[y][x];
    }

    // resizes the matrix such that it will have newRowCount rows
    // if newRowCount is less than the current number of rows, the extra rows will be deleted, starting from the bottom (greatest y coordinate)
    // if newRowCount is greater than the current number of rows, the new rows will be initialized to the default value
    void resizeRows(size_t newRowCount) {
        if (newRowCount == rows()) {
            return; // no modification necessary
        }
        // case where we need to add new rows
        else if (newRowCount > rows()) {
            for (size_t y = rows() ; y < newRowCount ; y++ ) {
                m_data.push_back(std::vector<T>(cols()));
            }
        }
        // case where we need to delete rows
        else if (newRowCount < rows()) {
            size_t rowsToDelete = rows() - newRowCount;
            for (size_t deletionCounter = 0 ; deletionCounter < rowsToDelete ; deletionCounter++ ) {
                m_data.pop_back();
            }
        }
    }

    // resizes the matrix such that it will have newColumnCount rows
    // if newColumnCount is less than the current number of columns, the extra columns will be deleted, starting 
    // from the rightmost column (greatest x coordinate)
    // if newColumnCount is greater than the current number of columns, the new columns will be initialized to the default value
    // and added at the right (greatest x coordinate)
    void resizeCols(size_t newColumnCount) {
        if (newColumnCount == cols()) {
            return; // no modification necessary
        }
        // case where we need to add new columns
        else if (newColumnCount > cols()) {
            size_t colsToAdd = newColumnCount - cols();
            for (size_t y = 0 ; y < rows() ; y++ ) {
                m_data[y].insert(m_data[y].end(), colsToAdd, T());
            }
        }
        // case where we need to remove (delete) columns
        else if (newColumnCount < cols()) {
            size_t colsToDelete = cols() - newColumnCount;
            for (size_t y = 0 ; y < rows() ; y++) {
                for (size_t deletionCounter = 0 ; deletionCounter < colsToDelete ; deletionCounter++ ) {
                    m_data[y].pop_back();
                }
            }
        }
    }

    // prints the matrix 
    void print() const {
        std::cout << "** " << rows() << " by " << cols() << " MATRIX ** \n";
        for (size_t y = 0 ; y < rows() ; y++) {
            printRow(y);
        }
    }

};


int main() {
    Matrix<int> m(5, 3, 2);

    m.print();

    m.resizeCols(10);

    m.print();


}
