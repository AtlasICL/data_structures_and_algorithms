#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <utility>


template<typename T>
struct ListNode {
    T val;
    ListNode<T>* nextNode;

    ListNode(T v, ListNode<T>* next) : val(v), nextNode(next) {}

    // explicit conversion operator to convert a ListNode object to a string
    // debugging function, produces output of type [ListNode | addr: 0xffff val: {value}]
    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[ListNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};

template<typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    LinkedList(const std::vector<T>& values) {
        this->createList(values);
    }

    // destructor should deallocate all memory used by the list
    ~LinkedList() {
        ListNode<T>* current = head;
        ListNode<T>* tmp;

        while (current != nullptr) {
            tmp = current->nextNode;
            delete current;
            current = tmp;
        }
    }

    // copy constructor - we want to implement deep copy instead of shallow copy
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
        for (ListNode<T>* current = other.head; current != nullptr; current = current->nextNode) {
            insertAtTail(current->val);
        }
    }

    // assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {        // check we are not doing a = a, in which case no work needs to be done
            LinkedList tmp(other);   // create a temporary copy of the "copied" instance
            swap(tmp);               // swap the contents of this object with temporary copy
        }
        return *this;
    }



    // this function creates a linked list with the values provided by the vector argument
    void createList(const std::vector<T>& values) {
        head = nullptr;
        tail = nullptr;

        for (const T& value : values) {
            ListNode<T>* newNode = new ListNode<T>(value, nullptr);

            // if the list is empty, this created new node becomes both the head and the tail
            // as it is the only node in the list
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                // otherwise, we append the node to the end of the list
                tail->nextNode = newNode;
                tail = newNode;
            }
        }
    }

    // this function returns the number of nodes in the linked list
    int countNodes() const {
        int nodeCount = 0;
        ListNode<T>* ptr = head;
        while (ptr != nullptr) {
            nodeCount++;
            ptr = ptr->nextNode;
        }
        return nodeCount;
    }

    // this function inserts a node at the head of the linked list
    void insertAtHead(const T v) {
        // if the list is empty, we set both head and tail to be this new node
        if (head == nullptr) {
            ListNode<T>* tmp = new ListNode<T>(v, nullptr);
            this->head = tmp;
            this->tail = tmp;
            return;
        }

        // otherwise we add a new node, which has next = head, then we update head
        ListNode<T>* tmp = new ListNode<T>(v, head);
        this->head = tmp;
    }

    // this function inserts a node at the tail of the linked list
    void insertAtTail(const T v) {
        // if the list is empty, we set both head and tail to be this new node
        if (head == nullptr) {
            ListNode<T>* tmp = new ListNode<T>(v, nullptr);
            this->head = tmp;
            this->tail = tmp;
            return;
        }

        // otherwise we add a new node, which has next = nullptr, as it as the tail
        // we link the new node to the previous tail, then we update tail
        ListNode<T>* tmp = new ListNode<T>(v, nullptr);
        this->tail->nextNode = tmp;
        this->tail = tmp;
    }

    // this function inserts a node at a specified index of the linked list
    void insertAtIndex(const T v, const int idx) {
        // check provided index is positive
        if (idx < 0) {
            throw std::invalid_argument("Negative index not allowed.");
        }
        // check provided index is not bigger than length of the list
        // list is 0-indexed, so we use >=
        if (idx > this->countNodes()) {
            throw std::out_of_range("index is out of range for insertion.");
        }

        // body of the function for insertion

        // if insertion at idx 0, special case insert at head
        if (idx == 0) {
            insertAtHead(v);
            return;
        }

        // if insertion is at the tail, special case
        if (idx == countNodes()) {
            insertAtTail(v);
        }

        // traverse to the node at idx
        ListNode<T>* current = head;
        for (int i = 0; i < idx - 1; ++i) {
            current = current->nextNode;
        }

        ListNode<T>* tmp = new ListNode<T>(v, current->nextNode);
        current->nextNode = tmp;
        
        // if idx was the last element, update tail
        if (current == tail) {
            tail = tmp;
        }
    }

    // this function returns true if the linked list contains a node with the value v
    // false otherwise
    bool contains(const T v) const {
        if (head == nullptr) {
            // the list is empty, and therefore definitely does not contain the value v
            return false;
        }

        ListNode<T>* current = head;

        // iterate through the nodes
        while (current != nullptr) {
            if (current->val == v) {
                return true;
            }
            current = current->nextNode;
        }
        return false;
    }

    // this function deletes the first instance of a value in the linked list
    // returns true if a deletion occurred, else false (the value was not found in the list)
    bool deleteFirstInstance(const T v) {
        
        // if the list is empty, we do not delete anything, hence return false
        if (head == nullptr) {
            return false;
        }

        // check the case where head contains the target value
        if (head->val == v) {
            ListNode<T>* tmp = head;
            head = head->nextNode;

            if (head == nullptr) {
                // if the list becomes empty after the deletion we need to update tail to be null too
                // otherwise tail will point to a deleted node, which causes undefined behaviour
                tail = nullptr;
            }

            delete tmp; // free the memory of the deleted node
            return true; // return true as a deletion did take place
        }

        // traverse the list
        ListNode<T>* current = head;
        while (current->nextNode != nullptr) {
            if (current->nextNode->val == v) {
                ListNode<T>* tmp = current->nextNode;
                current->nextNode = current->nextNode->nextNode;

                if (tmp == tail) {
                    tail = current;
                }

                delete tmp; // free the memory of the deleted node
                return true;
            }
            current = current->nextNode;
        }
        
        // if we have traversed the list without finding v, then the element was not present in the list
        // therefore we cannot delete, so we return false.
        assert(this->countInstances(v) == 0 && "check delete first instance");
        return false;
    }

    // this function deletes all instances of a value in the linked list
    void deleteAllInstances(const T v) {
        while (deleteFirstInstance(v)) {} // delete the first instance of v repeatedly, until it returns false
        // this implementation is not particularly efficient, as we traverse the list multiple times
        // this could be implemented with only one travesal of the list.
    }

    // this function returns the number of the nodes with the specified value
    int countInstances(const T v) const {
        int counter = 0; // counts the number of occurrences of v
        ListNode<T>* current = head;

        // traverse the list
        while (current != nullptr) {
            counter += current->val == v;
            current = current->nextNode;
        }

        return counter;
    }

    // this function reverses the order of the linked list in-place
    void reverse() {
        ListNode<T>* previous = nullptr;
        ListNode<T>* current = this->head;

        while (current != nullptr) {
            ListNode<T>* tmp = current->nextNode;  // save the next node
            current->nextNode = previous;       // reversal, current->next now points to its preceding node
            previous = current;                 // previous becomes current
            current = tmp;                      // current becomes next node
        }

        this->tail = this->head;   // the old tail becomes the head
        this->head = previous;     // the new head is the last node pointed to by previous (as current is null at end of while loop)
    }

    // this function prints the linked list to the terminal
    // with the mem addr and the value of each list node
    void print() const {
        if (head == nullptr) {
            std::cout << "Empty list" << std::endl;
            return;
        }
        
        // iterate through each node in the list
        for (ListNode<T>* current = head; current != nullptr; current = current->nextNode) {
            // using the explicit conversion operator to convert the node to a string
            std::cout << static_cast<std::string>(*current);
        }
    }

    // helper function to swap the internals of two LinkedList objects
    void swap(LinkedList& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
};