/**
 * Implementation of a red-black tree.
 */

#include <iostream>
#include <stdexcept>

class RBTree;
struct RBNode;

enum Color { RED, BLACK };

struct RBNode {
    int val;
    Color color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;     
};