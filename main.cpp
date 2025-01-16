/**
* COP3503 - Project 1 - Gator AVL Tree
* @author Preston Hemmy
* @version 2.0
*/

#include "tree.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isValidName(const string& name) {
    bool hasAlpha = false;
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
        if (isalpha(c)) {
            hasAlpha = true;
        }
    }
    return hasAlpha;
}

bool isValidID(int id) {
    string idStr = to_string(id);
    return idStr.length() == 8;
}

int main() {
    AVLTree tree;

    cout << "Usage:\n\n"

         << "\tinsert <name> <id>\n"
         << "\tsearch <id>\n"
         << "\tsearch <name>\n"
         << "\tremove <id>\n"
         << "\tremoveInorder <n>\n"
         << "\tprintInorder\n"
         << "\tprintPreorder\n"
         << "\tprintPostorder\n"
         << "\tprintLevelCount\n\n"

         << "\tNames may contain spaces and should be placed in double quotation marks.\n"
         << "\tIDs must be eight digits.\n"
         << "\tThe first input denotes the number of lines or the total number of commands that follow.\n\n";

    int num_commands;
    cin >> num_commands;
    cin.ignore();

    for (int i = 0; i < num_commands; i++) {
        string command;
        getline(cin, command);

        istringstream iss(command);
        string operation;
        iss >> operation;

        if (operation == "insert") {
            string name;
            int id;

            iss.ignore();
            iss.ignore();
            getline(iss, name, '"');
            iss.ignore();

            iss >> id;

            if (isValidName(name) && isValidID(id)) {
                tree.insert(name, id);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (operation == "remove") {
            int id;
            iss >> id;

            if (isValidID(id)) {
                tree.remove(id);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (operation == "search") {
            string query;
            iss >> query;

            if (query[0] == '"') {
                query = query.substr(1, query.length() - 2);
                vector<int> ids = tree.search(query);
                if (!ids.empty()) {
                    for (int id : ids) {
                        cout << id << endl;
                    }
                } else {
                    cout << "unsuccessful" << endl;
                }
            } else {
                int id = stoi(query);
                if (isValidID(id)) {
                    string result = tree.search(id);
                    if (!result.empty()) {
                        cout << result << endl;
                    } else {
                        cout << "unsuccessful" << endl;
                    }
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        } else if (operation == "printInorder") {
            cout << tree.printInorder() << endl;
        } else if (operation == "printPreorder") {
            cout << tree.printPreorder() << endl;
        } else if (operation == "printPostorder") {
            cout << tree.printPostorder() << endl;
        } else if (operation == "printLevelCount") {
            cout << tree.printLevelCount() << endl;
        } else if (operation == "removeInorder") {
            int n;
            iss >> n;

            if (n >= 0) {
                tree.removeInorder(n);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}
