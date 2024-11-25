#pragma once
#include <string>
#include <iostream>

// Se crea una clase Nodo
class Node {
    public:
    // Lectura de archivo
    std::string ip; 
    int key; // Numero de ips destino
    Node* left; //Nodo hijo izquierdo
    Node* right; //nodo hijo derecho

    Node(std::string, int); //Constructor
    Node(); //Constructor por default
};

// Constructor
Node::Node(std::string _ip, int _key) { 
    ip = _ip; // Stores ip address
    key = _key;
    left = nullptr; 
    right = nullptr;
}

// Constructor por default
Node::Node() {
    ip = "0.0.0.0";
    key = 0;
    left = nullptr;
    right = nullptr;
}