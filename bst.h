#include "nodo.h"

class ArbolBST {
    public:
        Node* root = nullptr; 

        // Método principal agregar datos
        Node* addLeaf(Node* adding, int key, std::string ip); // Agregar hoja al arbol
        void deleteTree(Node* root); // Borrar el arbol
        void displayKeyIP(Node* disp); // Display the times accessed and IP address 
        void recorrido(Node* root, int& counter, int& lim); // Recorrer los 5 más grandes
        void recorrer5grandes(Node* root); // Obtener las 5 IPs más repetidas
        void bootMaster(Node* root); //Display boot master
};

/* 
Propósito: Agregar una hoja al arbol BST
Precondición: raiz, valor de la llave o el numero de repeticiones de la línea de información, y la liena de infromación
Postcondición: la hoja agregada en el arbol BST
Complejidad: O(n)
*/
Node* ArbolBST::addLeaf(Node* adding, int key, std::string ip) { 
    // Sets as root if empty
    if (root == nullptr) {
        root = new Node(ip, key);
        return root;
    }
    // Checks if key should go on the left side 
    else if (key < adding->key) {
        // If left is empty, add to left
        if (adding->left == nullptr) {
            adding->left = new Node(ip, key);
        } 
        // Else not a leaf, keep going down 
        else {
            adding->left = addLeaf(adding->left, key, ip);
        }
    }
    else if (key > adding->key) {
        // If right is empty, add to right
        if (adding->right == nullptr) {
            adding->right = new Node(ip, key);
        } 
        // Else not a leaf, keep going down
        else {
            adding->right = addLeaf(adding->right, key, ip);
        }
    }
    // Handle case where key is equal to adding->key
    else {
        // Key already exists, do not insert the data
        return adding;
    }
    return adding;
}


/* 
Propósito: Borrar el arbol BST
Precondición: La raiz del arbol
Postcondición: el arbol se elimina
Complejidad: O(n)
*/
void ArbolBST::deleteTree(Node* root) { 
    // If tree empty, return
    if (root == nullptr) {
        return;
    }
    // Recursively go through tree to delete all nodes
    deleteTree(root->left);
    deleteTree(root->right);

    // Delete current node
    delete root;

    // If currently at root, set root to nullptr
    if (this->root == root) {
        this->root = nullptr;
        std::cout << "Árbol borrado\n";
    }
}

/* 
Propósito: Mostrar en consola la IP y la cantidad de veces que accedió a otra IP
Precondición: El valor de IP a mostrar
Postcondición: La llave (numero de repeticiones de la IP) y el valor de la IP
Complejidad: O(1)
*/
void ArbolBST::displayKeyIP(Node* disp) { 
    std::cout << "IP: " << disp->ip << " con " << disp->key << " accesos\n";
}

/* 
Propósito: Recorrer el arbol y buscar las 5 IPs más repetidas
Precondición: Raiz del Arbol BST y variable contador inicializado en 0
Postcondición: 5 nodos con Ip más repetidos
Complejidad: O(n)
*/
void ArbolBST::recorrido(Node* root, int& counter, int& lim) { 
    // Caso base hoja o ya se encontraron los cinco más grandes
    if (root == nullptr || counter>=lim) {
        return;
    }
    // Checa lado derecho 
    recorrido(root->right, counter,lim);
    // Desplega dato
    if (counter < lim) {
        displayKeyIP(root);
        counter++;
    }
    recorrido(root->left, counter,lim);
}

/* 
Propósito: Mostrar 5 IPs mas repetidas
Precondición: Raiz del Arbol BST
Postcondición: mostrar en consola las 5 mas repetidas de mayor a menor cantidad de acceso
Complejidad: O(1)
*/
void ArbolBST::recorrer5grandes(Node* root){
    std::cout << "Mostrando las 5 IPs de origen con más conexiones...\n";
    int contador=0;
    int lim=5;
    recorrido(root,contador,lim);
    std::cout<<"\n";
}
/* 
Propósito: Mostrar boot master
Precondición: Raiz del Arbol BST
Postcondición: mostrar en consola la IP boot master
Complejidad: O(1)
*/
void ArbolBST::bootMaster(Node* root){
    std::cout<<"Direccion IP de boot master...\n";
    int contador=0;
    int lim=1;
    recorrido(root,contador,lim);
    std::cout<<"\n";
}