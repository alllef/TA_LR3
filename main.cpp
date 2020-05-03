#include <iostream>

using namespace std;

struct TreeNode {
public:
    TreeNode *leftAddress = nullptr;
    TreeNode *rightAddress = nullptr;
    TreeNode *parent = nullptr;
    int data = NULL;

    TreeNode(TreeNode *leftAddress, TreeNode *rightAddress, TreeNode *parent, int data) {
        this->leftAddress = leftAddress;
        this->rightAddress = rightAddress;
        this->data = data;
        this->parent = parent;
    }
};

class BinarySearchTree {
    TreeNode *root;

public:
    void add(int data) {

        while (root != nullptr) {
            if (data > root->data)root = root->rightAddress;
            else root = root->leftAddress;
        }

        root = new TreeNode(nullptr, nullptr, root, data);
        while (root->parent != nullptr){
            root = root->parent;
        }
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
    return 0;
}



