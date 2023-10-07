#include<iostream>
#include <sstream>
#include <vector>
//#include "AVL.h"
#define SPACE 10

using namespace std;

class TreeNode {
public:
    string name;
    string ufid;
    TreeNode * left;
    TreeNode * right;

    TreeNode() {
        name = "";
        ufid = "";
        left = NULL;
        right = NULL;
    }
    TreeNode(string n, string u) {
        name = n;
        ufid = u;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:
    TreeNode * root;
    AVLTree() {
        root = NULL;
    }

    bool isTreeEmpty() {
        if (root == NULL) {
            return true;
        } else {
            return false;
        }
    }

    // Get Height
    int height(TreeNode * N) {
        if (N == NULL)
            return 0;
        return max(height(N->left), height(N->right)) + 1;
    }

    int getBalanceFactor(TreeNode * N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    TreeNode * rightRotate(TreeNode * y) {
        TreeNode * x = y->left;
        TreeNode * T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    TreeNode * leftRotate(TreeNode * x) {
        TreeNode * y = x->right;
        TreeNode * T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    TreeNode * insert(TreeNode * r, TreeNode * new_node) {
        int new_value = std::stoi(new_node->ufid);
        if (r == NULL) {
            r = new_node;
            cout << "Value inserted successfully" << endl;
            return r;
        }

        int r_value = std::stoi(r->ufid);
        if (new_value < r_value) {
            r->left = insert(r->left, new_node);
        } else if (new_value > r_value) {
            r->right = insert(r->right, new_node);
        } else {
            cout << "No duplicate UFID allowed!" << endl;
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

    TreeNode * minValueNode(TreeNode * node) {
        TreeNode * current = node;
        /* loop down to find the leftmost leaf */
        while (current -> left != NULL) {
            current = current -> left;
        }
        return current;
    }

    TreeNode * deleteNode(TreeNode * r, int v) {
        // Convert string to integer for comparison

        // base case
        if (r == NULL) {
            return NULL;
        }

        // Convert root's ufid to integer for comparison
        int r_value = std::stoi(r->ufid);

        // If the key to be deleted is smaller than the root's key,
        // then it lies in the left subtree
        if (v < r_value) {
            r->left = deleteNode(r->left, v);
        }
            // If the key to be deleted is greater than the root's key,
            // then it lies in the right subtree
        else if (v > r_value) {
            r->right = deleteNode(r->right, v);
        }
            // if key is the same as root's key, then this is the node to be deleted
        else {
            // node with only one child or no child
            if (r->left == NULL) {
                TreeNode * temp = r->right;
                delete r;
                return temp;
            } else if (r->right == NULL) {
                TreeNode * temp = r->left;
                delete r;
                return temp;
            } else {
                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                TreeNode * temp = minValueNode(r->right);
                // Copy the inorder successor's content to this node
                r->ufid = temp->ufid;
                // Delete the inorder successor
                r->right = deleteNode(r->right, std::stoi(temp->ufid));
            }
        }

        int bf = getBalanceFactor(r);
        // Left Left Imbalance/Case or Right rotation
        if (bf == 2 && getBalanceFactor(r -> left) >= 0)
            return rightRotate(r);
            // Left Right Imbalance/Case or LR rotation
        else if (bf == 2 && getBalanceFactor(r -> left) == -1) {
            r -> left = leftRotate(r -> left);
            return rightRotate(r);
        }
            // Right Right Imbalance/Case or Left rotation
        else if (bf == -2 && getBalanceFactor(r -> right) <= -0)
            return leftRotate(r);
            // Right Left Imbalance/Case or RL rotation
        else if (bf == -2 && getBalanceFactor(r -> right) == 1) {
            r -> right = rightRotate(r -> right);
            return leftRotate(r);
        }

        return r;
    }

    void printInorder(TreeNode * r, bool &isFirst) {
        if (r == NULL)
            return;
        printInorder(r->left, isFirst);
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
        printInorder(r->right, isFirst);
    }


    void printPostorder(TreeNode * r, bool &isFirst) {
        if (r == NULL)
            return;
        printPostorder(r->left, isFirst);
        printPostorder(r->right, isFirst);
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
    }

    void printPreorder(TreeNode * r, bool &isFirst) {
        if (r == NULL)
            return;
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
        printPreorder(r->left, isFirst);
        printPreorder(r->right, isFirst);
    }



    // Print nodes at a given level
    void printGivenLevel(TreeNode * r, int level) {
        if (r == NULL)
            return;
        else if (level == 0)
            cout << r -> ufid << " ";
        else // level > 0
        {
            printGivenLevel(r -> left, level - 1);
            printGivenLevel(r -> right, level - 1);
        }
    }

    void printLevelOrderBFS(TreeNode * r) {
        int h = height(r);
        for (int i = 0; i <= h; i++)
            printGivenLevel(r, i);
    }

    TreeNode * iterativeSearch(int v) {
        if (root == NULL) {
            return root;
        } else {
            TreeNode * temp = root;
            while (temp != NULL) {
                if (v == std::stoi(temp->ufid)) {
                    return temp;
                } else if (v < std::stoi(temp->ufid)) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
            return NULL;
        }
    }

    TreeNode * recursiveSearch(TreeNode * r, int val) {
        if (r == NULL || std::stoi(r->ufid))
            return r;

        else if (val < std::stoi(r->ufid))
            return recursiveSearch(r -> left, val);

        else
            return recursiveSearch(r -> right, val);
    }
};



int main() {
    AVLTree avl;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "insert") {
            string remaining_line;
            getline(ss, remaining_line);
            size_t last_quote = remaining_line.find_last_of("\"");
            string name = remaining_line.substr(1, last_quote - 1);
            string ufid = remaining_line.substr(last_quote + 2);

            // Validate that the name contains only alphabetic characters
            bool validName = true;
            for (char c : name) {
                if (isdigit(c)) {
                    validName = false;
                    break;
                }
            }

            if (validName) {
                TreeNode* newNode = new TreeNode(name, ufid);
                avl.root = avl.insert(avl.root, newNode);
            } else {
                cout << "Invalid name. Only alphabetic characters are allowed." << endl;
            }
        } else if (command == "printInorder") {
            bool isFirst = true;
            avl.printInorder(avl.root, isFirst);
            cout << endl;

        } else if (command == "printPreorder") {
            bool isFirst = true;
            avl.printPreorder(avl.root, isFirst);
            cout << endl;

        } else if (command == "printPostorder") {
            bool isFirst = true;
            avl.printPostorder(avl.root, isFirst);
            cout << endl;

        } else if (command == "remove") {
            int ufid;
            ss >> ufid;
            avl.root = avl.deleteNode(avl.root, ufid);
            cout << "successful" << endl;

        } else if (command == "removeInorder") {
            int position;
            ss >> position;
            // You'll need to implement a function to remove a node by inorder position
            // avl.removeInorder(position);
            cout << "successful" << endl;

        } else {
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}