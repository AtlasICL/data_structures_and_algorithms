/**
 * Problem Week 7:
 * 
 * Implement a stack and use it to reverse a string input by the user.
 * 
 * Challenge: implement a deque (double-ended queue) with linked list representation.
 * Include operations for insertion and deletion at both ends; and test it
 * with a palindromic check on strings.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


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
    ~Stack() {
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
        if (this->isEmpty()) { throw std::runtime_error("Attempted to pop from empty stack"); }
        
        Node<T>* tmp = head;
        head = head->next;
        delete tmp; // deallocate the memory used by the top node
    }
    
    // returns the value of the top element
    T top() const {
        if (isEmpty()) { throw std::runtime_error("Attempted to get top from empty stack"); }

        return head->val;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        const Node<T>* curr = head;
        if (head == nullptr) {
            std::cout << "EMPTY STACK" << std::endl;
            return;
        }

        std::cout << "STACK {\n";
        do {
            std::cout << "--" << static_cast<std::string>(*curr);
            curr = curr->next;
        } while (curr != nullptr);

        std::cout << "}" << std::endl;
    }
};


// function to get word from user through console
std::string getInputWord() {
    std::string userInput;
    std::cout << "Enter a word: " << std::endl;
    std::cin >> userInput;
    return userInput;
}


// function to reverse the word
void reverseUserInputWord() {

    std::string userInput = getInputWord();

    Stack<char> letterStack = Stack<char>();
    for (const char& c : userInput) {
        letterStack.push(c);
    }

    std::string reversed = "";
    while (!letterStack.isEmpty()) {
        reversed.push_back(letterStack.top());
        letterStack.pop();
    }

    std::cout << "Reversed string: " << reversed << std::endl;
}

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
class Dequeue {
private: 
    QueueNode<T>* head;
    QueueNode<T>* tail;

public:
    Dequeue() : head(nullptr), tail(nullptr) {}

    ~Dequeue() {
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


bool checkPalindrome(std::string word) {

    Dequeue<char> palindromeDequeue = Dequeue<char>();
    
    for (const char c : word) {
        palindromeDequeue.insertAtHead(c);
    }

    char left;
    char right;

    while (palindromeDequeue.countElements() > 1) { // if odd number of letters, middle letter does not affect palindrome-ness

        left = palindromeDequeue.getHead();
        palindromeDequeue.popHead();

        right = palindromeDequeue.getTail();
        palindromeDequeue.popTail();

        if (left != right) {
            return false;
        }
    }

    return true;
}



int main() {

    // PART 1
    reverseUserInputWord();

    // PART 2
    std::string word = "nolemonnomelon";
    bool isPalindrome = checkPalindrome(word);
    
    std::cout << word << " is palindrome? " << isPalindrome << std::endl;
}