#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    string key;
    string value;
    Node(string key, string value) {
        this->key = key;
        this->value = value;
    }
};

class HashTable {
private:
    static const int hashGroups = 20;
    vector<Node*> table[hashGroups];
    int size = 0;

    int HashFunction(string key) {
        int sum = 0, i = 0;

        while (key[i] != '\0') {
            sum += key[i];
            i++;
        }

        return sum % hashGroups;
    }

    bool IsEmpty() const {
        int sum{};
        for (int i{}; i < hashGroups; i++) {
            sum += table[i].size();
        }

        if (!sum) {
            return true;
        }
        return false;
    }

public:
    void InsertNode(string key, string value) {
        size++;
        int hashValue = HashFunction(key);
        table[hashValue].push_back(new Node(key, value));
        if (table[hashValue].size() > 1) {
            cout << "A collision occurred at index " << hashValue << ".\n";
        }
        return;
    }



    void RemoveNode(string key) {
        int hashValue = HashFunction(key);
        bool keyExists = false;
        for (auto it = table[hashValue].begin(); it != table[hashValue].end(); it++) {
            if ((*it)->key == key) {
                keyExists = true;
                it = table[hashValue].erase(it);
                cout << "Pair removed.\n";
                size--;
                break;
            }
        }

        if (!keyExists) {
            cout << "Key not found. Pair not removed.\n";
        }
        return;
    }

    string SearchTable(string key) {
        int hashValue = HashFunction(key);
        bool keyExists = false;
        for (auto& node : table[hashValue]) {
            if (node->key == key) {
                keyExists = true;
                return node->value;
            }
        }

        if (!keyExists) {
            return "Key not found.\n";
        }
    }

    void PrintTable() {
        size = 0;
        for (int i = 0; i < hashGroups; i++) {
            if (table[i].size() == 0) continue;

            for (auto itr = table[i].begin(); itr != table[i].end(); itr++) {
                size++;
                cout << "Index: " << i << "; Key: " << (*itr)->key << "; Value: " << (*itr)->value << "\n";
            }
        }
        return;
    }

    int GetSize()
    {
        return size;
    }
};