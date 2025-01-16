/**
* COP3503 - Project 1 - Gator AVL Tree
* @author Preston Hemmy
* @version 1.0
*/

#include "tree.h"
#include <functional>

AVLTree::Node::Node(const string& name, int id) : name(name), id(id), left(nullptr), right(nullptr), height(1) {}

// Private Functions

int AVLTree::height(AVLTree::Node* node) {
    if (node == nullptr)
        return 0;

    return node->height;
}

int AVLTree::balanceFactor(AVLTree::Node* node) {
    if (node == nullptr)
        return 0;

    return height(node->left) - height(node->right);
}

AVLTree::Node* AVLTree::rotateLeft(AVLTree::Node* node) {
    // Initialization
    Node* right_child = node->right;
    Node* right_left_child = right_child->left;

    // Rotation
    right_child->left = node;
    node->right = right_left_child;

    // Update heights
    node->height = 1 + max(height(node->left), height(node->right));
    right_child->height = 1 + max(height(right_child->left), height(right_child->right));

    // Update root
    if (node == root)
        root = right_child;

    return right_child;
}

AVLTree::Node* AVLTree::rotateRight(AVLTree::Node* node) {
    // Initialization
    Node* left_child = node->left;
    Node* left_right_child = left_child->right;

    // Rotation
    left_child->right = node;
    node->left = left_right_child;


    // Update heights
    node->height = 1 + max(height(node->left), height(node->right));
    left_child->height = 1 + max(height(left_child->left), height(left_child->right));

    // Update root
    if (node == root)
        root = left_child;

    return left_child;
}

AVLTree::Node* AVLTree::rotateLeftRight(AVLTree::Node* node) {
    // Initialization
    Node* left_child = node->left;
    Node* left_right_child = left_child->right;
    Node* left_right_left_child = left_right_child->left;

    // (Left) Rotation
    node->left = left_right_child;
    node->left->left = left_child;
    node->left->left->right = left_right_left_child;

    // Update heights
    node->height = 1 + max(height(node->left), height(node->right));
    left_child->height = 1 + max(height(left_child->left), height(left_child->right));
    left_right_child->height = 1 + max(height(left_right_child->left), height(left_right_child->right));

    // Right rotation
    return rotateRight(node);
}

AVLTree::Node* AVLTree::rotateRightLeft(AVLTree::Node* node) {
    // Initialization
    Node* right_child = node->right;
    Node* right_left_child = right_child->left;
    Node* right_left_right_child = right_left_child->right;

    // (Right) Rotation
    node->right = right_left_child;
//    right_left_child->right = right_child;
    node->right->right = right_child;
    node->right->right->left = right_left_right_child;

    // Update heights
    node->height = 1 + max(height(node->left), height(node->right));
    right_child->height = 1 + max(height(right_child->left), height(right_child->right));
    right_left_child->height = 1 + max(height(right_left_child->left), height(right_left_child->right));

    // Left rotation
    return rotateLeft(node);
}

AVLTree::Node* AVLTree::insert(AVLTree::Node* node, const string& name, int id) {
    if (node == nullptr)
        return new Node(name, id);

    // Recursively traverse tree
    if (id < node->id)
        node->left = insert(node->left, name, id);
    else if (id > node->id)
        node->right = insert(node->right, name, id);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Left-heavy branch
    if (balance > 1) {
        if (id < node->left->id) {
            return rotateRight(node);
        } else {
            return rotateLeftRight(node);
        }
    }

    // Right-heavy branch
    if (balance < -1) {
        if (id > node->right->id) {
            return rotateLeft(node);
        } else {
            return rotateRightLeft(node);
        }
    }

    return node;
}

