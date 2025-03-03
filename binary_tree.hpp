#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <stdexcept>


struct TreeNode{
    double val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(double val)
        : val(val), left(nullptr), right(nullptr) { }
    
    TreeNode(double val, TreeNode* left, TreeNode* right)
        : val(val), left(left), right(right) { }
};


class BinaryTree{
private:
    TreeNode* root;

    // recursive helper function for deallocating tree memory
    void destroy(TreeNode* node){
        if (node != nullptr){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    TreeNode* insert(double value, TreeNode* branch){

        if (branch == nullptr){
            return new TreeNode(value);
        }

        else if (value < branch->val){
            branch->left = insert(value, branch->left);
        }

        else if (value > branch->val){
            branch->right = insert(value, branch->right);
        }

        // if value == branch->val, it means we already have a node with that value
        // so we do nothing (we are not implementing duplicate nodes)
        return branch;
    }

    // Recursive helper to print the tree in-order.
    void printInOrder(TreeNode* node) const {
        if (node) {
            printInOrder(node->left);
            std::cout << node->val << " ";
            printInOrder(node->right);
        }
    }
    

public:
    BinaryTree() : root(nullptr) { }

    ~BinaryTree(){
        destroy(root);
    }

    void insert(double value) {
        root = insert(value, root);
    }

    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }

};