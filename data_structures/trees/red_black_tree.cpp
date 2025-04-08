/**
 * Implementation of a red-black tree.
 */

#include <iostream>
#include <stdexcept>

enum Color {
    RED,
    BLACK
};

template<typename T>
struct RBNode {
    T val;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    Color color;
};

template<typename T>
class RBTree {

};