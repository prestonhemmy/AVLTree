/**
* COP3503 - Project 1 - Gator AVL Tree
* @author Preston Hemmy
* @version 1.0
*/

#pragma once
#include <string>
#include <vector>

using namespace std;

class AVLTree {
private:
    struct Node {
        string name;
        int id;
        Node* left;
        Node* right;
        int height;

        Node(const string& name, int id);
    };

    Node* root;

    // Functions

    /**
     * This calculates the height of a given node in the AVL tree
     *
     * @param   node in AVL tree
     * @return  int height of given node
     * */
    int height(Node* node);

    /**
     * This function calculates the balance factor of a given node in the AVL tree
     *
     * @param   node in AVL tree
     * @return  int balance factor
     * */
    int balanceFactor(Node* node);

    /**
     * This function balances the AVL tree via left rotation
     *
     * @param   node to rotate
     * @return  Node* to rotated node
     * */
    Node* rotateLeft(Node* node);

    /**
     * This function balances the AVL tree via right rotation
     *
     * @param   node to rotate
     * @return  Node* to rotated node
     * */
    Node* rotateRight(Node* node);

    /**
     * This function balances the AVL tree via left-right rotation
     *
     * @param   node to rotate
     * @return  Node* to rotated node
     * */
    Node* rotateLeftRight(Node* node);

    /**
     * This function balances the AVL tree via right-left rotation
     *
     * @param   node to rotate
     * @return  Node* to rotated node
     * */
    Node* rotateRightLeft(Node* node);

    /**
     * This function recursively inserts a new node with given name and ID into the AVL tree, starting from the
     * specified node
     *
     * @param   node to start insertion from
     * @param   name of the student to insert
     * @param   id of the student to insert
     * @return  Node* to the inserted node
     * */
    Node* insert(Node* node, const string& name, int id);

    /**
     * This function recursively removes a node with the specified name and ID from the AVL tree, starting from the
     * given node
     *
     * @param   node to start removal from
     * @param   id of the student to remove
     * @return  Node* to the removed student
     * */
    Node* remove(Node* node, int id);

    /**
     * This function recursively searches for a node with the specified name and ID from the AVL tree, starting from the
     * given node
     * @param   node to start search from
     * @param   id of the student searching for
     * @return  Node* to the found student
     * */
    Node* search(Node* node, int id);

    /**
     * This function recursively searches for a node with the specified name from the AVL tree, starting from the
     * given node
     * @param   node to start search from
     * @param   name of the student searching for
     * @return  Node* to the found student
     * */
    Node* search(Node* node, const string& name);

    /**
     * This function performs an inorder traversal of the AVL tree, starting from the given node and appending the node
     * names to the result string
     *
     * @param   node to start traversal from
     * @param   result string of names
     * @return  void
     * */
    void inorder(Node* node, string& result);

    /**
     * This function performs an preorder traversal of the AVL tree, starting from the given node and appending the node
     * names to the result string
     *
     * @param   node to start traversal from
     * @param   result string of names
     * @return  void
     * */
    void preorder(Node* node, string& result);

    /**
     * This function performs an postorder traversal of the AVL tree, starting from the given node and appending the node
     * names to the result string
     *
     * @param   node to start traversal from
     * @param   result string of names
     * @return  void
     * */
    void postorder(Node* node, string& result);

    /**
     * This function calculates the number of levels in the AVL tree, starting from the given node
     *
     * @param   node to start calculation from
     * @return  int count of levels remaining in tree
     * */
    int getLevelCount(Node* node);

    /**
     * This function recursively removes the nth node of the AVL tree using inorder traversal, starting from the given
     * node
     *
     * @param   node to start removal from
     * @param   counter (index) parameter
     * @param   n index of node to remove
     * @return  int
     * */
    Node* removeInorder(Node* node, int& counter, int n);

public:
    AVLTree();
    ~AVLTree();

    // Functions

    /**
     * This function inserts a new node with the given name and ID into the AVL tree
     *
     * @param   name of student to insert
     * @param   id of student to insert
     * @return  void
     * */
    void insert(const string& name, int id);

    /**
     * This function removes a node with the specified ID from the AVL tree
     *
     * @param   id of student to remove
     * @return  void
     * */
    void remove(int id);

    /**
     * This function searches the AVL tree for the specified ID, returning the associated name
     *
     * @param   id of student searching for
     * @return  string name of found student
     * */
    string search(int id);

    /**
     * This function searches the AVL tree for the specified name, returning the associated ID(s)
     *
     * @param   name of student(s) searching for
     * @return  vector<int> of student IDs which match the given name
     * */
    vector<int> search(const string& name);

    /**
     * This function returns string representation of an inorder traversal of the AVL tree
     *
     * @param   void
     * @return  string
     * */
    string printInorder();

    /**
     * This function returns string representation of an preorder traversal of the AVL tree
     *
     * @param   void
     * @return  string
     * */
    string printPreorder();

    /**
     * This function returns string representation of an postorder traversal of the AVL tree
     *
     * @param   void
     * @return  string
     * */
    string printPostorder();

    /**
     * This function returns the number of levels in the AVL tree (tree height)
     *
     * @param   void
     * @return  int number of levels
     * */
    int printLevelCount();

    /**
     * This function removes the nth node of the AVL tree using inorder traversal
     *
     * @param   n index of node to remove
     * @return  void
     * */
    void removeInorder(int n);
};



