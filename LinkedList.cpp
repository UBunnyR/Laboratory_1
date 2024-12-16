#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

class LinkedList {
public:
    LinkedList(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    void addToHead(std::string value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void addToTail(std::string value) {
        Node* newNode = new Node(value);
        if (!head) { head = newNode; return; }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    void removeFromHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    void removeFromTail() {
        if (!head) return;
        if (!head->next) { delete head; head = nullptr; return; }
        Node* temp = head;
        while (temp->next->next) temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }
    void removeByValue(std::string value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != value) temp = temp->next;
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }
    bool search(std::string value) {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
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
        while (file >> value) addToTail(value);
        file.close();
    }
    std::string getName() const { return name; }

private:
    Node* head = nullptr;
    std::string name;
};
