 // Hermann Pauwells Rivera
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <vector>
#include <algorithm>
#include "nodo.h"
#include "bst.h"

int main() {
    // Apertura del archivo
    std::fstream bitacora("bitacora_reformatted.txt");
    if (!bitacora.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo 'bitacora_reformatted.txt'.\n";
        return 1;
    }

    std::string line;
    std::unordered_map<std::string, int> ipCount;
    std::regex ipRegex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))");
    std::smatch match;

    // Leer el archivo y extraer las IPs
    while (std::getline(bitacora, line)) {
        if (!line.empty() && std::regex_search(line, match, ipRegex)) {
            std::string ip = match.str();
            ipCount[ip]++;
        }
    }
    bitacora.close();

    std::cout << "Cantidad de IPs únicas: " << ipCount.size() << "\n";

    // Crear el árbol binario de búsqueda (BST)
    ArbolBST arbolIPs;

    // Agregar cada IP y su número de accesos al árbol
    for (const auto& entry : ipCount) {
        arbolIPs.addLeaf(arbolIPs.root, entry.second, entry.first);
    }

    // Recopilar nodos y ordenar
    std::vector<std::pair<int, std::string>> nodos;
    arbolIPs.recopilarNodos(arbolIPs.root, nodos);
    std::sort(nodos.rbegin(), nodos.rend());

    // Mostrar las primeras 5 IPs
    std::cout << "\nLas primeras 5 IPs:\n";
    int limite = std::min(5, (int)nodos.size());
    for (int i = 0; i < limite; ++i) {
        std::cout << "IP: " << nodos[i].second << " con " << nodos[i].first << " accesos\n";
    }

    // Mostrar la IP con más accesos ("boot master")
    if (!nodos.empty()) {
        std::cout << "\nDireccion IP de boot master...\n";
        std::cout << "IP: " << nodos[0].second << " con " << nodos[0].first << " accesos\n";
    }

    // Eliminar el árbol binario
    arbolIPs.deleteTree(arbolIPs.root);

    std::cout << "Finalizado.\n";
    return 0;
}
