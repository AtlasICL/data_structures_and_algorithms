/**
 * Problem Week 1:
 * 
 * Write a function to compute the Fibonacci sequence iteratively.
 * Write a function to compute the Fibonacci sequence recursively.
 * 
 * Challenge: implement memoization for the recursive function.
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

// returns the nth fibonacci number, iteratively calculated
int fib_iterative(int n) {
    if (n <= 0) { throw std::invalid_argument("Defined for n > 0"); }

    if (n == 1 || n == 2) {
        return 1;
    }

    int prev = 1;
    int curr = 1;
    int idx = 2;

    while (idx < n) {
        int tmp_prev = prev;
        prev = curr;
        curr = tmp_prev + curr;
        idx++;
    }

    return curr;
}

// returns the nth fibonacci number, recursively calculated
int fib_recursive(int n) {
    if (n <= 0) { throw std::invalid_argument("Defined for n > 0"); }

    if (n == 1 || n == 2) {
        return 1;
    }
    return fib_recursive(n-1) + fib_recursive(n-2);
}
