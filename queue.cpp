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
    QueueNode(T val, QueueNode<T>* next) : val(val), next(next) { }

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

    ~Queue(){
        while (head != nullptr){
            QueueNode<T>* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    // copy constructor
    Queue(const Queue& other) : head(nullptr), tail(nullptr) {
        QueueNode<T>* current = other.head;
        while (current != nullptr) {
            enqueue(current->val);
            current = current->next;
        }
    }

    // assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            Queue tmp(other);
            swap(tmp);
        }
        return *this;
    }

    void enqueue(T val){
        QueueNode<T>* tmp = new QueueNode<T>(val);
        if (tail == nullptr){ // Queue is empty
            head = tmp;
            tail = tmp;
        }
        else {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    T dequeue(){
        if (head == nullptr){
            throw std::out_of_range("Called dequeue on empty queue");
        }
        QueueNode<T>* tmp = head;
        T value = head->val;
        head = head->next;
        if (head == nullptr){ // Queue becomes empty
            tail = nullptr;
        }
        delete tmp;
        return value;
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

    void print() const {
        QueueNode<T>* curr = head;
        std::cout << "Queue{\n";
        while (curr != nullptr){
            std::cout << "    " << static_cast<std::string>(*curr);
            curr = curr->next;
        }
        std::cout << "}" << std::endl;
    }

    // Helper function
    void swap(Queue& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }

};

} // namespace atlas



int main(){
    atlas::Queue<int> myQ;

    myQ.enqueue(2);
    myQ.enqueue(6);
    myQ.enqueue(5);
    myQ.enqueue(3);
    myQ.enqueue(9);

    myQ.print();
}

