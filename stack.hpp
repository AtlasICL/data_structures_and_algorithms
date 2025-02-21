#pragma once

#include <iostream>
#include <stdexcept>


template<typename T>
struct Node{
    T val;
    Node* next;

    Node(const T& val) : val(val), next(nullptr) { }
    Node(const T& val, Node<T>* next) : val(val), next(next) { }
};


template<typename T>
class Stack{
private:
    Node<T>* head;

public:
    Stack() : head(nullptr) { }
    
    // the destructor frees the memory used by the stack
    ~Stack(){
        while (head != nullptr) {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // push an element onto the stack
    void push(const T& val){
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    // remove an element from the top of the stack
    void pop(){
        if (this->isEmpty()){
            throw std::runtime_error("Attempted to pop from empty stack");
        }
        
        Node<T>* tmp = head;
        head = head->next;
        delete tmp; // deallocate the memory used by the top node
    }
    
    // returns the value of the top element
    T top() const {
        if (isEmpty()){
            throw std::runtime_error("Attempted to get top from empty stack");
        }

        return head->val;
    }


    bool isEmpty() const {
        return head == nullptr;
    }
};


