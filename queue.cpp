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
    QueueNode* head;
    QueueNode* tail;

public:
    Queue() : head(nullptr), tail(nullptr) { }

    

};

}