#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <stdexcept>

const int LIVES = 3; // number of lives per soldier (node)
const int SKIPS = 0; // number of skips before we start the election algorithm
const int K = 3;     // every k nodes, we eliminate a node

// definition for JNode (Josephus Node)
// similar to singly linked list, but the last node points back to the head
struct JNode{
    std::string val;
    JNode* next;
    int lives;

    JNode(std::string v, JNode* nextNode) : val(v), next(nextNode), lives(1) { }

    // explicit conversion operator to convert a JNode object to a string
    // debugging function, produces output of type [ListNode | addr: 0xffff val: {value}]
    explicit operator std::string() const {
        std::ostringstream oss;
        oss << "[JNode | addr: " << this << " val: " << this->val << "]\n";
        return oss.str();
    }
};

// this function creates a Josephus list with the names provided
// and returns a pointer to the head (note that head is essentially arbitrary, could be any node)
JNode* createJosephusList(const std::vector<std::string>& names){
    // if names is empty, we return an empty JNode list
    if (names.empty()){
        return nullptr;
    }

    JNode* head = new JNode(names[0], nullptr);
    JNode* current = head;

    for (size_t i = 1; i < names.size(); i++){
        current->next = new JNode(names[i], nullptr);
        current = current->next;
    }

    // link the final node to the head of the list
    current->next = head;

    return head;
}

// this function counts the number of nodes (/soldiers) in a Josephus list
int countNodes(JNode* head){
    if (head == nullptr){
        return 0; // empty list, so 0 nodes
    }

    int counter = 0;
    JNode* current = head;

    do {
        counter++;
        current = current->next;
    } while (current != head);

    return counter;
}

// this function prints a Josephus list
void printJosephusList(JNode* head) {
    if (head == nullptr) {
        std::cout << "Empty list" << std::endl;
        return;
    }
    
    JNode* current = head;
    do {
        std::cout << static_cast<std::string>(*current);
        current = current->next;
    } while (current != head);
    
    std::cout << std::endl;
}

// this function implements the Josephus election algorithm, eliminating every k nodes
// returns the value of the last remaining node
std::string josephusElection(JNode* head, int k){
    
    JNode* current = head;

    do {
        for (int i = 0; i < k-1; i++){
            current = current->next;
        }
        JNode* tmp = current->next;
        current->next = current->next->next;

        delete tmp; // free the memory of the deleted node

    } while (countNodes(head) > 1);

    return head->val;

}

int main()
{
    std::vector<std::string> names = {"a", "b", "c", "e", "g", "z"};
    JNode* jos = createJosephusList(names);
    printJosephusList(jos);

    int numNodes = countNodes(jos);
    std::cout << "Number of nodes = " << numNodes << std::endl;
}


