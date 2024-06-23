#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map> // Added for more efficient command dispatching
#include "AVL.h"

// Function prototypes for command handlers
void handleInsert(AVLTree& avl, std::stringstream& ss);
void handleRemove(AVLTree& avl, std::stringstream& ss);
void handleSearch(AVLTree& avl, std::stringstream& ss);

int main() {
    AVLTree avl;
    int numCommands;
    std::cin >> numCommands;
    std::cin.ignore();

    // Added command map for more efficient dispatching
    std::unordered_map<std::string, void(*)(AVLTree&, std::stringstream&)> commandMap = {
        {"insert", handleInsert},
        {"remove", handleRemove},
        {"search", handleSearch}
    };

    for (int i = 0; i < numCommands; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (commandMap.find(command) != commandMap.end()) {
            commandMap[command](avl, ss);
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
        } else if (command == "removeInorder") {
            int position;
            ss >> position;
            avl.removeInorder(avl.root, position);
        } else if (command == "printLevelCount") {
            avl.printLevelCount();
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
    return 0;
}

// Separated command handlers for cleaner main function
void handleInsert(AVLTree& avl, std::stringstream& ss) {
    std::string remaining_line;
    std::getline(ss, remaining_line);

    size_t last_quote = remaining_line.find_last_of("\"");
    std::string name = remaining_line.substr(2, last_quote - 2);
    std::string ufid = remaining_line.substr(last_quote + 2);

    bool validName = true;
    for (char c : name) {
        if (!std::isalpha(c) && c != ' ') {
            validName = false;
            break;
        }
    }

    bool validUFID = ufid.length() == 8;
    for (char c : ufid) {
        if (!std::isdigit(c)) {
            validUFID = false;
            break;
        }
    }

    if (validName && validUFID) {
        avl.root = avl.insert(avl.root, name, ufid);
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void handleRemove(AVLTree& avl, std::stringstream& ss) {
    int ufid;
    ss >> ufid;
    TreeNode* newRoot = avl.deleteNode(avl.root, ufid);
    if (newRoot != nullptr) {
        avl.root = newRoot;
        std::cout << "successful" << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

void handleSearch(AVLTree& avl, std::stringstream& ss) {
    std::string remaining_line;
    std::getline(ss, remaining_line);
    if (remaining_line.find("\"") != std::string::npos) {
        size_t first_quote = remaining_line.find_first_of("\"");
        size_t last_quote = remaining_line.find_last_of("\"");
        std::string name = remaining_line.substr(first_quote + 1, last_quote - first_quote - 1);
        avl.searchNAME(name);
    } else {
        std::stringstream ss_remaining(remaining_line);
        std::string ufid;
        ss_remaining >> ufid;
        if (ufid.length() == 8) {
            avl.searchID(ufid);
        } else {
            std::cout << "unsuccessful" << std::endl;
        }
    }
}