#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

namespace atlas
{

template<typename T>
struct QueueNode{

    T val;
    QueueNode* next;

    QueueNode() : val(), next(nullptr) { }
    QueueNode(T val) : val(val), next(nullptr) { }
    QueueNode(T val, QueueNode* next) : val(val), next(next) { }

    // Explicit conversion operator to convert from QueueNode object to a string.
    // Output of type [ListNode | addr: 0xffff val: {value}].
    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[QueueNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};


template<typename T>
class Queue {
private:
    QueueNode<T>* head;
    QueueNode<T>* tail;

public:
    Queue() : head(nullptr), tail(nullptr) { }

    void enqueue(T val){
        QueueNode<T>* tmp = new QueueNode<T>(val);
        tail->next = tmp;
        tail = tail->next;
    }

    T dequeue(){
        if (head == nullptr){
            throw std::out_of_range("Called dequeue on empty queue");
        }
        QueueNode<T>* tmp = head;
        T val = head->val;
        head = head->next;
        delete tmp;
        return val;
    }

    int size() const {
        if (head == nullptr){
            return 0;
        }
        int counter = 0;
        QueueNode<T>* curr = head;
        while (curr != nullptr){
            curr = curr->next;
            counter++;
        }
        return counter;
    }

};

}

