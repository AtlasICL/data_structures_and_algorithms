/**
 * Problem Week 1:
 * Write a function to compute the Fibonacci sequence iteratively.
 * Write a function to compute the Fibonacci sequence recursively.
 * Then implement memoization for the recursive function.
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


// helper function which handles the recursive part of the memoized version
int fib_memo_helper(int n, std::unordered_map<int, int>& memo) {
    if (memo.count(n) > 0) {
        return memo[n];
    }

    if (n == 1 || n == 2) {
        return 1;
    }

    memo[n] = fib_memo_helper(n-1, memo) + fib_memo_helper(n-2, memo); // instead of returning this directly, we save it
    return memo[n]; // then we return
}


// returns the nth fibonacci number, calculated recursively with memoization
int fib_recursive_memoized(int n) {
    if (n <= 0) { throw std::invalid_argument("Defined for n > 0"); }

    std::unordered_map<int, int> memo;

    return fib_memo_helper(n, memo);
}
