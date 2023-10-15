#include<iostream>
#include <sstream>
#include <vector>

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
        left = nullptr;
        right = nullptr;
    }
    TreeNode(string n, string u) {
        name = n;
        ufid = u;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
public:
    TreeNode * root;
    AVLTree() {
        root = nullptr;
    }

    // Print Level Count
    void printLevelCount() {
        int levels = height(this->root);  // Assuming this->root is the root of your AVL tree
        cout << levels << endl;
    }

    // Get Height
    int height(TreeNode * N) {
        if (N == nullptr)
            return 0;
        return max(height(N->left), height(N->right)) + 1;
    }

    int getBalanceFactor(TreeNode * N) {
        if (N == nullptr)
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

    // Inserts a new node into the AVL tree and balances it
    TreeNode * insert(TreeNode * r, TreeNode * new_node) {
        int new_value = std::stoi(new_node->ufid);
        if (r == nullptr) {
            r = new_node;
            cout << "successful" << endl;
            return r;
        }

        int r_value = std::stoi(r->ufid);
        if (new_value < r_value) {
            r->left = insert(r->left, new_node);
        } else if (new_value > r_value) {
            r->right = insert(r->right, new_node);
        } else {
            cout << "unsuccessful" << endl;
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
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    // Deletes a node from the AVL tree and balances it
    TreeNode * deleteNode(TreeNode * r, int v) {
        // Convert string to integer for comparison

        // base case
        if (r == nullptr) {
            return nullptr;
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
            if (r->left == nullptr) {
                TreeNode * temp = r->right;
                delete r;
                return temp;
            } else if (r->right == nullptr) {
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

    // Performs an in-order traversal and stores the nodes in a vector
    void inorderTraversal(TreeNode* r, vector<TreeNode*>& nodes) {
        if (r == nullptr) {
            return;
        }
        inorderTraversal(r->left, nodes);
        nodes.push_back(r);
        inorderTraversal(r->right, nodes);
    }

    // Removes the nth node in an in-order traversal
    void removeInorder(TreeNode*& root, int n) {
        vector<TreeNode*> nodes;
        inorderTraversal(root, nodes);
        if (n >= 0 && n < nodes.size()) {
            int ufid = std::stoi(nodes[n]->ufid);
            root = deleteNode(root, ufid);
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Prints the tree in in-order traversal
    void printInorder(TreeNode * r, bool &isFirst) {
        if (r == nullptr)
            return;
        printInorder(r->left, isFirst);
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
        printInorder(r->right, isFirst);
    }

    // Prints the tree in post-order traversal
    void printPostorder(TreeNode * r, bool &isFirst) {
        if (r == nullptr)
            return;
        printPostorder(r->left, isFirst);
        printPostorder(r->right, isFirst);
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
    }

    // Prints the tree in pre-order traversal
    void printPreorder(TreeNode * r, bool &isFirst) {
        if (r == nullptr)
            return;
        if (!isFirst) cout << ", ";
        cout << r->name;
        isFirst = false;
        printPreorder(r->left, isFirst);
        printPreorder(r->right, isFirst);
    }

    // Print nodes at a given level
    void printGivenLevel(TreeNode * r, int level) {
        if (r == nullptr)
            return;
        else if (level == 0)
            cout << r -> ufid << " ";
        else // level > 0
        {
            printGivenLevel(r -> left, level - 1);
            printGivenLevel(r -> right, level - 1);
        }
    }

    // Searches for a node by its UFID
    TreeNode * recursiveSearch(TreeNode * r, string val) {
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

    // Searches for a node by its UFID and prints its name
    void searchID(string ufid) {
        TreeNode *result = recursiveSearch(this->root, ufid);
        if (result != nullptr) {
            cout << result->name << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Searches for nodes by their name and prints their UFIDs
    void searchNAME(string name) {
        vector<string> ids;
        searchNAMEHelper(this->root, name, ids);
        if (!ids.empty()) {
            for (const string &id : ids) {
                cout << id << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Helper function for searchNAME
    void searchNAMEHelper(TreeNode * r, const string & name, vector<string> &ids) {
        if (r == NULL) {
            return;
        }
        searchNAMEHelper(r->left, name, ids);
        if (r->name == name) {
            ids.push_back(r->ufid);
        }
        searchNAMEHelper(r->right, name, ids);
    }

};

int main() {
    AVLTree avl;  // Create an AVL tree object
    int numCommands;  // Variable to store the number of commands

    // Read the number of commands and ignore it
    cin >> numCommands;
    cin.ignore();  // Clear the newline character from the input buffer

    // Loop to read and execute each command
    for (int i = 0; i < numCommands; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "insert") {
            string remaining_line;
            getline(ss, remaining_line);

            size_t last_quote = remaining_line.find_last_of("\"");

            string name = remaining_line.substr(2, last_quote - 2);
            string ufid = remaining_line.substr(last_quote + 2);

            // Validate that the name contains only alphabetic characters
            bool validName = true;
            for (char c : name) {
                if (isdigit(c)) {
                    validName = false;
                    break;
                }
            }

            // Validate that the UFID is exactly 8 digits and numeric
            bool validUFID = ufid.length() == 8;
            for (char c : ufid) {
                if (!isdigit(c)) {
                    validUFID = false;
                    break;
                }
            }

            if (validName && validUFID) {
                TreeNode* newNode = new TreeNode(name, ufid);
                avl.root = avl.insert(avl.root, newNode);
            } else {
                cout << "unsuccessful" << endl;
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
            TreeNode* newRoot = avl.deleteNode(avl.root, ufid);
            if (newRoot != NULL) {
                avl.root = newRoot;
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }


        } else if (command == "removeInorder") {
            int position;
            ss >> position;
            avl.removeInorder(avl.root, position);


        } else if (command == "search") {
            string remaining_line;
            getline(ss, remaining_line);
            if (remaining_line.find("\"") != string::npos) {  // Search by name
                size_t first_quote = remaining_line.find_first_of("\"");
                size_t last_quote = remaining_line.find_last_of("\"");
                string name = remaining_line.substr(first_quote + 1, last_quote - first_quote - 1);
                avl.searchNAME(name);
            } else {  // Search by UFID
                stringstream ss_remaining(remaining_line);
                string ufid;
                ss_remaining >> ufid;
                if (ufid.length() == 8) {
                    avl.searchID(ufid);
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        } else if (command == "printLevelCount") {
            avl.printLevelCount();  // Assuming printLevelCount is a member function of AVLTree
        } else {
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}