#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
#include <algorithm> // for std::max

using namespace std;

const int SPACE = 5;  // For pretty printing the tree

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
        return root == NULL;
    }

    void insert(string name, string ufid);
    TreeNode * deleteNode(TreeNode * r, int v);
    void printPreorder(TreeNode * r, bool isFirst = true);
    void printInorder(TreeNode * r, bool isFirst = true);
    void printPostorder(TreeNode * r, bool isFirst = true);

private:
    int height(TreeNode * N);
    int getBalanceFactor(TreeNode * N);
    TreeNode * rightRotate(TreeNode * y);
    TreeNode * leftRotate(TreeNode * x);
    TreeNode * insertHelper(TreeNode * r, string name, string ufid);
    TreeNode * minValueNode(TreeNode * node);
    void print2D(TreeNode * r, int space);
    void printGivenLevel(TreeNode * r, int level);
    void printLevelOrderBFS(TreeNode * r);
    TreeNode * iterativeSearch(int v);
    TreeNode * recursiveSearch(TreeNode * r, int val);
};

#endif // AVL_H