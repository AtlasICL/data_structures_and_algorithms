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

