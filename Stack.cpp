#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>


class Stack {
public:
    Stack(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    std::string Top()
    {
        return top->data;
    }

    bool empty() {
        if (top) return false;
        else return true;
    }

    void push(std::string value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }
    std::string pop() {
        if (!top) return "-1";
        std::string value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    void print() {
        Node* temp = top;
        while (temp) { std::cout << temp->data << " "; temp = temp->next; }
        std::cout << std::endl;
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        Node* temp = top;
        while (temp) { file << temp->data << std::endl; temp = temp->next; }
        file.close();
    }
    int count(const std::string& filename)
    {
        std::ifstream file(filename);
        std::string value;
        int index = 0;
        while (file >> value)
        {
            index++;
        }
        file.close();
        return index;
    }
    void loadFromFile(const std::string& filename) {

        std::string value;
        int index = count(filename);
        while (index != 0)
        {
            std::ifstream file(filename);
            int tempIndex = 0;
            while (file >> value)
            {
                tempIndex++;
                if (index == tempIndex)
                    push(value);
            }
            file.close();
            index--;
        }

    }
    std::string getName() const { return name; }

private:
    Node* top = nullptr;
    std::string name;
};
