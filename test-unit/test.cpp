//#include "../src/main.cpp"
//#include <catch2/catch_test_macros.hpp>
//#include <algorithm> // for std::sort
//#include <cstdlib>   // for rand()
//#include <ctime>     // for std::time()
//#include <sstream>
//TEST_CASE("Incorrect commands", "[AVLTree]") {
//    AVLTree tree;
//
//    SECTION("Insert with invalid name") {
//        tree.root = tree.insert(tree.root, new TreeNode("A11y", "45679999"));
//        REQUIRE(tree.root->name == "unsuccessful");
//    }
//    SECTION("Insert with empty name") {
//        tree.root = tree.insert(tree.root, new TreeNode("", "12345678"));
//        REQUIRE(tree.root->name == "unsuccessful");
//    }
//
//    SECTION("Insert with empty UFID") {
//        tree.root = tree.insert(tree.root, new TreeNode("John", ""));
//        REQUIRE(tree.root->name == "unsuccessful");
//    }
//
//    SECTION("Insert with negative UFID") {
//        tree.root = tree.insert(tree.root, new TreeNode("John", "-12345678"));
//        REQUIRE(tree.root->name == "unsuccessful");
//    }
//
//    SECTION("Insert with UFID containing letters") {
//        tree.root = tree.insert(tree.root, new TreeNode("John", "1234ABCD"));
//        REQUIRE(tree.root->name == "unsuccessful");
//    }
//}
//
//TEST_CASE("Edge cases", "[AVLTree]") {
//    AVLTree tree;
//
//    SECTION("Removing a node that doesn't exist") {
//        tree.root = tree.deleteNode(tree.root, 12345678);
//        REQUIRE(tree.root == nullptr);
//    }
//
//    SECTION("Removing a node that doesn't exist") {
//        tree.root = tree.deleteNode(tree.root, 99999999);
//        // Assuming you have a way to capture the output, check that it says "unsuccessful"
//    }
//
//    SECTION("Searching for a name that doesn't exist") {
//        tree.searchNAME("NonExistent");
//        // Assuming you have a way to capture the output, check that it says "unsuccessful"
//    }
//}
//
//TEST_CASE("Rotation cases", "[AVLTree]") {
//    AVLTree tree;
//
//    SECTION("Left-Left Rotation") {
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        tree.root = tree.insert(tree.root, new TreeNode("Charlie", "3"));
//        // Check that the tree is balanced and the root is now "Bob"
//        REQUIRE(tree.root->name == "Bob");
//    }
//
//    SECTION("Right-Right Rotation") {
//        tree.root = tree.insert(tree.root, new TreeNode("Charlie", "3"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        // Check that the tree is balanced and the root is now "Bob"
//        REQUIRE(tree.root->name == "Bob");
//    }
//
//    SECTION("Left-Right Rotation") {
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.insert(tree.root, new TreeNode("Charlie", "3"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        // Check that the tree is balanced and the root is now "Bob"
//        REQUIRE(tree.root->name == "Bob");
//    }
//
//    SECTION("Right-Left Rotation") {
//        tree.root = tree.insert(tree.root, new TreeNode("Charlie", "3"));
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        // Check that the tree is balanced and the root is now "Bob"
//        REQUIRE(tree.root->name == "Bob");
//    }
//}
//
//TEST_CASE("Deletion cases", "[AVLTree]") {
//    AVLTree tree;
//
//    SECTION("Delete node with no children") {
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.deleteNode(tree.root, std::stoi("1"));
//        // Check that the tree is empty
//        REQUIRE(tree.root == nullptr);
//    }
//
//    SECTION("Delete node with one child") {
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        tree.root = tree.deleteNode(tree.root, std::stoi("1"));
//        // Check that the tree now only contains "Bob"
//        REQUIRE(tree.root->name == "Bob");
//    }
//
//    SECTION("Delete node with two children") {
//        tree.root = tree.insert(tree.root, new TreeNode("Alice", "1"));
//        tree.root = tree.insert(tree.root, new TreeNode("Bob", "2"));
//        tree.root = tree.insert(tree.root, new TreeNode("Charlie", "3"));
//        tree.root = tree.deleteNode(tree.root, std::stoi("2"));
//        // Check that the tree now only contains "Alice" and "Charlie"
//        // And the root should be "Charlie"
//        REQUIRE(tree.root->name == "Charlie");
//    }
//}
//
//TEST_CASE("Bulk operations", "[AVLTree]") {
//    AVLTree tree;
//    SECTION("Insert 100 nodes and remove 10") {
//        // Insert 100 nodes
//        for (int i = 1; i <= 100; ++i) {
//            tree.root = tree.insert(tree.root, new TreeNode("Node" + std::to_string(i), std::to_string(i)));
//        }
//
//        // Remove 10 random nodes
//        std::vector<int> random_indices = {3, 7, 12, 19, 25, 33, 47, 56, 62, 78};
//        for (int index : random_indices) {
//            tree.root = tree.deleteNode(tree.root, index);
//        }
//
//        // Check in-order traversal
//        std::vector<TreeNode*> nodes;
//        tree.inorderTraversal(tree.root, nodes);
//        std::vector<int> remaining_values;
//        for (const auto& node : nodes) {
//            remaining_values.push_back(std::stoi(node->ufid));
//        }
//
//        // Create expected remaining values
//        std::vector<int> expected_remaining_values;
//        for (int i = 1; i <= 100; ++i) {
//            if (std::find(random_indices.begin(), random_indices.end(), i) == random_indices.end()) {
//                expected_remaining_values.push_back(i);
//            }
//        }
//
//        REQUIRE(remaining_values == expected_remaining_values);
//    }
//}