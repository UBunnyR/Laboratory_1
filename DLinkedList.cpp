#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

struct DNode {
    std::string data;
    DNode* next;
    DNode* back;
    DNode(std::string data) : data(data), next(nullptr), back(nullptr) {}
};
class DoubleList {
public:
    DoubleList(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    void addToHead(std::string value) {
        DNode* newNode = new DNode(value);
        if (head == nullptr)
            head = tail = newNode;
        else {
            head->back = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    void addToTail(std::string value) {
        DNode* newNode = new DNode(value);
        if (tail == nullptr)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->back = tail;
            tail = newNode;
        }
    }
    void removeFromHead() {
        if (!head) return;
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
    void removeFromTail() {
        if (!tail) return;
        DNode* temp = tail;
        tail = tail->back;
        delete temp;
    }
    void removeByValue(std::string value) {
        if (!head) return;
        if (head->data == value) {
            DNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        DNode* temp = head;
        while (temp->next && temp->next->data != value) temp = temp->next;
        if (temp->next) {
            DNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }
    bool search(std::string value) {
        DNode* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }
    void print() {
        DNode* temp = head;
        while (temp) { std::cout << temp->data << " "; temp = temp->next; }
        std::cout << std::endl;
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        DNode* temp = head;
        while (temp) { file << temp->data << std::endl; temp = temp->next; }
        file.close();
    }
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        head = tail;
        tail = head;
        if (!file.is_open()) return;
        std::string value;
        while (file >> value) addToTail(value);
        file.close();
    }
    std::string getName() const { return name; }

private:
    DNode* head = nullptr;
    DNode* tail = nullptr;
    std::string name;
};
