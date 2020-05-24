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
    int key = NULL;
    COLOR color;

    TreeNode(TreeNode *leftAddress, TreeNode *rightAddress, TreeNode *parent, int data, COLOR color) {
        this->leftAddress = leftAddress;
        this->rightAddress = rightAddress;
        this->key = data;
        this->parent = parent;
        this->color = color;
    }
};

class BinarySearchTree {
    TreeNode *root = nullptr;

public:
    void add(int key) {

        if (root == nullptr) {
            root = new TreeNode(nullptr, nullptr, nullptr, key, black);

        } else {
            while (root != nullptr) {

                if (key > root->key) {
                    if (root->rightAddress != nullptr) root = root->rightAddress;
                    else {
                        root->rightAddress = new TreeNode(nullptr, nullptr, root, key, red);
                        root = root->rightAddress;
                        break;
                    }
                } else if (key < root->key) {
                    if (root->leftAddress != nullptr)root = root->leftAddress;

                    else {
                        root->leftAddress = new TreeNode(nullptr, nullptr, root, key, red);
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
        } else {
            tmpNode->parent = node->parent;
            node->parent->rightAddress = tmpNode;
        }
        node->leftAddress = tmpNode->rightAddress;
        tmpNode->rightAddress = node;
        node->parent = tmpNode;
    }

    void rotateLeft(TreeNode *node) {
        TreeNode *tmpNode = node->rightAddress;
        if (node->parent == nullptr) {
            tmpNode->parent = node->parent;
            node->parent = tmpNode;
        }
        else {
            tmpNode->parent = node->parent;
            node->parent->rightAddress = tmpNode;
        }
        node->rightAddress = tmpNode->leftAddress;
        tmpNode->leftAddress = node;
        node->parent = tmpNode;
    }

    bool ancestorsOnDifferentSides(TreeNode *node) {
        return (node->parent->rightAddress == node && node->parent->parent->leftAddress == node->parent) ||
               (node->parent->leftAddress == node && node->parent->parent->rightAddress == node->parent);
    }


    bool findData(int key) {
        TreeNode *currentNode = root;
        while (currentNode != nullptr) {
            if (currentNode->key == key)return true;
            if (key >= currentNode->key)currentNode = currentNode->rightAddress;
            else currentNode = currentNode->leftAddress;
        }
        return false;
    }

    void deleteNode(int key) {
        while (root->key != key) {
            if (key >= root->key)root = root->rightAddress;
            else root = root->leftAddress;
        }

        if (root->leftAddress == nullptr && root->rightAddress == nullptr) {

            root = root->parent;

            if (root->rightAddress->key == key) {
                delete root->rightAddress;
                root->rightAddress = nullptr;  //удаление вершины,у которой нет братьев
            } else {
                delete root->leftAddress;
                root->leftAddress = nullptr;
            }

        }


        if (key == root->key && root->leftAddress != nullptr && root->rightAddress == nullptr) {

            TreeNode *tmpNode = root;
            root = root->leftAddress;
            root->parent = tmpNode->parent;
            if (root->parent != nullptr) {
                if (tmpNode->parent->rightAddress == tmpNode)root->parent->rightAddress = root;
                else root->parent->leftAddress = root;
            }

        }

        if (key == root->key && root->leftAddress == nullptr && root->rightAddress != nullptr) {

            TreeNode *tmpNode = root;
            root = root->rightAddress;
            root->parent = tmpNode->parent;
            if (root->parent != nullptr) {
                if (tmpNode->parent->rightAddress == tmpNode)root->parent->rightAddress = root;
                else root->parent->leftAddress = root;
            }

        }

        if (key == root->key && root->leftAddress != nullptr && root->rightAddress != nullptr) {
            root = root->rightAddress;

            while (root->leftAddress != nullptr) {
                root = root->leftAddress;
            }

            int tmpData = root->key;
            if (root->rightAddress != nullptr) {
                root = root->parent;
                TreeNode *tmpNode = root->leftAddress->rightAddress;
                delete (root->leftAddress);
                root->leftAddress = tmpNode;        // удаление если у удаляемого элемента два узла
                root->leftAddress->parent = root;
            } else {
                root = root->parent;
                delete (root->leftAddress);
            }
            while (root->key != key) {
                root = root->parent;
            }
            root->key = tmpData;
        }

        while (root->parent != nullptr) {
            root = root->parent;
        }
    }

};

int main() {
    BinarySearchTree myTree{};
    for(int i=1;i<=10000; i++)myTree.add(i);


    return 0;
}



