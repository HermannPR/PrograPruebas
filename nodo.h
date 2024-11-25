#pragma once
#include <string>

class Node {
public:
    std::string ip; // Dirección IP
    int key;        // Número de accesos asociados a esta IP
    Node* left;     // Nodo hijo izquierdo
    Node* right;    // Nodo hijo derecho

    Node(std::string, int); // Constructor parametrizado
    Node();                 // Constructor por defecto
};

Node::Node(std::string _ip, int _key) { 
    ip = _ip; 
    key = _key;
    left = nullptr;
    right = nullptr;
}

Node::Node() {
    ip = "0.0.0.0";
    key = 0;
    left = nullptr;
    right = nullptr;
}
