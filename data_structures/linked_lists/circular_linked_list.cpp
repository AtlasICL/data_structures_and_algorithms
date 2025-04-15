#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
struct ListNode {
    T val;
    ListNode<T>* nextNode;

    ListNode(T v, ListNode<T>* next) : val(v), nextNode(next) {}

    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[ListNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};

template<typename T>
class CircularLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;

public:
    CircularLinkedList() : head(nullptr), tail(nullptr) {}

    // Instantiates a circular linked list, with the initial values provided.
    CircularLinkedList(const std::vector<T>& values) : head(nullptr), tail(nullptr) {
        createList(values);
    }

    // Destructor: to prevent infinite loops, we break the circular link before deletion.
    ~CircularLinkedList() {
        if (head != nullptr) {
            tail->nextNode = nullptr;
        }
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* tmp = current->nextNode;
            delete current;
            current = tmp;
        }
    }

    // Copy constructor (deep copy)
    CircularLinkedList(const CircularLinkedList& other) : head(nullptr), tail(nullptr) {
        if (other.head != nullptr) {
            ListNode<T>* current = other.head;
            do {
                insertAtTail(current->val);
                current = current->nextNode;
            } while (current != other.head);
        }
    }

    // Assignment operator.
    CircularLinkedList& operator=(const CircularLinkedList& other) {
        if (this != &other) { // check for self-assignment
            CircularLinkedList tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // Creates a circular linked list from the provided vector.
    void createList(const std::vector<T>& values) {
        head = nullptr;
        tail = nullptr;
        for (const T& value : values) {
            insertAtTail(value);
        }
    }

    // Returns the number of nodes in the circular linked list.
    int countNodes() const {
        if (head == nullptr)
            return 0;
        int count = 0;
        ListNode<T>* current = head;
        do {
            count++;
            current = current->nextNode;
        } while (current != head);
        return count;
    }

    void insertAtHead(const T v) {
        ListNode<T>* newNode = new ListNode<T>(v, nullptr);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->nextNode = head;
        }
        else {
            newNode->nextNode = head;
            head = newNode;
            tail->nextNode = head;
        }
    }

    void insertAtTail(const T v) {
        ListNode<T>* newNode = new ListNode<T>(v, nullptr);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->nextNode = head;
        }
        else {
            newNode->nextNode = head;
            tail->nextNode = newNode;
            tail = newNode;
        }
    }

    void insertAtIndex(const T v, const int idx) {
        if (idx < 0)
            throw std::invalid_argument("Negative index not allowed.");
        int count = countNodes();
        if (idx > count)
            throw std::out_of_range("Index is out of range for insertion.");

        if (idx == 0) {
            insertAtHead(v);
            return;
        }
        if (idx == count) {
            insertAtTail(v);
            return;
        }

        ListNode<T>* current = head;
        for (int i = 0; i < idx - 1; ++i) {
            current = current->nextNode;
        }
        ListNode<T>* newNode = new ListNode<T>(v, current->nextNode);
        current->nextNode = newNode;
    }

    // Returns true if a node with the value v exists in the list, false otherwise.
    bool contains(const T v) const {
        if (head == nullptr)
            return false;

        ListNode<T>* current = head;
        do {
            if (current->val == v) {
                return true;
            }
            current = current->nextNode;
        } while (current != head);
        return false;
    }

    // Deletes the first instance of a node with the value v.
    // Returns true if a deletion occurred, false if the value was not found.
    bool deleteFirstInstance(const T v) {
        if (head == nullptr)
            return false;

        // Special case for deleting the head node.
        if (head->val == v) {
            if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                ListNode<T>* temp = head;
                head = head->nextNode;
                tail->nextNode = head;  // update tail's pointer
                delete temp;
            }
            return true;
        }

        ListNode<T>* current = head;
        do {
            if (current->nextNode->val == v) {
                ListNode<T>* temp = current->nextNode;
                // If the node to delete is tail, update tail.
                if (temp == tail) {
                    tail = current;
                }
                current->nextNode = temp->nextNode;
                delete temp;
                return true;
            }
            current = current->nextNode;
        } while (current != head);

        return false;
    }

    // Deletes all nodes that contain the value v.
    void deleteAllInstances(const T v) {
        while (deleteFirstInstance(v)) {}
    }

    // Returns the number of nodes containing the specified value v.
    int countInstances(const T v) const {
        if (head == nullptr)
            return 0;

        int counter = 0;
        ListNode<T>* current = head;
        do {
            if (current->val == v)
                counter++;
            current = current->nextNode;
        } while (current != head);
        return counter;
    }

    // Reverses the circular linked list in-place.
    void reverse() {
        // If the list is empty or has only one node, no reversal is necessary.
        if (head == nullptr || head == tail)
            return;

        // Break the circular link temporarily to reuse reversal logic from a linear list.
        tail->nextNode = nullptr;

        ListNode<T>* previous = nullptr;
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* next = current->nextNode;
            current->nextNode = previous;
            previous = current;
            current = next;
        }
        tail = head;
        head = previous;

        tail->nextNode = head;
    }

    // Prints the circular linked list to the console.
    // Each node is printed with its memory address and value.
    void print() const {
        if (head == nullptr) {
            std::cout << "Empty list" << std::endl;
            return;
        }
        ListNode<T>* current = head;
        do {
            std::cout << static_cast<std::string>(*current);
            current = current->nextNode;
        } while (current != head);
    }

    // Helper function to swap the contents of two CircularLinkedList objects.
    void swap(CircularLinkedList& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
};