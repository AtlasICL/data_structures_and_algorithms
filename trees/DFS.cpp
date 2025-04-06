/*
 * Implementation of DFS on a basic binary tree.
 */

#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
struct Node {
    T val;
    Node* left;
    Node* right;

    Node() : val(), left(nullptr), right(nullptr) {}
    Node(T val) : val(val), left(nullptr), right(nullptr) {}
    Node(T val, Node* left, Node* right) 
        : val(val), left(left), right(right) {}
};

template<typename T>
class BST {
private:
    Node<T>* m_root; // pointer to root node

public:
    BST() : m_root(nullptr) {}

    BST(T val) : m_root(new Node<T>(val)) {}

    ~BST() {
        dealloc(m_root);
    }

    // inserts the given value in the BST
    // @throws invalid_argument if val already exists in the tree
    void insert(const T& val) {
        if (contains(val)) { throw std::invalid_argument("Attempted to insert duplicate element"); }
        m_root = insert(val, m_root);
    }

    // @returns Returns true if the tree contains the value val
    // @returns false otherwise.
    bool contains(const T& val) const {
        return contains(val, m_root);
    }

    // performs a pre-order depth-first traversal of the tree
    // and prints out the order in which the nodes are visited
    // NOTE: this implementation is called pre-order because it processes 
    // the root node before the subtrees
    void pre_order_DFS() const {
        std::cout << "**** Performing pre-order DFS ****" << std::endl;
        pre_order_DFS(m_root);
        std::cout << std::endl;
    }

    // performs an in-order depth-first traversal of the tree
    // and prints out the order in which the nodes were visited
    void in_order_DFS() const {
        std::cout << "**** Performing in-order DFS ****" << std::endl;
        in_order_DFS(m_root);
        std::cout << std::endl;
    }
    
private:
    // helper function to free the memory used by the tree 
    void dealloc(Node<T>* ptr) {
        if (ptr == nullptr) { return; }
        dealloc(ptr->left);
        dealloc(ptr->right);
        delete ptr;
    }

    // helper function for recursion
    // checks if the subtree with root curr_node contains the value val
    bool contains(const T& val, Node<T>* curr_node) const {
        if (curr_node == nullptr) {
            return false;
        }
        if (curr_node->val == val) {
            return true;
        }
        return val < curr_node->val ? contains(val, curr_node->left) : contains(val, curr_node->right);
    }

    // recursive helper for insertion
    Node<T>* insert(const T& val, Node<T>* curr_root) {
        if (curr_root == nullptr) {
            return new Node<T>(val);
        }
        if (val <= curr_root->val) {
            curr_root->left = insert(val, curr_root->left);
        }
        else if (val > curr_root->val) {
            curr_root->right = insert(val, curr_root->right);
        }
        return curr_root;
    }

    // helper function for pre-order DFS
    void pre_order_DFS(Node<T>* curr_node) const {
        if (curr_node == nullptr) {
            return;
        }
        std::cout << "| " << curr_node->val << " ";
        pre_order_DFS(curr_node->left);
        pre_order_DFS(curr_node->right);
    }

    // helper function for in-order DFS
    void in_order_DFS(Node<T>* curr_node) const {
        if (curr_node == nullptr) {
            return;
        }
        in_order_DFS(curr_node->left);
        std::cout << "| " << curr_node->val << " ";
        in_order_DFS(curr_node->right);
    }
};

int main() {

    BST<int> t(6);
    t.insert(2);
    t.insert(7);
    t.insert(1);
    t.insert(4);
    t.insert(3);
    t.insert(5);
    t.insert(9);
    t.insert(8);

    t.pre_order_DFS();

    t.in_order_DFS();

}