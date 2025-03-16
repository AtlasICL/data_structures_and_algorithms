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
    Node<T>* leftRotate(Node<T>* x);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* insert(Node<T>* node, T val);
    void insert(T val); // interface to insert a value
    void inorder(Node<T>* node);

    


};

