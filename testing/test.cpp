#include "../src/AVL.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

// Helper class to capture and check cout output
// CaptureOutput: A helper class that temporarily redirects std::cout to a stringstream for testing output
// Prevents output from cluttering the console during testing
class CaptureOutput {
public:
    CaptureOutput() : old_cout(std::cout.rdbuf(ss.rdbuf())) {}
    ~CaptureOutput() { std::cout.rdbuf(old_cout); }
    std::string get() { return ss.str(); }
    void clear() { ss.str(""); }

private:
    std::stringstream ss;
    std::streambuf* old_cout;
};

// Insertion tests are grouped together because they all test the functionality
// of adding new nodes to the AVL tree. This includes testing successful insertions,
// multiple insertions, and attempting to insert duplicate keys.
TEST_CASE("AVL Tree Insertion", "[AVLTree]") {
    AVLTree tree;
    CaptureOutput capture;

    SECTION("Insert single node") {
        tree.root = tree.insert(tree.root, "Adam", "12345678");
        REQUIRE(capture.get() == "successful\n");
    }

    SECTION("Insert multiple nodes") {
        tree.root = tree.insert(tree.root, "David", "31239830");
        tree.root = tree.insert(tree.root, "Danielle", "27782901");
        tree.root = tree.insert(tree.root, "David", "11133245");
        REQUIRE(capture.get() == "successful\nsuccessful\nsuccessful\n");
    }

    SECTION("Insert duplicate UFID") {
        tree.root = tree.insert(tree.root, "Adam", "12345678");
        capture.clear();
        tree.root = tree.insert(tree.root, "Eve", "12345678");
        REQUIRE(capture.get() == "unsuccessful\n");
    }
}

// Search tests are grouped together because they all test the tree's ability
// to find nodes based on either UFID or name. This includes testing for both
// existing and non-existing entries.
TEST_CASE("AVL Tree Search", "[AVLTree]") {
    AVLTree tree;
    CaptureOutput capture;

    tree.root = tree.insert(tree.root, "Adam", "12345678");
    tree.root = tree.insert(tree.root, "David", "31239830");
    tree.root = tree.insert(tree.root, "Danielle", "27782901");
    capture.clear();

    SECTION("Search by ID - Existing") {
        tree.searchID("12345678");
        REQUIRE(capture.get() == "Adam\n");
    }

    SECTION("Search by ID - Non-existing") {
        tree.searchID("99999999");
        REQUIRE(capture.get() == "unsuccessful\n");
    }

    SECTION("Search by Name - Existing") {
        tree.searchNAME("Danielle");
        REQUIRE(capture.get() == "27782901\n");
    }

    SECTION("Search by Name - Non-existing") {
        tree.searchNAME("Eve");
        REQUIRE(capture.get() == "unsuccessful\n");
    }
}

// Deletion tests are grouped together because they all test the removal of nodes
// from the AVL tree. This includes testing direct deletion by UFID and removal
// by inorder position, as well as attempting to delete non-existing nodes.
TEST_CASE("AVL Tree Deletion", "[AVLTree]") {
    AVLTree tree;
    CaptureOutput capture;

    tree.root = tree.insert(tree.root, "Brandon", "45674567");
    tree.root = tree.insert(tree.root, "Brian", "35455565");
    tree.root = tree.insert(tree.root, "Briana", "87878787");
    tree.root = tree.insert(tree.root, "Bella", "95462138");
    capture.clear();

    SECTION("Delete existing node") {
        tree.root = tree.deleteNode(tree.root, 45674567);
        REQUIRE(capture.get() == "successful\n");
    }

    SECTION("Delete non-existing node") {
        tree.root = tree.deleteNode(tree.root, 11111111);
        REQUIRE(capture.get() == "unsuccessful\n");
    }

    SECTION("Remove inorder") {
        tree.removeInorder(tree.root, 2);
        capture.clear();
        bool isFirst = true;
        tree.printInorder(tree.root, isFirst);
        REQUIRE(capture.get() == "Brian, Brandon, Bella\n");
    }
}

// Traversal tests are grouped together because they all test different methods
// of traversing the AVL tree (inorder, preorder, postorder). These tests ensure
// that the tree structure is correct and that nodes are visited in the expected order.
TEST_CASE("AVL Tree Traversal", "[AVLTree]") {
    AVLTree tree;
    CaptureOutput capture;

    tree.root = tree.insert(tree.root, "Caroline", "50005000");
    tree.root = tree.insert(tree.root, "Cory", "35354334");
    tree.root = tree.insert(tree.root, "Cecilia", "76543210");
    tree.root = tree.insert(tree.root, "Carla", "56567342");
    tree.root = tree.insert(tree.root, "Cody", "83711221");
    tree.root = tree.insert(tree.root, "Chris", "17449900");
    capture.clear();

    SECTION("Inorder Traversal") {
        bool isFirst = true;
        tree.printInorder(tree.root, isFirst);
        REQUIRE(capture.get() == "Chris, Cory, Caroline, Carla, Cecilia, Cody\n");
    }

    SECTION("Preorder Traversal") {
        bool isFirst = true;
        tree.printPreorder(tree.root, isFirst);
        REQUIRE(capture.get() == "Caroline, Cory, Chris, Cecilia, Carla, Cody\n");
    }

    SECTION("Postorder Traversal") {
        bool isFirst = true;
        tree.printPostorder(tree.root, isFirst);
        REQUIRE(capture.get() == "Chris, Cory, Carla, Cody, Cecilia, Caroline\n");
    }
}

// Level Count tests are grouped together because they specifically test the height
// or number of levels in the AVL tree. This includes testing an empty tree and
// a tree with multiple nodes to ensure that the balancing property of the AVL tree
// is maintained.
TEST_CASE("AVL Tree Level Count", "[AVLTree]") {
    AVLTree tree;
    CaptureOutput capture;

    SECTION("Level count for empty tree") {
        tree.printLevelCount();
        REQUIRE(capture.get() == "0\n");
    }

    SECTION("Level count for non-empty tree") {
        tree.root = tree.insert(tree.root, "Evan", "44985771");
        tree.root = tree.insert(tree.root, "Earl", "31834874");
        tree.root = tree.insert(tree.root, "Erica", "21456789");
        capture.clear();
        tree.printLevelCount();
        REQUIRE(capture.get() == "2\n");

        tree.root = tree.insert(tree.root, "Enrique", "17891824");
        capture.clear();
        tree.printLevelCount();
        REQUIRE(capture.get() == "3\n");
    }
}