# Comparison of number of operations in a
# sequantial search over an unsorted array

import random

array_to_search: list[int] = [random.choice(range(1, 250)) for _ in range(100)]

numbers_to_search_for: list[int] = [random.choice(array_to_search) for _ in range(3)]

def search_and_count(array: list[int], n: int) -> int:
    """
    Searches for element with value n in array.
    Returns the number of operations to find n.
    """
    comparison_counter: int = 0
    for element in array:
        comparison_counter += 1
        if element == n:
            return comparison_counter
    return -1


def week2_problem():
    for num in numbers_to_search_for:
        print(f"-- Searching for {num} --")
        ops: int = search_and_count(array_to_search, num)
        print(f"Found in {ops} operations")


if __name__ == "__main__":
    main()
