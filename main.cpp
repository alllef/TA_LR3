#include <iostream>

using namespace std;

enum COLOR {
    red, black
};

struct TreeNode {
public:
    TreeNode *leftAddress = nullptr;
    TreeNode *rightAddress = nullptr;
    TreeNode *parent = nullptr;
    int data = NULL;
    COLOR color;

    TreeNode(TreeNode *leftAddress, TreeNode *rightAddress, TreeNode *parent, int data, COLOR color) {
        this->leftAddress = leftAddress;
        this->rightAddress = rightAddress;
        this->data = data;
        this->parent = parent;
        this->color = color;
    }
};

class BinarySearchTree {
    TreeNode *root = nullptr;

public:
    void add(int data) {
        if (root == nullptr) root = new TreeNode(nullptr, nullptr, nullptr, data, black);
        else {
            while (root != nullptr) {

                if (data > root->data) {
                    if (root->rightAddress != nullptr) root = root->rightAddress;
                    else {
                        root->rightAddress = new TreeNode(nullptr, nullptr, root, data, red);
                        root = root->rightAddress;
                        break;
                    }
                } else if (data < root->data) {
                    if (root->leftAddress != nullptr)root = root->leftAddress;

                    else {
                        root->leftAddress = new TreeNode(nullptr, nullptr, root, data, red);
                        root = root->leftAddress;
                        break;
                    }
                }
            }
        }
        while (root->parent != nullptr) {
            if (root->parent->color == red) {
                if (uncle(root) != nullptr) {
                    if (uncle(root)->color == red) {
                        root->parent->parent->color = red;
                        root->parent->color = black;
                        uncle(root)->color = black;
                    }
                } else {
                    if (ancestorsOnDifferentSides(root)) {

                        if (root->parent->leftAddress == root) {
                            rotateRight(root->parent);
                            COLOR tmpColor = root->color;
                            root->color = root->parent->color;
                            root->parent->color = tmpColor;
                            rotateLeft(root->parent);
                        }
                            //else if(root->parent->rightAddress==root){
                        else {
                            rotateLeft(root->parent);
                            COLOR tmpColor = root->color;
                            root->color = root->parent->color;
                            root->parent->color = tmpColor;
                            rotateRight(root->parent);
                        }
                    } else {
                        if (root->parent->leftAddress == root) {
                            COLOR tmpColor = root->parent->color;
                            root->parent->color = root->parent->parent->color;
                            root->parent->parent->color = tmpColor;
                            rotateRight(root->parent->parent);
                        } else {
                            COLOR tmpColor = root->parent->color;
                            root->parent->color = root->parent->parent->color;
                            root->parent->parent->color = tmpColor;
                            rotateLeft(root->parent->parent);
                        }
                    }
                }
            } else root = root->parent;
        }
        if (root->color == red)root->color = black;
    }


    TreeNode *uncle(TreeNode *node) {
        if (node->parent->parent->leftAddress == nullptr || node->parent->parent->rightAddress == nullptr)
            return nullptr;
        else if (node->parent->parent->leftAddress != node->parent)return node->parent->parent->leftAddress;
        else return node->parent->parent->rightAddress;
    }

    void rotateRight(TreeNode *node) {
        TreeNode *tmpNode = node->leftAddress;
        node->leftAddress = tmpNode->rightAddress;
        tmpNode->rightAddress = node;
        root = tmpNode;
    }

    void rotateLeft(TreeNode *node) {
        TreeNode *tmpNode = node->rightAddress;
        node->rightAddress = tmpNode->leftAddress;
        tmpNode->leftAddress = node;
        root = tmpNode;
    }

    bool ancestorsOnDifferentSides(TreeNode *node) {
        return (node->parent->rightAddress == node && node->parent->parent->leftAddress == node->parent) ||
               (node->parent->leftAddress == node && node->parent->parent->rightAddress == node->parent);
    }


    bool findData(int data) {
        TreeNode *currentNode = root;
        while (currentNode != nullptr) {
            if (currentNode->data == data)return true;
            if (data >= currentNode->data)currentNode = currentNode->rightAddress;
            else currentNode = currentNode->leftAddress;
        }
        return false;
    }

    void deleteNode(int data, TreeNode *cnode) {
        if (data == cnode->data && cnode->leftAddress == nullptr && cnode->rightAddress == nullptr) delete (cnode);

        if (data == cnode->data && cnode->leftAddress != nullptr && cnode->rightAddress == nullptr) {
            cnode->data = cnode->leftAddress->data;
            TreeNode *tmpNode = cnode->leftAddress;
            delete (cnode->leftAddress);
            cnode->leftAddress = tmpNode;
        }

        if (data == cnode->data && cnode->leftAddress == nullptr && cnode->rightAddress != nullptr) {
            cnode->data = cnode->rightAddress->data;
            TreeNode *tmpNode = cnode->rightAddress;
            delete (cnode->rightAddress);
            cnode->rightAddress = tmpNode;
        }

        if (data == cnode->data && cnode->leftAddress == nullptr && cnode->rightAddress != nullptr) {
            TreeNode *tmpNode = cnode->rightAddress;
            while (tmpNode->leftAddress != nullptr) {
                tmpNode = tmpNode->leftAddress;
            }
            cnode->data = tmpNode->data;

        }
    }

};

int main() {
    BinarySearchTree myTree{};
    myTree.add(1);
    myTree.add(2);
    myTree.add(3);
    myTree.add(4);
    myTree.add(5);

    return 0;
}



