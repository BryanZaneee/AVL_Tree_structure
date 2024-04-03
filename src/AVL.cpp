#include "AVL.h"
#include <iostream>
#include <algorithm>

TreeNode::TreeNode() {
    name = "";
    ufid = "";
    left = nullptr;
    right = nullptr;
}

TreeNode::TreeNode(std::string n, std::string u) {
    name = n;
    ufid = u;
    left = nullptr;
    right = nullptr;
}

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::printLevelCount() const {
    int levels = height(this->root);  // Assuming this->root is the root of your AVL tree
    std::cout << levels << std::endl;
}

int AVLTree::height(TreeNode* N) const {
    if (N == nullptr)
        return 0;
    return std::max(height(N->left), height(N->right)) + 1;
}

int AVLTree::getBalanceFactor(TreeNode* N) const {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

TreeNode* AVLTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

TreeNode* AVLTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

TreeNode* AVLTree::insert(TreeNode* r, TreeNode* new_node) {
    int new_value = std::stoi(new_node->ufid);
    if (r == nullptr) {
        r = new_node;
        std::cout << "successful" << std::endl;
        return r;
    }

    int r_value = std::stoi(r->ufid);
    if (new_value < r_value) {
        r->left = insert(r->left, new_node);
    } else if (new_value > r_value) {
        r->right = insert(r->right, new_node);
    } else {
        std::cout << "unsuccessful" << std::endl;
        return r;
    }

    int bf = getBalanceFactor(r);
    if (bf > 1 && new_value < std::stoi(r->left->ufid))
        return rightRotate(r);
    if (bf < -1 && new_value > std::stoi(r->right->ufid))
        return leftRotate(r);
    if (bf > 1 && new_value > std::stoi(r->left->ufid)) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    if (bf < -1 && new_value < std::stoi(r->right->ufid)) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

TreeNode* AVLTree::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* AVLTree::deleteNode(TreeNode* r, int v) {
    if (r == nullptr) {
        return nullptr;
    }

    int r_value = std::stoi(r->ufid);

    if (v < r_value) {
        r->left = deleteNode(r->left, v);
    } else if (v > r_value) {
        r->right = deleteNode(r->right, v);
    } else {
        if (r->left == nullptr) {
            TreeNode* temp = r->right;
            delete r;
            return temp;
        } else if (r->right == nullptr) {
            TreeNode* temp = r->left;
            delete r;
            return temp;
        } else {
            TreeNode* temp = minValueNode(r->right);
            r->ufid = temp->ufid;
            r->name = temp->name;
            r->right = deleteNode(r->right, std::stoi(temp->ufid));
        }
    }

    int bf = getBalanceFactor(r);
    if (bf == 2 && getBalanceFactor(r->left) >= 0)
        return rightRotate(r);
    else if (bf == 2 && getBalanceFactor(r->left) == -1) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    } else if (bf == -2 && getBalanceFactor(r->right) <= -0)
        return leftRotate(r);
    else if (bf == -2 && getBalanceFactor(r->right) == 1) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

void AVLTree::inorderTraversal(TreeNode* r, std::vector<TreeNode*>& nodes) {
    if (r == nullptr) {
        return;
    }
    inorderTraversal(r->left, nodes);
    nodes.push_back(r);
    inorderTraversal(r->right, nodes);
}

void AVLTree::removeInorder(TreeNode*& root, int n) {
    std::vector<TreeNode*> nodes;
    inorderTraversal(root, nodes);
    if (n >= 0 && n < nodes.size()) {
        int ufid = std::stoi(nodes[n]->ufid);
        root = deleteNode(root, ufid);
        std::cout << "successful" << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::printInorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    printInorder(r->left, isFirst);
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
    printInorder(r->right, isFirst);
}

void AVLTree::printPostorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    printPostorder(r->left, isFirst);
    printPostorder(r->right, isFirst);
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
}

void AVLTree::printPreorder(TreeNode* r, bool& isFirst) const {
    if (r == nullptr)
        return;
    if (!isFirst) std::cout << ", ";
    std::cout << r->name;
    isFirst = false;
    printPreorder(r->left, isFirst);
    printPreorder(r->right, isFirst);
}

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

void AVLTree::searchID(std::string ufid) {
    TreeNode* result = recursiveSearch(this->root, ufid);
    if (result != nullptr) {
        std::cout << result->name << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::searchNAME(std::string name) {
    std::vector<std::string> ids;
    searchNAMEHelper(this->root, name, ids);
    if (!ids.empty()) {
        for (const std::string& id : ids) {
            std::cout << id << std::endl;
        }
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void AVLTree::searchNAMEHelper(TreeNode* r, const std::string& name, std::vector<std::string>& ids) {
    if (r == NULL) {
        return;
    }
    searchNAMEHelper(r->left, name, ids);
    if (r->name == name) {
        ids.push_back(r->ufid);
    }
    searchNAMEHelper(r->right, name, ids);
}