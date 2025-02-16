#include <iostream>
#include <string>
#include <sstream>
#include <vector>

typedef int list_t;

struct ListNode{
    list_t val;
    ListNode* nextNode;

    ListNode(list_t v, ListNode* next) : val(v), nextNode(next) { }

    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[ListNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};

class LinkedList{
private:
    ListNode* head;
    ListNode* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) { }

    void createList(const std::vector<list_t>& values){
        head = nullptr;
        tail = nullptr;

        for (const list_t& value : values){
            ListNode* newNode = new ListNode(value, nullptr);

            // if the list is empty, this created new node becomes both the head and the tail
            // as it is the only node in the list
            if (head == nullptr){
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
        int nodeCount = 1; 
        ListNode* ptr = head;
        while (ptr->nextNode != nullptr){
            ptr = ptr->nextNode;
            nodeCount++;
        }
        return nodeCount;
    }

    // this function inserts a node at the head of the linked list
    void insertAtHead(const list_t v){
        // if the list is empty, we set both head and tail to be this new node
        if (head == nullptr){
            ListNode* tmp = new ListNode(v, nullptr);
            this->head = tmp;
            this->tail = tmp;
            return;
        }

        // otherwise we add a new node, which has next = head, then we update head
        ListNode* tmp = new ListNode(v, head);
        this->head = tmp;
    }

    // this function inserts a node at the tail of the linked list
    void insertAtTail(list_t v){
        // if the list is empty, we set both head and tail to be this new node
        if (head == nullptr){
            ListNode* tmp = new ListNode(v, nullptr);
            this->head = tmp;
            this->tail = tmp;
            return;
        }

        // otherwise we add a new node, which has next = nullptr, as it as the tail
        // we link the new node to the previous tail, then we update tail
        ListNode* tmp = new ListNode(v, nullptr);
        this->tail->nextNode = tmp;
        this->tail = tmp;
    }

    // this function inserts a node at a specified index of the linked list
    void insertAtIndex(list_t v, int idx){
        // check provided index is positive
        if (idx < 0) {
            throw std::invalid_argument("Negative index not allowed.");
        }
        // check provided index is not bigger than length of the list
        // list is 0-indexed, so we use >=
        if (idx >= this.countNodes()){
            throw std::out_of_range("index is out of range for insertion.")
        }

        // body of the function for insertion

        // if insertion at idx 0, special case insert at head
        if (idx == 0) {
            insertAtHead(v);
            return;
        }

        // traverse to the node at idx
        ListNode* current = head;
        for (int i = 0; i < idx - 1; ++i) {
            current = current->nextNode;
        }

        ListNode* tmp = new ListNode(v, current->nextNode);
        current->nextNode = tmp;
        
        // if idx was the last element, update tail
        if (current == tail) {
            tail = tmp;
        }
    }

    // this function deletes the first instance of a value in the linked list
    // returns true if a deletion occurred, else false (the value was not found in the list)
    bool deleteFirstInstance(list_t v){
        return false;
    }

    // this function deletes all instances of a value in the linked list
    // returns true if at least one deletion occurred, else false (the value was not found in the list)
    bool deleteAllInstances(list_t v){
        return false;
    }

    // this function returns the number of the nodes with the specified value
    int countInstances(const list_t v) const {
        return 0;
    }

    void reverse(){

    }

    void print() const {
        if (head == nullptr) {
            std::cout << "Empty list" << std::endl;
            return;
        }
        
        // iterate through each node in the list
        for (ListNode* current = head; current != nullptr; current = current->nextNode) {
            // using the explicit conversion operator to convert the node to a string
            std::cout << static_cast<std::string>(*current);
        }
    }
};


int main(){

    LinkedList myList;
    myList.createList({2, 4, 5, 6, 7, 9});

    myList.print();

}