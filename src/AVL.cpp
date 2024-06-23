#include "AVL.h"
#include <iostream>
#include <algorithm>

// Default constructor for TreeNode
TreeNode::TreeNode() {
    name = "";
    ufid = "";
    left = nullptr;
    right = nullptr;
}

// Parameterized constructor for TreeNode, initializes member variables with given values
TreeNode::TreeNode(std::string n, std::string u) {
    name = n;
    ufid = u;
    left = nullptr;
    right = nullptr;
}

// Default constructor for AVLTree
AVLTree::AVLTree() {
    root = nullptr;
}

// Prints the number of levels (height) in the tree
void AVLTree::printLevelCount() const {
    int levels = height(this->root);  // Assuming this->root is the root of the AVL tree
    std::cout << levels << std::endl;
}

// Returns the height of the tree from a given node N
int AVLTree::height(TreeNode* N) const {
    if (N == nullptr)
        return 0;
    return std::max(height(N->left), height(N->right)) + 1;
}

// Calculates and returns the balance factor of a given node N
int AVLTree::getBalanceFactor(TreeNode* N) const {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Performs a right rotation around a given node y and returns the new root
TreeNode* AVLTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Performs a left rotation around a given node x and returns the new root
TreeNode* AVLTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Inserts a new node into the tree and rebalances if necessary
TreeNode* AVLTree::insert(TreeNode* r, const std::string& name, const std::string& ufid) {
    if (r == nullptr) {
        std::cout << "successful" << std::endl;
        return new TreeNode(name, ufid);
    }

    int new_value = std::stoi(ufid);
    int r_value = std::stoi(r->ufid);

    if (new_value < r_value) {
        r->left = insert(r->left, name, ufid);
    } else if (new_value > r_value) {
        r->right = insert(r->right, name, ufid);
    } else {
        std::cout << "unsuccessful" << std::endl;
        return r;
    }

    // Perform rotations if the tree is unbalanced
    int bf = getBalanceFactor(r);
    // Left Left Case
    if (bf > 1 && new_value < std::stoi(r->left->ufid))
        return rightRotate(r);

    // Right Right Case
    if (bf < -1 && new_value > std::stoi(r->right->ufid))
        return leftRotate(r);

    // Left Right Case
    if (bf > 1 && new_value > std::stoi(r->left->ufid)) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    // Right Left Case
    if (bf < -1 && new_value < std::stoi(r->right->ufid)) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

// Finds and returns the node with the minimum value in the tree
TreeNode* AVLTree::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Deletes a node with a given value from the tree and rebalances if necessary
TreeNode* AVLTree::deleteNode(TreeNode* r, int v) {
    if (r == nullptr)
        return r;
        
    if (v < std::stoi(r->ufid))
        r->left = deleteNode(r->left, v);
    else if (v > std::stoi(r->ufid))
        r->right = deleteNode(r->right, v);
    else {
        if (r->left == nullptr || r->right == nullptr) {
            TreeNode* temp = r->left ? r->left : r->right;
            if (temp == nullptr) {
                temp = r;
                r = nullptr;
            } else {
                *r = *temp;
            }
            delete temp;
        } else {
            TreeNode* temp = minValueNode(r->right);
            r->ufid = temp->ufid;
            r->name = temp->name;
            r->right = deleteNode(r->right, std::stoi(temp->ufid));
        }
    }

    if (r == nullptr)
        return r;

    int bf = getBalanceFactor(r);
    if (bf > 1 && getBalanceFactor(r->left) >= 0)
        return rightRotate(r);
    if (bf > 1 && getBalanceFactor(r->left) < 0) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    if (bf < -1 && getBalanceFactor(r->right) <= 0)
        return leftRotate(r);
    if (bf < -1 && getBalanceFactor(r->right) > 0) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

// Traverses the tree in inorder and stores the nodes in a vector
// void AVLTree::inorderTraversal(TreeNode* r, std::vector<TreeNode*>& nodes) {
//     if (r == nullptr)
//         return;
//     inorderTraversal(r->left, nodes);
//     nodes.push_back(r);
//    inorderTraversal(r->right, nodes);
// }

TreeNode* AVLTree::findNthInorder(TreeNode* root, int n, int& count) {
    if (root == nullptr) return nullptr;

    TreeNode* left = findNthInorder(root->left, n, count);
    if (left) return left;

    if (count == n) return root;
    count++;

    return findNthInorder(root->right, n, count);
}

// Removes the nth node in inorder traversal
// Modified to use findNthInorder for more efficient operation
void AVLTree::removeInorder(TreeNode*& root, int n) {
    int count = 0;
    TreeNode* node_to_delete = findNthInorder(root, n, count);
    if (node_to_delete) {
        root = deleteNode(root, std::stoi(node_to_delete->ufid));
        std::cout << "successful" << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Prints the tree nodes in inorder
void AVLTree::printInorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    printInorder(r->left, isFirst);
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
    printInorder(r->right, isFirst);
}

// Prints the tree nodes in postorder
void AVLTree::printPostorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    printPostorder(r->left, isFirst);
    printPostorder(r->right, isFirst);
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
}

// Prints the tree nodes in preorder
void AVLTree::printPreorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
    printPreorder(r->left, isFirst);
    printPreorder(r->right, isFirst);
}

// Prints the nodes at a given level in the tree
void AVLTree::printGivenLevel(TreeNode* r, int level) const {
    if (r == nullptr)
        return;
    else if (level == 0)
        std::cout << r->ufid << " ";
    else {
        printGivenLevel(r->left, level - 1);
        printGivenLevel(r->right, level - 1);
    }
}

// Searches for a node with a given value starting from a given root
TreeNode* AVLTree::recursiveSearch(TreeNode* r, std::string val) const {
    if (r == nullptr) {
        return nullptr;
    }

    if (val == r->ufid) {
        return r;
    } else if (val < r->ufid) {
        return recursiveSearch(r->left, val);
    } else {
        return recursiveSearch(r->right, val);
    }
}

// Update these function signatures to match the header file:
void AVLTree::searchID(std::string_view ufid) {
    TreeNode* result = recursiveSearch(this->root, std::string(ufid));
    if (result != nullptr) {
        std::cout << result->name << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::searchNAME(std::string_view name) {
    std::vector<std::string> ids;
    searchNAMEHelper(this->root, std::string(name), ids);
    if (!ids.empty()) {
        for (const std::string& id : ids) {
            std::cout << id << std::endl;
        }
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::searchNAMEHelper(TreeNode* r, const std::string& name, std::vector<std::string>& ids) const {
    if (r == nullptr) {
        return;
    }
    searchNAMEHelper(r->left, name, ids);
    if (r->name == name) {
        ids.push_back(r->ufid);
    }
    searchNAMEHelper(r->right, name, ids);
}