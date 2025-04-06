/**
 * Problem Week 9:
 * 
 * Implement a binary tree with functions for insertion and inorder traversal.
 * 
 * Challenge: implement an AVL tree (or red-black tree) with insertion and
 * rotation operations. 
 * Test it with a series of input values to demonstrate self-balancing properties.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

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

    // helper function to free the memory used by the tree 
    void dealloc(Node<T>* ptr) {
        if (ptr == nullptr) { return; }
        dealloc(ptr->left);
        dealloc(ptr->right);
        delete ptr;
    }

    // helper function for insertion
    static Node<T>* insert(const T& val, Node<T>* curr_root) {
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

    // helper function for recursion
    // checks if the subtree with root curr_node contains the value val
    static bool contains(const T& val, Node<T>* curr_node) {
        if (curr_node == nullptr) {
            return false;
        }
        if (curr_node->val == val) {
            return true;
        }
        return val < curr_node->val ? contains(val, curr_node->left) : contains(val, curr_node->right);
    }

    // helper function to find the in-order successor of a node
    // @returns Returns the address of the successor (not the value!)
    static Node<T>* inorderSuccessor(Node<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        node = node->right;
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // helper function for removing elements 
    Node<T>* remove(const T& val, Node<T>* root) {
        if (root == nullptr) { throw std::invalid_argument("val not found"); }

        if (val < root->val) {
            root->left = remove(val, root->left);
        }
        else if (val > root->val) {
            root->right = remove(val, root->right);
        }
        else if (val == root->val) {
            Node<T>* left_child = root->left;
            Node<T>* right_child = root->right;

            // if the node had no children
            if (left_child == nullptr && right_child == nullptr) {
                delete root;
                return nullptr;
            }

            // if the node had only one child:
            if (left_child == nullptr) {
                delete root;
                return right_child;
            }
            else if (right_child == nullptr) {
                delete root;
                return left_child;
            }

            // if the node had two children, we need to find which one to connect to the grandparent
            // the node which must be connected is the in-order successor (smallest node in the right subtree)
            Node<T>* tmp = inorderSuccessor(root);
            root->val = tmp->val;
            root->right = remove(tmp->val, root->right); // we call the remove function with the val of
            // the inorder successor of root.
            // That value, which used to be stored in root->right, has now been moved to root (and is duplicated)
            // so we repeat this same process on root->right
        }
        return root;
    }

    // helper function for in-order traversal
    static void in_order_DFS(Node<T>* curr_node) {
        if (curr_node == nullptr) {
            return;
        }
        in_order_DFS(curr_node->left);
        std::cout << "| " << curr_node->val << " ";
        in_order_DFS(curr_node->right);
    }

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

    // removes the element from the tree
    // @throws invalid_argument if the element does not exist
    void remove(const T& val) {
        if (!contains(val)) { throw std::invalid_argument("Element does not exist"); }
        m_root = remove(val, m_root);
    }

    // prints out the tree in-order
    void print_in_order() const {
        std::cout << "**** Performing in-order traversal ****" << std::endl;
        in_order_DFS(m_root);
        std::cout << std::endl;
    }

};

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
    static AVLNode<T>* rightRotate(AVLNode<T>* unbalancedNode) {
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

        // left-heavy case
        if (bf > 1) {
            // if "zig-zag" case, we need to transform into "linear" case
            if (balanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left); // transform into linear case
            }
            return rightRotate(node);
        }

        // right-heavy case
        if (bf < -1) {
            // if "zig-zag" case, we transform into linear case
            if (balanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    // helper function for insertion
    static AVLNode<T>* insert(const T& val, AVLNode<T>* node) {
        if (node == nullptr) {
            return new AVLNode<T>(val);
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

    // helper function for recursion
    // checks if the subtree with root curr_node contains the value val
    bool contains(const T& val, AVLNode<T>* curr_node) const {
        if (curr_node == nullptr) {
            return false;
        }
        if (curr_node->val == val) {
            return true;
        }
        return val < curr_node->val ? contains(val, curr_node->left) : contains(val, curr_node->right);
    }

    // helper function for in-order traversal
    static void in_order_DFS(AVLNode<T>* curr_node) {
        if (curr_node == nullptr) {
            return;
        }
        in_order_DFS(curr_node->left);
        std::cout << "| " << curr_node->val << " ";
        in_order_DFS(curr_node->right);
    }

    // helper function for removing elements 
    AVLNode<T>* remove(const T& val, AVLNode<T>* root) {
        if (root == nullptr) { throw std::invalid_argument("val not found"); }

        if (val < root->val) {
            root->left = remove(val, root->left);
        }
        else if (val > root->val) {
            root->right = remove(val, root->right);
        }
        else if (val == root->val) {
            AVLNode<T>* left_child = root->left;
            AVLNode<T>* right_child = root->right;

            // if the node had no children
            if (left_child == nullptr && right_child == nullptr) {
                delete root;
                return nullptr;
            }

            // if the node had only one child:
            if (left_child == nullptr) {
                delete root;
                return right_child;
            }
            else if (right_child == nullptr) {
                delete root;
                return left_child;
            }

            // if the node had two children, we need to find which one to connect to the grandparent
            // the node which must be connected is the in-order successor (smallest node in the right subtree)
            AVLNode<T>* tmp = inorderSuccessor(root);
            root->val = tmp->val;
            root->right = remove(tmp->val, root->right); // we call the remove function with the val of
            // the inorder successor of root.
            // That value, which used to be stored in root->right, has now been moved to root (and is duplicated)
            // so we repeat this same process on root->right
        }
        return balance(root);
    }

    // helper function to find the in-order successor of a node
    // @returns Returns the address of the successor (not the value!)
    static AVLNode<T>* inorderSuccessor(AVLNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        node = node->right;
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    AVLTree() : m_root(nullptr) {}
    
    AVLTree(const T& val) : m_root(new AVLNode<T>(val)) {}
    
    ~AVLTree() {
        dealloc(m_root);
    }

    // inserts a value into the tree
    void insert(const T& val) {
        m_root = insert(val, m_root);
    }

    // removes the element from the tree
    // @throws invalid_argument if the element does not exist
    void remove(const T& val) {
        if (!contains(val)) { throw std::invalid_argument("Element does not exist"); }
        m_root = remove(val, m_root);
    }

    // @returns Returns true if the tree contains the value val
    // @returns false otherwise.
    bool contains(const T& val) const {
        return contains(val, m_root);
    }

    // prints the elements of the tree in-order
    void inorder() const {
        std::cout << "**** Performing in-order traversal ****" << std::endl;
        in_order_DFS(m_root);
        std::cout << std::endl;
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

    t.print_in_order();

    t.remove(2);
    
    t.print_in_order();

}

