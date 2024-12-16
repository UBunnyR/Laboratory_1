#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include "array.cpp"
#include "Node.cpp"
#include "LinkedList.cpp"
#include "HashTable.cpp"
#include "Queue.cpp"
#include "Stack.cpp"
#include "CompliteBinaryTree.cpp"
#include "DLinkedList.cpp"



class LogicalStream
{

public:
    LogicalStream(const std::string& line = ""){}

    int precedence(std::string op) {
        if (op == "!") return 3;
        if (op == "&") return 2;
        if (op == "|" || op == "^") return 1;
        return 0;
    }

    int applyOp(std::string a, std::string b, std::string op) {
        char oper = op[0];

        int var1 = a[0] - '0';
        int var2 = b[0] - '0';

        switch (oper) {
        case '&': return var1 & var2;
        case '|': return var1 | var2;
        case '^': return var1 ^ var2;
        }
        return 0; // Этот случай не должен произойти
    }

    std::string applyNot(std::string a) {
        if (a == "0") return "1";
        else return "0";
    }

    void work(std::string Line) {
        std::string c = "";
        for (size_t i = 0; i < Line.length(); i++) {
            c = Line[i];

            // Если текущий символ - пробел, пропускаем его
            if (c == " " ) continue;

            // Если текущий символ - открывающая скобка, помещаем его в стек операторов
            if (c == "(") {
                ops.push(c);
            }
            else if (c == "1" || c == "0") {
                values.push(c);
            }
            else if (c == ")") {
                while (!ops.empty() && ops.Top() != "(") {
                    std::string op = ops.Top();
                    ops.pop();

                    if (op == "!") {
                        std::string val = values.Top();
                        values.pop();
                        values.push(applyNot(val));
                    }
                    else {
                        std::string val2 = values.Top();
                        values.pop();
                        std::string val1 = values.Top();
                        values.pop();
                        char ch = applyOp(val1, val2, op) + '0';
                        std::string st;
                        st = ch;
                        values.push(st);
                    }
                }
                // Удаляем открывающую скобку
                if (!ops.empty()) ops.pop();
            }
            else {
                while (!ops.empty() == true && precedence(ops.Top()) >= precedence(c)) {
                    std::string op = ops.Top();
                    ops.pop();

                    if (op == "!") {
                        std::string val = values.Top();
                        values.pop();
                        values.push(applyNot(val));
                    }
                    else {
                        std::string val2 = values.Top();
                        values.pop();
                        std::string val1 = values.Top();
                        values.pop();
                        char ch = applyOp(val1, val2, op) + '0';
                        std::string st;
                        st = ch;
                        values.push(st);
                    }
                }
                // Помещаем текущий оператор в стек операторов
                ops.push(c);
            }
        }
        while (!ops.empty()) {
            std::string op = ops.Top();
            ops.pop();

            if (op == "!") {
                std::string val = values.Top();
                values.pop();
                values.push(applyNot(val));
            }
            else {
                std::string val2 = values.Top();
                values.pop();
                std::string val1 = values.Top();
                values.pop();
                char ch = applyOp(val1, val2, op) + '0';
                std::string st;
                st = ch;
                values.push(st);
            
            }
        }
        std::cout << values.Top();
    }

    void saveToFile(std::string Line, std::string filePath){
        std::fstream file(filePath, std::ios::out);
        file << Line << "\n" << "Answer: " << values.Top();
    }

private:
    Stack values;
    Stack ops;
};



class DataStructureManager {
public:
    void executeCommand(const std::string& command, const std::string& filename) {
        std::istringstream iss(command);
        std::string type, operation, name;
        std::string filePath = "/home/kali/proggraming/Structs/";
        iss >> type >> operation >> name;

        if (type == "M") handleArrayCommand(operation, name, iss, filename, filePath);
        else if (type == "L") handleListCommand(operation, name, iss, filename, filePath);
        else if (type == "Q") handleQueueCommand(operation, name, iss, filename, filePath);
        else if (type == "S") handleStackCommand(operation, name, iss, filename, filePath);
        else if (type == "H") handleHashTableCommand(operation, name, iss, filename, filePath);
        else if (type == "T") handleTreeCommand(operation, name, iss, filename, filePath);
        else if (type == "D") handleTreeCommand(operation, name, iss, filename, filePath);
        else if(type == "EX1") handleEx1(operation, name, iss, filename, filePath);
        else if (type == "DL") handleDoubleListCommand(operation, name, iss, filename, filePath);
        else std::cerr << "Unknown data structure type" << std::endl;
    }

private:
    struct ArrayEntry {
        Array array;
        ArrayEntry* next;
        ArrayEntry(const Array& array) : array(array), next(nullptr) {}
    };
    struct ListEntry {
        LinkedList list;
        ListEntry* next;
        ListEntry(const LinkedList& list) : list(list), next(nullptr) {}
    };
    struct DListEntry {
        DoubleList list;
        DListEntry* next;
        DListEntry(const DoubleList& list) : list(list), next(nullptr) {}
};
    struct QueueEntry {
        Queue queue;
        QueueEntry* next;
        QueueEntry(const Queue& queue) : queue(queue), next(nullptr) {}
    };
    struct StackEntry {
        Stack stack;
        StackEntry* next;
        StackEntry(const Stack& stack) : stack(stack), next(nullptr) {}
    };
    struct HashTableEntry {
        HashTable hashTable;
        HashTableEntry* next;
        HashTableEntry(const HashTable& hashTable) : hashTable(hashTable), next(nullptr) {}
    };
    struct TreeEntry {
        CompleteBinaryTree tree;
        TreeEntry* next;
        TreeEntry(const CompleteBinaryTree& tree) : tree(tree), next(nullptr) {}
    };

