#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

struct Node {
    std::string data;
    Node* next;
    Node(std::string data) : data(data), next(nullptr) {}
};