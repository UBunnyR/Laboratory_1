#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>


class TreeNode {
public:
    std::string data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(std::string data) : data(data), left(nullptr), right(nullptr) {}
};

class CompleteBinaryTree {
public:
    CompleteBinaryTree(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    bool isComplete() {
        if (!root) return true; 

        int nodeCount = countNodes(root); 
        return isCompleteUtil(root, 0, nodeCount);
    }

    int checkDeep(TreeNode* node) {
        int deep = 0;
        while (node->right)
        {
            deep++;
            node = node->right;
        }
        return deep;
    }

    void insert(std::string value) {
        if (!root) {
            root = new TreeNode(value);
            return;
        }
        int deep = checkDeep(root);
        insertRecursive(root, value, 0, deep);
    }

    bool search(std::string value) { return searchNode(root, value); }
    bool searchNode(TreeNode* node, std::string value) {
        if (!node) return false;
        if (node->data == value) return true;
        return searchNode(node->left, value) || searchNode(node->right, value);
    }
    void print() { printTree(root); }
    void remove(std::string value) {
        if (!root) return;

        TreeNode* nodeToRemove = findNode(root, value);
        if (!nodeToRemove) return; // Узел не найден

        TreeNode* lastNode = findLastNode(root);

        // Заменяем значение узла для удаления значением последнего узла
        nodeToRemove->data = lastNode->data;

        // Удаляем последний узел
        removeLastNode(root, lastNode);
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        int height = getHeight(root);
        int width = static_cast<int>(pow(2, height) * 4);
        std::string* lines = new std::string[height];
        for (int i = 0; i < height; ++i) {
            lines[i].resize(width, ' ');
        }
        saveTree(root, file, lines, 0, 0, width / 4 - 1);
        for (int i = 0; i < height; ++i) {
            file << lines[i] << std::endl;
        }

        delete[] lines;
        file.close();
    }
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        std::string value;
        while (file >> value) insert(value);
        file.close();
    }
    std::string getName() const { return name; }

private:
    TreeNode* root = nullptr;
    std::string name;

   int countNodes(TreeNode* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    bool isCompleteUtil(TreeNode* node, int index, int nodeCount) {
        if (!node) return true;

        
        if (index >= nodeCount) return false;

        
        return isCompleteUtil(node->left, 2 * index + 1, nodeCount) &&
               isCompleteUtil(node->right, 2 * index + 2, nodeCount);
    }

    int insertRecursive(TreeNode* node, std::string value, int tempDeep, int deep) {
        
        int checkInsert = 0;

        if (!node->left) {
            node->left = new TreeNode(value);
            return 1;
        }
        else if (!node->right) {
            node->right = new TreeNode(value);
            return 1;
        }
        else {
            if (node->left && tempDeep < deep && checkInsert != 1) {
                checkInsert = insertRecursive(node->left, value, tempDeep + 1, deep);
            }
            
            if (node->right && tempDeep < deep && checkInsert != 1)
            {
                checkInsert = insertRecursive(node->right, value, tempDeep + 1, deep);
            }
            else
                return checkInsert;
        }
        return checkInsert;
    }

    void printTree(TreeNode* node) {
        if (!node) return;
        std::cout << node->data << " ";
        printTree(node->left);
        printTree(node->right);
    }
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    TreeNode* findNode(TreeNode* node, std::string value) {
        if (!node) return nullptr;
        if (node->data == value) return node;
        TreeNode* foundNode = findNode(node->left, value);
        if (foundNode) return foundNode;
        return findNode(node->right, value);
    }

    TreeNode* findLastNode(TreeNode* node) {
        if (!node) return nullptr;
        if (!node->left && !node->right) return node;
        if (node->right) return findLastNode(node->right);
        return findLastNode(node->left);
    }

    void removeLastNode(TreeNode* node, TreeNode* lastNode) {
        if (!node) return;
        if (node->left == lastNode) {
            delete node->left;
            node->left = nullptr;
            return;
        }
        if (node->right == lastNode) {
            delete node->right;
            node->right = nullptr;
            return;
        }
        removeLastNode(node->left, lastNode);
        removeLastNode(node->right, lastNode);
    }
    int getHeight(TreeNode* node) {
        if (!node) return 0;
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    void saveTree(TreeNode* node, std::ofstream& file, std::string* lines, int level, int left, int right) {
        if (!node) return;
        int mid = (left + right) / 2;
        int pos = mid * 4;
        //std::string value = node->data;
        lines[level].replace(pos, node->data.size(), node->data);
        //lines[level] = value;
        saveTree(node->left, file, lines, level + 1, left, mid - 1);
        saveTree(node->right, file, lines, level + 1, mid + 1, right);
    }
};
