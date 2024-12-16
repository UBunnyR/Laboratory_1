#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>

class Array {
public:
    Array(const std::string& name = "", const std::string& filename = "") : name(name) {
        if (!filename.empty()) loadFromFile(filename);
    }

    void add(int index, char* value) {
        if (index < 0 || index > length) return;
        if (length == size) resize();
        for (int i = length; i > index; --i) data[i] = data[i - 1];
        data[index] = value;
        ++length;
    }
    void addToEnd(char* value) {
        if (length == 0)
            data[0] = value;
        if (length == size) resize();
        data[length++] = value;
    }
    std::string get(int index) {
        if (index < 0 || index >= length) return "-1";
        return data[index];
    }
    void remove(int index) {
        if (index < 0 || index >= length) return;
        for (int i = index; i < length - 1; ++i) data[i] = data[i + 1];
        --length;
    }
    void replace(int index, char* value) {
        if (index < 0 || index >= length) return;
        data[index] = value;
    }
    int getLength() { return length; }
    void print() {
        for (int i = 0; i < length; ++i) std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    void createFile(const std::string& filename)
    {
        std::fstream file(filename, std::ios::out);
        file.close();
    }
    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        file << length << std::endl;
        for (int i = 0; i < length; ++i) file << data[i] << std::endl;
        if (length == 0)
            file << 1 << "\n" << data[0];
        file.close();
    }
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) { createFile(filename); std::ifstream file(filename); }
        file >> length;
        size = length;
        data = new char* [size];
        if (size == 0)
            data = new char* [1];
        //data[0] = 0;
        for (int i = 0; i < length; ++i) {
            std::string temp;
            file >> temp;
            data[i] = new char[temp.size() + 1];
            strncpy(data[i], temp.c_str(), temp.size() + 1);
        }
        file.close();
    }
    std::string getName() const { return name; }

private:
    char** data;
    int size = 10;
    int length = 0;
    std::string name;

    void resize() {
        int newSize = size * 2;
        char** newData = new char* [newSize];
        for (int i = 0; i < length; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        size = newSize;
    }
};