AVLTree::Node* AVLTree::remove(AVLTree::Node* node, int id) {
    if (node == nullptr)
        return nullptr;

    // Recursively traverse tree
    if (id < node->id)
        node->left = remove(node->left, id);
    else if (id > node->id)
        node->right = remove(node->right, id);
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node* successor = node->right;
            while (successor->left != nullptr)
                successor = successor->left;

            node->id = successor->id;
            node->name = successor->name;
            node->right = remove(node->right, successor->id);
        }
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Left-heavy branch
    if (balance > 1) {
        if (balanceFactor(node->left) >= 0)
            return rotateRight(node);
        else
            return rotateLeftRight(node);
    }

    // Right-heavy branch
    if (balance < -1) {
        if (balanceFactor(node->right) <= 0)
            return rotateLeft(node);
        else
            return rotateRightLeft(node);
    }

    return node;
}

AVLTree::Node* AVLTree::search(AVLTree::Node* node, int id) {
    if (node == nullptr)
        return nullptr;

    if (id < node->id)
        return search(node->left, id);
    else if (id > node->id)
        return search(node->right, id);

    return node;
}

AVLTree::Node* AVLTree::search(AVLTree::Node* node, const string& name) {
    if (node == nullptr)
        return nullptr;

    if (name == node->name)
        return node;

    Node* left_child = search(node->left, name);
    if (left_child != nullptr)
        return left_child;

    return search(node->right, name);
}

void AVLTree::inorder(AVLTree::Node* node, string& result) {
    if (node == nullptr)
        return;

    inorder(node->left, result);
    result += node->name + ", ";
    inorder(node->right, result);
}

void AVLTree::preorder(AVLTree::Node* node, string& result) {
    if (node == nullptr)
        return;

    result += node->name + ", ";
    preorder(node->left, result);
    preorder(node->right, result);
}

void AVLTree::postorder(AVLTree::Node* node, string& result) {
    if (node == nullptr)
        return;

    postorder(node->left, result);
    postorder(node->right, result);
    result += node->name + ", ";
}

int AVLTree::getLevelCount(AVLTree::Node* node) {
    if (node == nullptr)
        return 0;

    return 1 + max(getLevelCount(node->left), getLevelCount(node->right));
}

AVLTree::Node* AVLTree::removeInorder(AVLTree::Node* node, int& counter, int n) {
    if (node == nullptr)
        return nullptr;

    node->left = removeInorder(node->left, counter, n);

    if (counter == n) {
        Node* temp = remove(node, node->id);
        counter++;
        return temp;
    }

    counter++;
    node->right = removeInorder(node->right, counter, n);

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Left-heavy branch
    if (balance > 1) {
        if (balanceFactor(node->left) >= 0)
            return rotateRight(node);
        else
            return rotateLeftRight(node);
    }

    // Right-heavy branch
    if (balance < -1) {
        if (balanceFactor(node->right) <= 0)
            return rotateLeft(node);
        else
            return rotateRightLeft(node);
    }

    return node;
}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    // Recursive lambda expression which deletes all nodes
    function<void(Node*)> deleteNodes = [&](Node* node) {
        if (node == nullptr)
            return;

        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    };

    deleteNodes(root);
}

// Public Functions

void AVLTree::insert(const string& name, int id) {
    root = insert(root, name, id);
}

void AVLTree::remove(int id) {
    root = remove(root, id);
}

string AVLTree::search(int id) {
    Node* result = search(root, id);

    if (result == nullptr)
        return "";

    return result->name;
}

vector<int> AVLTree::search(const string& name) {
    vector<int> ids;

    // Recursive lambda function which searches for a name match
    function<void(Node*)> searchName = [&](Node* node) {
        if (node == nullptr)
            return;

        if (node->name == name)
            ids.push_back(node->id);

        searchName(node->left);
        searchName(node->right);
    };

    searchName(root);
    return ids;
}

string AVLTree::printInorder() {
    string result;

    inorder(root, result);

    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }

    return result;
}

string AVLTree::printPreorder() {
    string result;

    preorder(root, result);

    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }

    return result;
}

string AVLTree::printPostorder() {
    string result;

    postorder(root, result);

    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }

    return result;
}

int AVLTree::printLevelCount() {
    return getLevelCount(root);
}

void AVLTree::removeInorder(int n) {
    int counter = 0;
    root = removeInorder(root, counter, n);
}