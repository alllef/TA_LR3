#include <iostream>

using namespace std;

struct TreeNode {
public:
    TreeNode *leftAddress = nullptr;
    TreeNode *rightAddress = nullptr;
    TreeNode *parent = nullptr;
    int data = NULL;
    string color = "";

    TreeNode(TreeNode *leftAddress, TreeNode *rightAddress, TreeNode *parent, int data, string color) {
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
        if (root == nullptr) root = new TreeNode(nullptr, nullptr, nullptr, data, "black");
        else {
            while (root != nullptr) {

                if (data > root->data) {
                    if (root->rightAddress != nullptr) root = root->rightAddress;
                    else {
                        root->rightAddress = new TreeNode(nullptr, nullptr, root, data, "red");

                        break;
                    }
                } else if (data < root->data) {
                    if (root->leftAddress != nullptr)root = root->leftAddress;

                    else {
                        root->leftAddress = new TreeNode(nullptr, nullptr, root, data, "red");

                        break;
                    }
                }
            }
        }
        while (root->parent != nullptr) {
            if (root->parent->color == "red") {
                if (uncle(root)->color == "red") {
                    root->parent->parent->color = "red";
                    root->parent->color = "black";
                    uncle(root)->color="black";
                }
                else if(uncle(root)->color=="black")
            }
        }
    }

    TreeNode *uncle(TreeNode *node) {
        if (node->parent->parent->leftAddress != node->parent)
            return node->parent->parent->leftAddress;
        else return node->parent->parent->rightAddress;
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
    myTree.add(30);
    myTree.add(27);
    myTree.add(56);
    myTree.add(87);
    myTree.add(46);
    myTree.add(99);
    myTree.add(15);
    return 0;
}



