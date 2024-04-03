#include <iostream>
#include <sstream>
#include <string>
#include "AVL.h"

int main() {
    AVLTree avl;  // Create an AVL tree object
    int numCommands;  // Variable to store the number of commands

    // Read the number of commands and ignore it
    std::cin >> numCommands;
    std::cin.ignore();  // Clear the newline character from the input buffer

    // Loop to read and execute each command
    for (int i = 0; i < numCommands; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "insert") {
            std::string remaining_line;
            std::getline(ss, remaining_line);

            size_t last_quote = remaining_line.find_last_of("\"");

            std::string name = remaining_line.substr(2, last_quote - 2);
            std::string ufid = remaining_line.substr(last_quote + 2);

            // Validate that the name contains only alphabetic characters and spaces
            bool validName = true;
            for (char c : name) {
                if (!std::isalpha(c) && c != ' ') {  // Allow spaces along with alphabets
                    validName = false;
                    break;
                }
            }

            // Validate that the UFID is exactly 8 digits and numeric
            bool validUFID = ufid.length() == 8;
            for (char c : ufid) {
                if (!std::isdigit(c)) {
                    validUFID = false;
                    break;
                }
            }

            if (validName && validUFID) {
                TreeNode* newNode = new TreeNode(name, ufid);
                avl.root = avl.insert(avl.root, newNode);
            } else {
                std::cout << "unsuccessful" << std::endl;
            }
        } else if (command == "printInorder") {
            bool isFirst = true;
            avl.printInorder(avl.root, isFirst);
            std::cout << std::endl;

        } else if (command == "printPreorder") {
            bool isFirst = true;
            avl.printPreorder(avl.root, isFirst);
            std::cout << std::endl;

        } else if (command == "printPostorder") {
            bool isFirst = true;
            avl.printPostorder(avl.root, isFirst);
            std::cout << std::endl;

        } else if (command == "remove") {
            int ufid;
            ss >> ufid;
            TreeNode* newRoot = avl.deleteNode(avl.root, ufid);
            if (newRoot != NULL) {
                avl.root = newRoot;
                std::cout << "successful" << std::endl;
            } else {
                std::cout << "unsuccessful" << std::endl;
            }

        } else if (command == "removeInorder") {
            int position;
            ss >> position;
            avl.removeInorder(avl.root, position);

        } else if (command == "search") {
            std::string remaining_line;
            std::getline(ss, remaining_line);
            if (remaining_line.find("\"") != std::string::npos) {  // Search by name
                size_t first_quote = remaining_line.find_first_of("\"");
                size_t last_quote = remaining_line.find_last_of("\"");
                std::string name = remaining_line.substr(first_quote + 1, last_quote - first_quote - 1);
                avl.searchNAME(name);
            } else {  // Search by UFID
                std::stringstream ss_remaining(remaining_line);
                std::string ufid;
                ss_remaining >> ufid;
                if (ufid.length() == 8) {
                    avl.searchID(ufid);
                } else {
                    std::cout << "unsuccessful" << std::endl;
                }
            }
        } else if (command == "printLevelCount") {
            avl.printLevelCount();  // Assuming printLevelCount is a member function of AVLTree
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
    return 0;
}