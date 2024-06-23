#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>  
#include <ctime>    
#include <sstream>
#include <string_view> // Added for more efficient string handling

class TreeNode {
public:
    std::string name;
    std::string ufid;
    TreeNode* left;
    TreeNode* right;

    TreeNode();
    TreeNode(std::string n, std::string u);
};

class AVLTree {
public:
    TreeNode* root;

    AVLTree();
    void printLevelCount() const;
    int height(TreeNode* N) const;
    int getBalanceFactor(TreeNode* N) const;
    TreeNode* rightRotate(TreeNode* y);
    TreeNode* leftRotate(TreeNode* x);
    // Modified to take name and ufid directly for efficiency
    TreeNode* insert(TreeNode* r, const std::string& name, const std::string& ufid);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* r, int v);
    // Removed inorderTraversal and added findNthInorder for more efficient removeInorder
    TreeNode* findNthInorder(TreeNode* root, int n, int& count);

    void removeInorder(TreeNode*& root, int n);
    void printInorder(TreeNode* r, bool& isFirst) const;
    void printPostorder(TreeNode* r, bool& isFirst) const;
    void printPreorder(TreeNode* r, bool& isFirst) const;
    void printGivenLevel(TreeNode* r, int level) const;
    TreeNode* recursiveSearch(TreeNode* r, std::string val) const;
    // Modified to use string_view for more efficient string handling
    void searchID(std::string_view ufid);
    void searchNAME(std::string_view name);
    // Modified to be const as it doesn't modify the tree
    void searchNAMEHelper(TreeNode* r, const std::string& name, std::vector<std::string>& ids) const;

        // void inorderTraversal(TreeNode* r, std::vector<TreeNode*>& nodes) const;
};

#endif