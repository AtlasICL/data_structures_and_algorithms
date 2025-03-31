# Week 2 challenge

import math
import time

input_sizes: list[int] = [100, 500, 1000, 5000]

def O_n(n: int) -> None:
    some_list = []
    i = 0
    while i < n:
        some_list.append(i)
        i += 1

def O_n_squared(n: int) -> None:
    some_list = []
    i = 0
    while i < n * n:
        some_list.append(i)
        i += 1

def O_n_logn(n: int) -> None:
    some_list = []
    i = 0
    while i < n * math.log10(n):
        some_list.append(i)
        i += 1

def measure_runtime_seconds(func, arg) -> float:
    """
    Measures the runtime of the given function with the given argument.
    """
    start_time = time.perf_counter()
    func(arg)
    end_time = time.perf_counter()

    return end_time - start_time


functions = [O_n, O_n_squared, O_n_logn]

for arg in input_sizes:
    for func in functions:
        runtime = measure_runtime_seconds(func, arg)
        print(f"{func.__name__} with input size {arg} took {runtime:.6f} seconds")

