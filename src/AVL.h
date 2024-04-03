#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>  
#include <ctime>    
#include <sstream>

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
    TreeNode* insert(TreeNode* r, TreeNode* new_node);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* r, int v);
    void inorderTraversal(TreeNode* r, std::vector<TreeNode*>& nodes);
    void removeInorder(TreeNode*& root, int n);
    void printInorder(TreeNode* r, bool& isFirst) const;
    void printPostorder(TreeNode* r, bool& isFirst) const;
    void printPreorder(TreeNode* r, bool& isFirst) const;
    void printGivenLevel(TreeNode* r, int level) const;
    TreeNode* recursiveSearch(TreeNode* r, std::string val) const;
    void searchID(std::string ufid);
    void searchNAME(std::string name);
    void searchNAMEHelper(TreeNode* r, const std::string& name, std::vector<std::string>& ids);
};

#endif