/**
 * Implementation of an AVL tree.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

template<typename T>
struct Node {
    T val;
    Node* left;
    Node* right;
    int height;

    Node() : val(), left(nullptr), right(nullptr), height(1) {}
    Node(T val) : val(val), left(nullptr), right(nullptr), height(1) {}
    Node(T val, Node* left, Node* right) :
        val(val), left(left), right(right), height(1) {}

    static int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    static int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int l = getHeight(node->left);
        int r = getHeight(node->right);
        return l - r;
    }
};


template<typename T>
class AVLTree {
private:
    Node<T>* root;

public:
    AVLTree() : root(nullptr) {}
    bool contains(T val);
    Node<T>* leftRotate(Node<T>* x);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* insert(Node<T>* node, T val);
    void insert(T val); // interface to insert a value
    void deleteVal(T val);
    void inorder(Node<T>* node);


    Node<T>* insert(Node<T>* node, T val) const {

        if (contains(val)) {
            throw std::invalid_argument("Attempted to insert duplicate element");
        }

        // 1. standard BST insertion
        if (node == nullptr) {
            return new Node<T>(val);
        }

        if (val < node->val) {
            node->left = insert(node->left, val);
        }
        else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        
        // 2. update height of the parent node
        node->height = max(Node<T>::getHeight(node->left), Node<T>::getHeight(node->right)) + 1;

        // 3. check if this node has become unbalanced
        int balance = Node<T>::getBalance(node);

        // 4. if it is unbalanced, 4 possible cases


    }


};

