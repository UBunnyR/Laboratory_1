#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>



class HashTable {
public:
    HashTable(int size = 191, const std::string& name = "", const std::string& filename = "") : size(size), name(name) {
        table = new Node * [size]();
        if (!filename.empty()) loadFromFile(filename);
    }

    void set(const std::string& key, std::string value) {
        int index = hash(key);
        Node* entry = table[index];
        while (entry) {
            if (entry->key == key) { entry->value = value; return; }
            entry = entry->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }
    std::string get(const std::string& key) {
        int index = hash(key);
        Node* entry = table[index];
        while (entry) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return "-1";
    }
    void remove(const std::string& key) {
        int index = hash(key);
        Node* entry = table[index];
        Node* prev = nullptr;
        while (entry) {
            if (entry->key == key) {
                if (prev) prev->next = entry->next;
                else table[index] = entry->next;
                delete entry;
                return;
            }
            prev = entry;
            entry = entry->next;
        }
    }
    void print() {
        for (int i = 0; i < size; ++i) {
            Node* entry = table[i];
            while (entry) { std::cout << entry->key << ": " << entry->value << std::endl; entry = entry->next; }
        }
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        for (int i = 0; i < size; ++i) {
            Node* entry = table[i];
            while (entry) { file << entry->key << " " << entry->value << std::endl; entry = entry->next; }
        }
        file.close();
    }
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        std::string key;
        std::string value;
        while (file >> key >> value) set(key, value);
        file.close();
    }
    std::string getName() const { return name; }

private:
    struct Node {
        std::string key;
        std::string value;
        Node* next;
        Node(const std::string& key, std::string value) : key(key), value(value), next(nullptr) {}
    };

    Node** table;
    int size;
    std::string name;

    int hash(const std::string& key) {
        int hash = 0;
        for (char c : key) hash = (hash * 31 + c) % size;
        return hash;
    }
};