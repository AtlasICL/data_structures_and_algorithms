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