#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>



class Queue {
public:
    Queue(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    void push(std::string value) {
        Node* newNode = new Node(value);
        if (!head) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    std::string pop() {
        if (!head) return "-1";
        std::string value = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) tail = nullptr;
        return value;
    }
    void print() {
        Node* temp = head;
        while (temp) { std::cout << temp->data << " "; temp = temp->next; }
        std::cout << std::endl;
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        Node* temp = head;
        while (temp) { file << temp->data << std::endl; temp = temp->next; }
        file.close();
    }
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        std::string value;
        while (file >> value) push(value);
        file.close();
    }
    std::string getName() const { return name; }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::string name;
};