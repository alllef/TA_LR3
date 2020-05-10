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
        if (root == nullptr) {
            root = new TreeNode(nullptr, nullptr, nullptr, data, black);

        } else {
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

            if (root->parent->color == red && root->color == red) {
                if (uncle(root) == nullptr || uncle(root)->color == black) {
                    if (ancestorsOnDifferentSides(root)) {

                        if (root->parent->leftAddress == root) {
                            rotateRight(root->parent);
                            swapColor(root, root->parent);
                            rotateLeft(root->parent);
                        } else {
                            rotateLeft(root->parent);
                            swapColor(root, root->parent);
                            rotateRight(root->parent);
                        }
                    } else {
                        if (root->parent->leftAddress == root) {
                            swapColor(root->parent->parent, root->parent);
                            rotateRight(root->parent->parent);
                        } else {
                            swapColor(root->parent->parent, root->parent);
                            rotateLeft(root->parent->parent);
                        }
                    }
                } else {
                    root->parent->parent->color = red;
                    root->parent->color = black;
                    uncle(root)->color = black;
                }
            } else {
                if (root->parent->parent == nullptr && root->parent->color == red) {
                    root->parent->color = black;
                }
                root = root->parent;
            }
        }

    }


    TreeNode *uncle(TreeNode *node) {
        if (node->parent->parent->leftAddress == nullptr || node->parent->parent->rightAddress == nullptr)
            return nullptr;
        else if (node->parent->parent->leftAddress != node->parent)return node->parent->parent->leftAddress;
        else return node->parent->parent->rightAddress;
    }

    void swapColor(TreeNode *node, TreeNode *otherNode) {
        COLOR tmpColor = node->color;
        node->color = otherNode->color;
        otherNode->color = tmpColor;
    }

    void rotateRight(TreeNode *node) {
        TreeNode *tmpNode = node->leftAddress;
        if (node->parent == nullptr) {
            tmpNode->parent = node->parent;
            node->parent = tmpNode;
        }
        else node->parent->rightAddress=tmpNode;
        node->leftAddress = tmpNode->rightAddress;
        tmpNode->rightAddress = node;
    }

    void rotateLeft(TreeNode *node) {
        TreeNode *tmpNode = node->rightAddress;
        if (node->parent == nullptr) {
            tmpNode->parent = node->parent;
            node->parent = tmpNode;
        }
        else node->parent->rightAddress=tmpNode;
        node->rightAddress = tmpNode->leftAddress;
        tmpNode->leftAddress = node;
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

    void deleteNode(int data) {
        while(root->data!=data){

        }
        if (data == root->data && root->leftAddress == nullptr && root->rightAddress == nullptr) delete (root);

        if (data == root->data && root->leftAddress != nullptr && root->rightAddress == nullptr) {
            root->data = root->leftAddress->data;
            TreeNode *tmpNode = root->leftAddress;
            delete (root->leftAddress);
            root->leftAddress = tmpNode;
        }

        if (data == root->data && root->leftAddress == nullptr && root->rightAddress != nullptr) {
            root->data = root->rightAddress->data;
            TreeNode *tmpNode = root->rightAddress;
            delete (root->rightAddress);
            root->rightAddress = tmpNode;
        }

        if (data == root->data && root->leftAddress == nullptr && root->rightAddress != nullptr) {
            TreeNode *tmpNode = root->rightAddress;
            while (tmpNode->leftAddress != nullptr) {
                tmpNode = tmpNode->leftAddress;
            }
            root->data = tmpNode->data;

        }
    }

};

int main() {
    BinarySearchTree myTree{};
    myTree.add(7);
    myTree.add(3);
    myTree.add(18);
    myTree.add(10);
    myTree.add(22);
    myTree.add(8);
    myTree.add(11);
    myTree.add(26);
    return 0;
}



