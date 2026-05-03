#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <queue>
#include <stack>

template<typename T>
class AVLTree {
public:
    struct Node {
        T val;
        Node* left;
        Node* right;
        int height;

        Node(T val) : val(val), left(nullptr), right(nullptr), height(1) {}
    };

private:
    Node* m_root;

    /**
     * @brief Gets the height of a node.
     * @returns Returns the height of the given node.
     */
    static int getHeight(Node* node) {
        if (node == nullptr) { return 0; }
        return node->height;
    }

    /**
     * @brief Calculates the balance factor of a node.
     * @returns Returns the balance factor of the given node.
     */
    static int balanceFactor(Node* node) {
        if (node == nullptr) { return 0; }
        return getHeight(node->left) - getHeight(node->right);
    }

    /**
     * @brief Updates the height of a node (based on its children).
     * @throws std::invalid_argument if called with a null node.
     */
    static void updateHeight(Node* node) {
        if (node == nullptr) { 
            throw std::invalid_argument("Attempted to update height of null node"); 
        }
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    /**
     * @brief Performs a right-rotation on the subtree with root `unbalancedNode`.
     * @throws std::invalid_argument if called with a null node.
     * @returns Returns the new root of the rotated subtree. 
     */
    static Node* rightRotate(Node* unbalancedNode) {
        if (unbalancedNode == nullptr) {
            throw std::invalid_argument("Attempted to rotate a null node");
        }

        Node* leftChild = unbalancedNode->left;
        Node* subtreeToReattach = leftChild->right;

        // Make the unbalanced node the right child of its left child.
        leftChild->right = unbalancedNode;

        // subtreeToReattach becomes the left child of the unbalanced node.
        unbalancedNode->left = subtreeToReattach;

        updateHeight(unbalancedNode);
        updateHeight(leftChild);

        return leftChild; // new root
    }

    /**
     * @brief Performs a left-rotation on the subtree with root `unbalancedNode`.
     * @throws std::invalid_argument if called with a null node.
     * @returns Returns the (new) root of the rotated subtree.
     */
    static Node* leftRotate(Node* unbalancedNode) {
        if (unbalancedNode == nullptr) {
            throw std::invalid_argument("Attempted to rotate a null node");
        }

        Node* rightChild = unbalancedNode->right;
        Node* subtreeToReattach = rightChild->left;

        rightChild->left = unbalancedNode;
        unbalancedNode->right = subtreeToReattach;

        updateHeight(unbalancedNode);
        updateHeight(rightChild);

        return rightChild;
    }

    /**
     * @brief Balances a node.
     * @returns Returns the balanced node.
     */
    static Node* balance(Node* node) {
        updateHeight(node); // Ensure we have up-to-date height.
        int bf = balanceFactor(node);

        // Left-heavy case:
        if (bf > 1) {
            // If "zig-zag" case, we need to transform into "linear" case.
            if (balanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left); // Transform into linear case.
            }
            return rightRotate(node);
        }

        // Right-heavy case:
        if (bf < -1) {
            // If "zig-zag" case, we transform into linear case.
            if (balanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    /**
     * Helper function for inserting a node.
     */
    static Node* insert(const T& val, Node* node) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->val) {
            node->left = insert(val, node->left);
        }
        else if (val > node->val) {
            node->right = insert(val, node->right);
        }
        else { // val already exists
            return node;
        }
        return balance(node);
    }

    /**
     * Helper function to free the memory allocated to the tree.
     */
    static void dealloc(Node* root) {
        if (root == nullptr) {
            return;
        }
        dealloc(root->left);
        dealloc(root->right);
        delete root;
    }

    /**
     * Helper function for recursion.
     * Checks if the subtree with root curr_node contains the value val.
     */
    static bool contains(const T& val, Node* curr_node) {
        if (curr_node == nullptr) { return false; }
        if (curr_node->val == val) { return true; }
        return val < curr_node->val ? contains(val, curr_node->left) : contains(val, curr_node->right);
    }

    /**
     * Helper function for removing elements.
     */ 
    static Node* remove(const T& val, Node* root) {
        if (root == nullptr) { throw std::invalid_argument("val not found"); }

        if (val < root->val) {
            root->left = remove(val, root->left);
        }
        else if (val > root->val) {
            root->right = remove(val, root->right);
        }
        else if (val == root->val) {
            Node* left_child = root->left;
            Node* right_child = root->right;

            // If the node had no children:
            if (left_child == nullptr && right_child == nullptr) {
                delete root;
                return nullptr;
            }

            // If the node had only one child:
            if (left_child == nullptr) {
                delete root;
                return right_child;
            }
            else if (right_child == nullptr) {
                delete root;
                return left_child;
            }

            // If the node had two children, we need to find which one to connect to the grandparent.
            // The node which must be connected is the in-order successor (smallest node in the right subtree).
            Node* tmp = inorderSuccessor(root);
            root->val = tmp->val;
            root->right = remove(tmp->val, root->right); // we call the remove function with the val of
            // the inorder successor of root.
            // That value, which used to be stored in root->right, has now been moved to root (and is duplicated)
            // so we repeat this same process on root->right
        }
        return balance(root);
    }

    /**
     * @brief Helper function to find the in-order successor of a node
     * @returns Returns the address of the successor (not the value!)
     */
    static Node* inorderSuccessor(Node* node) {
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
    
    explicit AVLTree(const T& val) : m_root(new Node(val)) {}
    
    ~AVLTree() { dealloc(m_root); }

    // Explicitly delete copy and move constructors.
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    /**
     * @brief Inserts a value into the tree.
     * @note No-op if val already exists.
     */
    void insert(const T& val) {
        m_root = insert(val, m_root);
    }

    /**
     * @brief Removes an element from the tree.
     * @throws std::invalid_argument if the element does not exist.
     */
    void remove(const T& val) {
        if (!contains(val)) { throw std::invalid_argument("Element does not exist"); }
        m_root = remove(val, m_root);
    }

    /**
     * @brief Checks whether an element exists within the tree.
     * @returns Returns true if the tree contains the value val, false otherwise.
     */
    bool contains(const T& val) const {
        return contains(val, m_root);
    }

    /**
     * @brief Inorder DF traversal of the tree.
     * @returns Returns a vector with the elements in the traversed order.
     */
    std::vector<T> inOrderTraversal() const {
        std::vector<T> out;
        std::stack<Node*> stack;
        Node* curr = m_root;
        while (curr != nullptr || !stack.empty()) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.top(); stack.pop();
            out.push_back(curr->val);
            curr = curr->right;
        }
        return out;
    }

    /**
     * @brief Preorder DF traversal of the tree.
     * @returns Returns a vector with the elements in the traversed order.
     */
    std::vector<T> preOrderTraversal() const {
        std::vector<T> out;
        if (m_root == nullptr) { return out; }

        std::stack<Node*> stack;
        stack.push(m_root);

        while (!stack.empty()) {
            Node* curr = stack.top(); stack.pop();
            out.push_back(curr->val);
            if (curr->right != nullptr) { stack.push(curr->right); }
            if (curr->left != nullptr)  { stack.push(curr->left); }
        }
        return out;
    }

    /**
     * @brief Postorder DF traversal of the tree.
     * @returns Returns a vector with the elements in the traversed order.
     */
    std::vector<T> postOrderTraversal() const {
        std::vector<T> out;
        if (m_root == nullptr) { return out; }

        std::stack<Node*> stack;
        stack.push(m_root);

        while (!stack.empty()) {
            Node* curr = stack.top(); stack.pop();
            out.push_back(curr->val);
            if (curr->left != nullptr)  { stack.push(curr->left); }
            if (curr->right != nullptr) { stack.push(curr->right); }
        }

        std::reverse(out.begin(), out.end());
        return out;
    }

    /**
     * @brief BF traversal of the tree.
     * @returns Returns a vector with the elements in the traversed order.
     */
    std::vector<T> breadthFirstTraversal() const {
        std::queue<Node*> queue; 
        std::vector<T> output_order = {};

        if (m_root == nullptr) { return {}; }

        queue.push(m_root);
        while (!queue.empty()) {
            Node* curr_node = queue.front();
            queue.pop();

            output_order.push_back(curr_node->val);

            // Enqueue the children of our current node if they exist
            if (curr_node->left != nullptr) { queue.push(curr_node->left); }
            if (curr_node->right != nullptr) { queue.push(curr_node->right); }
        }

        return output_order;
    } 
};
