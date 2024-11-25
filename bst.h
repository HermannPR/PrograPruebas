#pragma once
#include "nodo.h"
#include <vector>
#include <iostream>

class ArbolBST {
public:
    Node* root = nullptr;

    Node* addLeaf(Node* adding, int key, std::string ip);
    void deleteTree(Node* root);
    void displayKeyIP(Node* disp);
    void recorrido(Node* root, int& counter, int& lim);
    void recorrer5grandes(Node* root);
    void bootMaster(Node* root);
    void recopilarNodos(Node* root, std::vector<std::pair<int, std::string>>& nodos);
    bool esDuplicado(Node* root, std::string ip);
};

Node* ArbolBST::addLeaf(Node* adding, int key, std::string ip) {
    if (root == nullptr) {
        root = new Node(ip, key);
        return root;
    }
    if (ip < adding->ip) {
        if (adding->left == nullptr) {
            adding->left = new Node(ip, key);
        } else {
            addLeaf(adding->left, key, ip);
        }
    } else if (ip > adding->ip) {
        if (adding->right == nullptr) {
            adding->right = new Node(ip, key);
        } else {
            addLeaf(adding->right, key, ip);
        }
    } else {
        adding->key += key;
    }
    return adding;
}

void ArbolBST::deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    if (this->root == root) this->root = nullptr;
}

void ArbolBST::displayKeyIP(Node* disp) {
    std::cout << "IP: " << disp->ip << " con " << disp->key << " accesos\n";
}

void ArbolBST::recorrido(Node* root, int& counter, int& lim) {
    if (root == nullptr || counter >= lim) return;

    recorrido(root->right, counter, lim);
    if (counter < lim) {
        displayKeyIP(root);
        counter++;
    }
    recorrido(root->left, counter, lim);
}

void ArbolBST::recorrer5grandes(Node* root) {
    int contador = 0;
    int lim = 5;
    recorrido(root, contador, lim);
}

void ArbolBST::bootMaster(Node* root) {
    int contador = 0;
    int lim = 1;
    recorrido(root, contador, lim);
}

void ArbolBST::recopilarNodos(Node* root, std::vector<std::pair<int, std::string>>& nodos) {
    if (root == nullptr) return;
    nodos.push_back({root->key, root->ip});
    recopilarNodos(root->left, nodos);
    recopilarNodos(root->right, nodos);
}

bool ArbolBST::esDuplicado(Node* root, std::string ip) {
    if (root == nullptr) return false;

    if (root->ip == ip) {
        return true;
    }

    if (ip < root->ip) {
        return esDuplicado(root->left, ip);
    } else {
        return esDuplicado(root->right, ip);
    }
}
