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
    AVLNode<T>* m_root;

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

    // performs a right-rotation on the subtree with root "unbalancedNode"
    // the caller is responsible for identifying the nodes which are unbalanced
    // returns the (new) root of the rotated subtree
    static void rightRotate(AVLNode<T>* unbalancedNode) {
        AVLNode<T>* leftChild = unbalancedNode->left;
        AVLNode<T>* subtreeToReattach = leftChild->right;

        // make the unbalanced node the right child of its left child
        leftChild->right = unbalancedNode;

        // subtreeToReattach becomes the left child of the unbalanced node
        unbalancedNode->left = subtreeToReattach;

        updateHeight(unbalancedNode);
        updateHeight(leftChild);

        return leftChild; // new root
    }

    // performs a left-rotation on the subtree with root "unbalancedNode"
    // the caller is responsible for identifying the nodes which are unbalanced
    // returns the (new) root of the rotated subtree
    static AVLNode<T>* leftRotate(AVLNode<T>* unbalancedNode) {
        if (unbalancedNode == nullptr) { throw std::invalid_argument("Attempted to rotate a null node"); }

        AVLNode<T>* rightChild = unbalancedNode->right;
        AVLNode<T>* subtreeToReattach = rightChild->left;

        rightChild->left = unbalancedNode;
        unbalancedNode->right = subtreeToReattach;

        updateHeight(unbalancedNode);
        updateHeight(rightChild);

        return rightChild;
    }

    // balance the given node
    static AVLNode<T>* balance(AVLNode<T>* node) {
        updateHeight(node); // to ensure we have up-to-date height
        int bf = balanceFactor(node);

    }

    // helper function for insertion
    static AVLNode<T>* insert(const T& val, AVLNode<T>* node) {
        if (node == nullptr) {
            return new AVLNode<T> val;
        }
        if (val < node->val) {
            node->left = insert(val, node->left);
        }
        else if (val > node->val) {
            node->right = insert(val, node->right);
        }
        else if (val == node->val) {
            // val already exists
            return node;
        }
        return balance(node);
    }

    // helper function to free the tree memory
    static void dealloc(AVLNode<T>* root) {
        if (root == nullptr) {
            return;
        }
        dealloc(root->left);
        dealloc(root->right);
        delete root;
    }

public:
    AVLTree() : m_root(nullptr) {}
    
    AVLTree(const T& val) : m_root(new Node<T>(val)) {}
    
    ~AVLTree() {
        dealloc(m_root);
    }

    // inserts a value into the tree
    void insert(const T& val) {
        m_root = insert(val, m_root);
    }

    void remove(const T& val);

    bool contains(const T& val);

    void inorder() const;
};

