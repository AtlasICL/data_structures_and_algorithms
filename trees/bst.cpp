/*
Implementation of a Binary Search Tree.
*/

#include <iostream>
#include <vector>
#include <stdexcept>

typedef int T;

struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(), left(nullptr), right(nullptr) {}
    TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(T val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
};


class BST {
private: 
    TreeNode* root;

public:

    // inserts a node with the specified value in the appropriate location
    // if provided value already exists in the BST, nothing will be changed
    void insertNode(T val) {
        if (contains(val)) { // BST already contains provided value; do nothing
            return; 
        }

        if (root == nullptr) { // tree is empty, insert as root
            root = new TreeNode(val);
            return;
        }

        TreeNode* curr = root;
        TreeNode* parent = nullptr;

        while (curr != nullptr) {
            parent = curr;
            if (val < curr->val) {
                curr = curr->left;
            }
            else if (val > curr->val) {
                curr = curr->right;
            }
        }
        
        if (val < parent->val) {
            parent->left = new TreeNode(val);
        }
        else if (val > parent->val) {
            parent->right = new TreeNode(val);
        }

    } 

    bool contains(T val) {
        if (root == nullptr) { // tree is empty
            return false;
        }
        TreeNode* curr = root;
        do {
            if (curr->val == val) {
                return true;
            }
            if (val < curr->val) {
                curr = curr->left;
            }
            else if (val > curr->val) {
                curr = curr->right;
            }
        } while (curr != nullptr);
        
        return false;
    }

};