#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

namespace atlas
{

template<typename T>
struct Node {
    T val;
    Node* next;

    Node(const T& val) : val(val), next(nullptr) {}
    Node(const T& val, Node<T>* next) : val(val), next(next) {}

    // Explicit conversion operator to convert from QueueNode object to a string.
    // Output of type [StackItem | addr: 0xffff val: {value}].
    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[Stack Item | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};



template<typename T>
class Stack {
private:
    Node<T>* head;

public:
    Stack() : head(nullptr) {}
    
    // the destructor frees the memory used by the stack
    ~Stack(){
        while (head != nullptr) {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // push an element onto the stack
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    // remove an element from the top of the stack
    void pop() {
        if (this->isEmpty()) {
            throw std::runtime_error("Attempted to pop from empty stack");
        }
        
        Node<T>* tmp = head;
        head = head->next;
        delete tmp; // deallocate the memory used by the top node
    }
    
    // returns the value of the top element
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Attempted to get top from empty stack");
        }

        return head->val;
    }


    bool isEmpty() const {
        return head == nullptr;
    }
};

}
