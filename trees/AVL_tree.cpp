/**
 * Implementation of an AVL tree.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

template<typename T>
struct AVLNode {
    T val;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T val) : val(val), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // gets the height of a node
    static int getHeight(AVLNode<T>* node) {
        if (node == nullptr) { return 0; }
        return node->height;
    }

    // calculates the balance factor of a node
    static int balanceFactor(AVLNode<T>* node) {
        if (node == nullptr) { return 0; }
        return getHeight(node->left) - getHeight(node->right);
    }

    // updates the height of a node (based on its children)
    static void updateHeight(AVLNode<T>* node) {
        if (node == nullptr) { throw std::invalid_argument("Attempted to update height of null node"); }
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

};

