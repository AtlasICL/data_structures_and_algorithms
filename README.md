# Some of my work for the module ECM1414 - Data Structures and Algorithms

- **Data structures / algorithms implemented:**
  - [Trees](#trees)
  - [Graphs](#graphs)
  - [Queues](#queues)
  - [Arrays](#arrays)
  - [Linked lists](#linked-lists)
  - [Stacks](#stacks)
- [Workshop suggested programs:](#workshop-suggested-programs)

---

## Trees

| Data structure | Binary search tree                                       | AVL tree                                                                                                        | Red-black tree |
| -------------- | -------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- | -------------- |
| **Features**       | - insertion <br> - deletion <br> - efficient search <br> | - insertion <br> - deletion <br> - efficient search <br> - self-balancing, using node height and balance factor | WIP            |
| **Algorithms**     | - in-order traversal <br> - pre-order traversal          | - in-order traversal <br> - pre-order traversal                                                                 | WIP            |

## Graphs 

| Data structure | Directed graph                                   | Undirected graph                                 | Weighted undirected graph                                                          |
| -------------- | ------------------------------------------------ | ------------------------------------------------ | ---------------------------------------------------------------------------------- |
| **Features**       | - directed graph using an adjacency list         | - undirected graph using an adjacency list       | - weighted undirected graph using a `struct Edge` and an `std::vector<Edge> edges` |
| **Algorithms**     | - Depth-first search <br> - Breadth-first search | - Depth-first search <br> - Breadth-first search | - Kruskal's algorithm, for finding MST or MSF                                      |

## Queues

| Data structure | Queue                                                                                                                                                                                           | Deque (double-ended queue)                                                                                                                     |
| -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| **Features**       | - queue template class, implement using linked list structure <br> - destructor to free memory; copy constructor for deep copy; assignment operator <br> - methods for enqueue, dequeue and top | - deque template class with same features <br> - insertion at head and tail <br> - methods for getHead and getTail <br> - pop at head and tail |

## Arrays 

| Data structure | Dynamic array                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        | std::vector                                |
| -------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------ |
| **Features**       | - dynamically allocated array using contiguous memory <br> - constructors: overloads for constructing array at a given size, and with specific default values <br> destructor to free memory, copy constructor for deep copy, assignment operator <br> - string conversion operator for printing <br> - checking if the array contains a value / find first occurrence / find all occurrences <br> - method for appending (push_back) <br> - deletion of first or all instances of a given value <br> - deletion at a specific index | (Standard template library implementation) |
| **Algorithms**    |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      | - bubble sort <br> - insertion sort        |

## Linked lists

| Data structure | Linked list                                                                                                                                                                                                                                                                                                                                                  | Circular linked list                     |
| -------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------- |
| **Features**      | - linked list template class <br> - constructor overload for creating a linked list from a vector <br> - destructor to free memory; copy constructor for deep copy; assignment operator <br> - insertion at head, tail, and a specific index <br> - deleting first / all ocurrences of an element <br> - counting instances / counting nodes <br> - printing |
| **Algorithms**    | reversal in-place                                                                                                                                                                                                                                                                                                                                            | Josephus election (with optional offset) |

## Stacks

| Data structure | Stack                        |
| -------------- | ---------------------------- |
| **Features**       | - push <br> - pop <br> - top |


---


# Workshop suggested programs:

The problem sheet is located [here](weekly_problems/weekly_problems.pdf).

- [x] Week 1
- [x] Week 2
- [x] Week 3
- [x] Week 4 (TODO: Challenge)
- [x] Week 5
- [x] Week 6
- [x] Week 7
- [x] Week 8 (TODO: Challenge)
- [x] Week 9
- [x] Week 10 (TODO: Challenge)
- [ ] Week 11


