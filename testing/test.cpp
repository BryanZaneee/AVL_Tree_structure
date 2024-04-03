#include "../src/AVL.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

TEST_CASE("AVL Tree Operations", "[AVLTree]") {
    AVLTree tree;
    std::stringstream ss;
    std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

    SECTION("File 1 Operations") {
        tree.searchID("12345678");
        REQUIRE(ss.str() == "unsuccessful\n");
        ss.str("");

        tree.searchNAME("Adam");
        REQUIRE(ss.str() == "unsuccessful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Adam", "12345678"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.searchID("23456789");
        REQUIRE(ss.str() == "unsuccessful\n");
        ss.str("");

        tree.searchID("12345678");
        REQUIRE(ss.str() == "Adam\n");
        ss.str("");
    }

    SECTION("File 2 Operations") {
        tree.root = tree.insert(tree.root, new TreeNode("David", "31239830"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Danielle", "27782901"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("David", "11133245"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.searchNAME("Danielle");
        REQUIRE(ss.str() == "27782901\n");
        ss.str("");

        tree.searchNAME("David");
        REQUIRE(ss.str() == "11133245\n31239830\n");
        ss.str("");
    }

     SECTION("File 3 Operations") {
        tree.root = tree.insert(tree.root, new TreeNode("Evan", "44985771"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Earl", "31834874"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Erica", "21456789"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.printLevelCount();
        REQUIRE(ss.str() == "2\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Enrique", "17891824"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.printLevelCount();
        REQUIRE(ss.str() == "3\n");
        ss.str("");
    }

    SECTION("File 4 Operations") {
        tree.root = tree.insert(tree.root, new TreeNode("Brandon", "45674567"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Brian", "35455565"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Briana", "87878787"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Bella", "95462138"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        bool isFirst = true;
        tree.printInorder(tree.root, isFirst);
        REQUIRE(ss.str() == "Brian, Brandon, Briana, Bella\n");
        ss.str("");

        tree.root = tree.deleteNode(tree.root, 45674567);
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.removeInorder(tree.root, 2);
        isFirst = true;
        tree.printInorder(tree.root, isFirst);
        REQUIRE(ss.str() == "Brian, Briana\n");
        ss.str("");
    }

    SECTION("File 5 Operations") {
        tree.root = tree.insert(tree.root, new TreeNode("Caroline", "50005000"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Cory", "35354334"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Cecilia", "76543210"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Carla", "56567342"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Cody", "83711221"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        tree.root = tree.insert(tree.root, new TreeNode("Chris", "17449900"));
        REQUIRE(ss.str() == "successful\n");
        ss.str("");

        bool isFirst = true;
        tree.printInorder(tree.root, isFirst);
        REQUIRE(ss.str() == "Chris, Cory, Caroline, Carla, Cecilia, Cody\n");
        ss.str("");

        isFirst = true;
        tree.printPreorder(tree.root, isFirst);
        REQUIRE(ss.str() == "Caroline, Cory, Chris, Cecilia, Carla, Cody\n");
        ss.str("");

        isFirst = true;
        tree.printPostorder(tree.root, isFirst);
        REQUIRE(ss.str() == "Chris, Cory, Carla, Cody, Cecilia, Caroline\n");
        ss.str("");
    }

    std::cout.rdbuf(old_cout); // Reset std::cout to its original buffer
}