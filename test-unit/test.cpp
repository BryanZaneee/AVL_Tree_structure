#include "../src/AVL.h"
#include <catch2/catch_test_macros.hpp>
#include <algorithm> // for std::sort
#include <cstdlib>   // for rand()
#include <ctime>     // for std::time()
#include <sstream>

TEST_CASE("AVL Tree Balancing", "[AVLTree]") {
AVLTree tree;

// Insert 8 nodes


// Check if the tree is balanced
REQUIRE(tree.isBalanced(tree.root) == true);

// REQUIRE(tree.printInorder() == "Expected inorder output");
// REQUIRE(tree.printPostorder() == "Expected postorder output");
}

// print Inorder test
// prints the values "in order"
TEST_CASE("BST Insert Inorder", "[flag]"){
AVLTree inputTree;
inputTree.insert("Bobby purple", "68580002");
inputTree.insert("Bobby brown", "18580000");
inputTree.insert("Bobby blue", "28580003");
inputTree.insert("Bobby green", "48580002");
inputTree.insert("Bobby yellow", "58580002");
inputTree.insert("Bobby red", "38580002");
std::string actualOutput = inputTree.printInorder();
std::string expectedOutput = "Bobby brown, Bobby blue, Bobby red, Bobby green, Bobby yellow, Bobby purple";
REQUIRE(actualOutput == expectedOutput);
}

// print Preorder test
// Root node first, then the left subtree, and then the right subtree
TEST_CASE("BST Insert Preorder", "[flag]"){
AVLTree inputTree;
inputTree.insert("Bobby purple", "68580002");
inputTree.insert("Bobby brown", "18580000");
inputTree.insert("Bobby blue", "28580003");
inputTree.insert("Bobby green", "48580002");
inputTree.insert("Bobby yellow", "58580002");
inputTree.insert("Bobby red", "38580002");
std::string actualOutput = inputTree.printPreorder();
std::string expectedOutput = "Bobby red, Bobby blue, Bobby brown, Bobby green, Bobby yellow, Bobby purple";
REQUIRE(actualOutput == expectedOutput);
}

// print Postorder test
// visit left subtree first, then right subtree, then the root node
TEST_CASE("BST Insert Postorder", "[flag]"){
AVLTree inputTree;
inputTree.insert("Bobby purple", "68580002");
inputTree.insert("Bobby brown", "18580000");
inputTree.insert("Bobby blue", "28580003");
inputTree.insert("Bobby green", "48580002");
inputTree.insert("Bobby yellow", "58580002");
inputTree.insert("Bobby red", "38580002");
std::string actualOutput = inputTree.printPostorder();
std::string expectedOutput = "Bobby brown, Bobby blue, Bobby purple, Bobby yellow, Bobby green, Bobby red";
REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Incorrect Commands", "[AVLTree]") {
AVLTree tree;
// Test 5 incorrect commands
REQUIRE(tree.insert("A11y", "45679999") == false);  // Contains a number in the name
REQUIRE(tree.insert("Ally", "45a7999") == false);   // Contains a letter in the UFID
REQUIRE(tree.insert("", "45679999") == false);       // Empty name
REQUIRE(tree.insert("Ally", "") == false);           // Empty UFID
REQUIRE(tree.insert("Ally", "45679999") == false);   // Duplicate UFID
}

TEST_CASE("Edge Cases", "[AVLTree]") {
AVLTree tree;
// Test 3 edge cases
REQUIRE(tree.deleteNode(tree.root, 123456) == false);  // Removing a node that doesn't exist
REQUIRE(tree.insert("Ally", "45679999") == true);      // Inserting a node with maximum UFID
REQUIRE(tree.insert("Ally", "00000000") == true);      // Inserting a node with minimum UFID
}

TEST_CASE("Rotation Cases", "[AVLTree]") {
AVLTree tree;
// Test all four rotation cases
// You'll need to implement a function to check the type of rotation performed
// and return a string or enum indicating the rotation
// REQUIRE(tree.checkRotationType(...) == "LL");
// REQUIRE(tree.checkRotationType(...) == "RR");
// REQUIRE(tree.checkRotationType(...) == "LR");
// REQUIRE(tree.checkRotationType(...) == "RL");
}

TEST_CASE("Deletion Cases", "[AVLTree]") {
AVLTree tree;
// Test all three deletion cases
// You'll need to implement a function to check the type of deletion performed
// and return a string or enum indicating the deletion
// REQUIRE(tree.checkDeletionType(...) == "NoChildren");
// REQUIRE(tree.checkDeletionType(...) == "OneChild");
// REQUIRE(tree.checkDeletionType(...) == "TwoChildren");
}

TEST_CASE("Bulk Insert and Delete", "[AVLTree]") {
AVLTree tree;
// Insert 100 nodes
for (int i = 1; i <= 100; ++i) {
std::string ufid = std::to_string(i);
REQUIRE(tree.insert("Node" + ufid, ufid) == true);
}
// Remove 10 random nodes
for (int i = 1; i <= 10; ++i) {
int ufid = rand() % 100 + 1;
REQUIRE(tree.deleteNode(tree.root, ufid) == true);
}
// Check in order
// You'll need to implement a function to return the inorder traversal as a string
// std::string actualOutput = tree.printInorder();
// std::string expectedOutput = "The expected inorder output after deletions";
// REQUIRE(actualOutput == expectedOutput);
}

//TEST_CASE("BST Insert Large", "[flag]"){
//    std::srand(std::time(nullptr)); // set seed for random number generation
//    AVLTree inputTree;
//    std::vector<string> expectedOutputVec;
//    std::string actualOutput, expectedOutput;
//
//    for(int i = 0; i < 100000; i++) {
//        int randomInput = rand();
//        string randomInputStr = to_string(randomInput);
//        if (std::count(expectedOutputVec.begin(), expectedOutputVec.end(), randomInputStr) == 0) {
//            expectedOutputVec.push_back(randomInputStr);
//            inputTree.insert("Random Name", randomInputStr);
//        }
//    }
//
//    std::sort(expectedOutputVec.begin(), expectedOutputVec.end());
//
//    // Convert expectedOutputVec to a comma-separated string
//    std::ostringstream oss;
//    for (size_t i = 0; i < expectedOutputVec.size(); ++i) {
//        oss << expectedOutputVec[i];
//        if (i != expectedOutputVec.size() - 1) {
//            oss << ", ";
//        }
//    }
//    expectedOutput = oss.str();
//
//    actualOutput = inputTree.printInorder();
//    REQUIRE(actualOutput == expectedOutput);
//}