    struct Logic {
        LogicalStream lg;
        Logic(const LogicalStream& lg) : lg(lg) {}
    };

    ArrayEntry* arrayHead = nullptr;
    ListEntry* listHead = nullptr;
    DListEntry* dListHead = nullptr;
    QueueEntry* queueHead = nullptr;
    StackEntry* stackHead = nullptr;
    HashTableEntry* hashTableHead = nullptr;
    TreeEntry* treeHead = nullptr;

    void handleArrayCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {

        filePath += "Array/";
        ArrayEntry* entry = findArrayEntry(name);
        if (!entry) {
            entry = new ArrayEntry(Array(name, filePath + filename + "_" + name + ".txt"));
            entry->next = arrayHead;
            arrayHead = entry;
        }

            if (operation == "MPUSH") {
        int index;
        char* value = nullptr;
        std::string temp;
        iss >> index >> temp;
        value = new char[temp.size() + 1];
        strncpy(value, temp.c_str(), temp.size() + 1);
        entry->array.add(index, value);
        entry->array.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "MPUSHEND") {
        char* value = nullptr;
        std::string temp;
        iss >> temp;
        value = new char[temp.size() + 1];
        strncpy(value, temp.c_str(), temp.size() + 1);
        entry->array.addToEnd(value);
        entry->array.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "MDEL") {
        int index;
        iss >> index;
        entry->array.remove(index);
        entry->array.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "MREM") {
        int index;
        char* value = nullptr;
        std::string temp;
        iss >> index >> temp;
        value = new char[temp.size() + 1];
        strncpy(value, temp.c_str(), temp.size() + 1);
        entry->array.replace(index, value);
        entry->array.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "MGET") {
        int index;
        iss >> index;
        std::cout << entry->array.get(index) << std::endl;
    }

    else if (operation == "MPTR") {
        entry->array.print();
    }

    else std::cerr << "Unknown array operation" << std::endl;
}

    void handleListCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "List/";
        ListEntry* entry = findListEntry(name);
        if (!entry) {
            entry = new ListEntry(LinkedList(name, filePath + filename + "_" + name + ".txt"));
            entry->next = listHead;
            listHead = entry;
        }

        if (operation == "LPUSHHEAD") {
            std::string value;
            iss >> value;
            entry->list.addToHead(value);
            entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
        }

        if (operation == "LPUSHTAIL") {
            std::string value;
            iss >> value;
            entry->list.addToTail(value);
            entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
        }

        else if (operation == "LDEL") {
            std::string value;
            iss >> value;
            entry->list.removeByValue(value);
            entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "LDELHEAD") {
            std::string value;
            iss >> value;
            entry->list.removeFromHead();
            entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "LDELTAIL") {
            std::string value;
            iss >> value;
            entry->list.removeFromTail();
            entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
        }

        else if (operation == "LGET") {
            entry->list.print();
        }

