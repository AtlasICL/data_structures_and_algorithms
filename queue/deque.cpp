/**
 * Deque (double-ended queue) implementation.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

template<typename T>
struct QueueNode {

    T val;
    QueueNode* next;

    QueueNode() : val(), next(nullptr) {}
    QueueNode(T val) : val(val), next(nullptr) {}
    QueueNode(T val, QueueNode<T>* next) : val(val), next(next) {}

    // Explicit conversion operator to convert from QueueNode object to a string.
    // Output of type [ListNode | addr: 0xffff val: {value}].
    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[QueueNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};


template<typename T>
class Deque {
private: 
    QueueNode<T>* head;
    QueueNode<T>* tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}

    ~Deque() {
        while (!isEmpty()) {
            popHead();
        }
    }

    // returns true if the queue is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // returns the number of elements in the queue
    int countElements() const {
        int counter = 0;
        const QueueNode<T>* curr = head;
        while (curr != nullptr) {
            counter++;
            curr = curr->next;
        }
        return counter;
    }

    // inserts an element at the head of the queue
    void insertAtHead(T val) {
        if (head == nullptr) { // case that list is empty
            head = new QueueNode<T>(val);
            tail = head;
            return;
        }
        QueueNode<T>* old_head = head;
        head = new QueueNode<T>(val);
        head->next = old_head;
    }

    // inserts an element at the tail of the queue
    void insertAtTail(T val) {
        if (head == nullptr) { // case that list is empty
            head = new QueueNode<T>(val);
            tail = head;
            return;
        }
        QueueNode<T>* newTail = new QueueNode<T>(val);
        tail->next = newTail;
        tail = tail->next;
    }

    // gets the first element of the queue
    // @throws runtime error if queue is empty when called
    T getHead() const {
        if (isEmpty()) { throw std::runtime_error("Attempted to getHead of empty queue"); }

        return head->val;
    }

    // gets the last element of the queue
    // @throws runtime error if queue is empty when called
    T getTail() const {
        if (isEmpty()) { throw std::runtime_error("Attempted to getTail of empty queue"); }

        return tail->val;
    }

    // removes the element at the head of the queue
    // @throws runtime error if queue is empty when called
    void popHead() {
        if (isEmpty()) { throw std::runtime_error("Attempted to popHead of empty queue"); }

        QueueNode<T>* oldHead = head;
        head = head->next;
        delete oldHead; // free the memory of the popped node

        if (head == nullptr) { // if the queue became empty
            tail = nullptr; // ensure tail does not point to the now-deleted node
        }
    }

    // removes the element at the tail of the queue
    // @throws runtime error if queue is empty when called
    void popTail() {
        if (isEmpty()) { throw std::runtime_error("Attempted to popTail of empty queue"); }

        if (head == tail) { // if there is only one element (special case)
            delete head;
            head = tail = nullptr;
            return;
        }
        
        QueueNode<T>* tailPtr = head;
        while (tailPtr->next != tail) {
            tailPtr = tailPtr->next;
        }

        delete tail; // free the memory of the (old) tail 

        tail = tailPtr; // update the tail
        tail->next = nullptr; // ensure the tail points to null
    }

};