        else std::cerr << "Unknown list operation" << std::endl;
    }

    void handleDoubleListCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
    filePath += "List/";
    DListEntry* entry = findDListEntry(name);
    if (!entry) {
        entry = new DListEntry(DoubleList(name, filePath + filename + "_" + name + ".txt"));
        entry->next = dListHead;
        dListHead = entry;
    }

    if (operation == "LPUSHHEAD") {
        std::string value;
        iss >> value;
        entry->list.addToHead(value);
        entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
    }

    if (operation == "LPUSHTAIL") {
        std::string value;
        iss >> value;
        entry->list.addToTail(value);
        entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
    }

    else if (operation == "LDEL") {
        std::string value;
        iss >> value;
        entry->list.removeByValue(value);
        entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "LDELHEAD") {
        std::string value;
        iss >> value;
        entry->list.removeFromHead();
        entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
    }
    else if (operation == "LDELTAIL") {
        std::string value;
        iss >> value;
        entry->list.removeFromTail();
        entry->list.saveToFile(filePath + filename + "_" + name + ".txt");
    }

    else if (operation == "LGET") {
        entry->list.print();
    }
    else std::cerr << "Unknown list operation" << std::endl;
}

    void handleQueueCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "Queue/";
        QueueEntry* entry = findQueueEntry(name);
        if (!entry) {
            entry = new QueueEntry(Queue(name,filePath + filename + "_" + name + ".txt"));
            entry->next = queueHead;
            queueHead = entry;
        }

        if (operation == "QPUSH") {
            std::string value;
            iss >> value;
            entry->queue.push(value);
            entry->queue.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "QPOP") {
            std::cout << entry->queue.pop() << std::endl;
            entry->queue.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "QPTR") {
            entry->queue.print();
        }
        else std::cerr << "Unknown queue operation" << std::endl;
    }

    void handleStackCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "Stack/";
        StackEntry* entry = findStackEntry(name);
        if (!entry) {
            entry = new StackEntry(Stack(name, filePath + filename + "_" + name + ".txt"));
            entry->next = stackHead;
            stackHead = entry;
        }

        if (operation == "SPUSH") {
            std::string value;
            iss >> value;
            entry->stack.push(value);
            entry->stack.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "SPOP") {
            std::cout << entry->stack.pop() << std::endl;
            entry->stack.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "SPTR") {
            entry->stack.print();
        }
        else std::cerr << "Unknown stack operation" << std::endl;
    }

    void handleHashTableCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "Hash/";
        HashTableEntry* entry = findHashTableEntry(name);
        if (!entry) {
            entry = new HashTableEntry(HashTable(10, name, filePath + filename + "_" + name + ".txt"));
            entry->next = hashTableHead;
            hashTableHead = entry;
        }

        if (operation == "HSET") {
            std::string key;
            std::string value;
            iss >> key >> value;
            entry->hashTable.set(key, value);
            entry->hashTable.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "HDEL") {
            std::string key;
            iss >> key;
            entry->hashTable.remove(key);
            entry->hashTable.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "HGET") {
            std::string key;
            iss >> key;
            std::cout << entry->hashTable.get(key) << std::endl;
        }
        else if (operation == "HPTR") {
            entry->hashTable.print();
        }
        else std::cerr << "Unknown hash table operation" << std::endl;
    }

    void handleTreeCommand(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "Tree/";
        TreeEntry* entry = findTreeEntry(name);
        if (!entry) {
            entry = new TreeEntry(CompleteBinaryTree(name, filePath + filename + "_" + name + ".txt"));
            entry->next = treeHead;
            treeHead = entry;
        }

        if (operation == "TINSERT") {
            std::string value;
            iss >> value;
            entry->tree.insert(value);
            entry->tree.saveToFile(filePath + filename + "_" + name + ".txt");
        }
        else if (operation == "TGET") {
            entry->tree.print();
        }
        else if (operation == "TSRC") {
            bool check;
            std::string value;
            iss>>value;
            check = entry->tree.search(value);
            entry->tree.saveToFile(filePath + filename + "_" + name + ".txt");
            std::cout << check;
        }
        else std::cerr << "Unknown tree operation" << std::endl;
    }

    void handleEx1(const std::string& operation, const std::string& name, std::istringstream& iss, const std::string& filename, std::string& filePath) {
        filePath += "Ex1/";
        std::string line = operation + name;
        std::string temp;
        while (iss >> temp)
            line += temp;
        Logic* entry = new Logic(line);
        entry->lg.work(line);
        entry->lg.saveToFile(line, filePath + "output.txt");
    }

    ArrayEntry* findArrayEntry(const std::string& name) {
        ArrayEntry* entry = arrayHead;
        while (entry) {
            if (entry->array.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    DListEntry* findDListEntry(const std::string& name) {
        DListEntry* entry = dListHead;
        while (entry) {
            if (entry->list.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    ListEntry* findListEntry(const std::string& name) {
        ListEntry* entry = listHead;
        while (entry) {
            if (entry->list.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    QueueEntry* findQueueEntry(const std::string& name) {
        QueueEntry* entry = queueHead;
        while (entry) {
            if (entry->queue.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    StackEntry* findStackEntry(const std::string& name) {
        StackEntry* entry = stackHead;
        while (entry) {
            if (entry->stack.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    HashTableEntry* findHashTableEntry(const std::string& name) {
        HashTableEntry* entry = hashTableHead;
        while (entry) {
            if (entry->hashTable.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
    TreeEntry* findTreeEntry(const std::string& name) {
        TreeEntry* entry = treeHead;
        while (entry) {
            if (entry->tree.getName() == name) return entry;
            entry = entry->next;
        }
        return nullptr;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./dbms --file file.data --query 'command'" << std::endl;
    }

    std::string file = argv[2];
    std::string query = argv[4];

    DataStructureManager manager;
    manager.executeCommand(query, file);

    return 0;
}