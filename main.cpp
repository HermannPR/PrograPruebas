/* 
Propósito: Leer y almacenar el archivo en un grafo con lista de adyacencias y encontrar los
mayores fan-outs de las IP almacenadas en el grafo.
Autoras: Monica Guzman A00838824, Cielo Vega A01741542, Fatima Castillo A00838972
Fecha: 14/11/2024
Complejidad: O(n + m * log(m))
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "nodo.h"
#include "bst.h"

int main(){
    // Lectura archivo
    std::fstream bitacora("bitacoraACT4_3(B).txt");
    std::string line,palabra;

    // Setup 
    std::vector<std::string> IPtemp; // Carga IPs temporalmente
    std::vector<std::vector<std::string>> grafoFinal; // Guarda todo el grafo
    std::vector<std::string> tempAdy; // Para agregar nodos al garfo
    
    // Cantidad de nodos y adyacencias
    int nodos, adyacencias;
    std::getline(bitacora, line);
    std::cout << line;
    std::istringstream iss(line);
    iss >> nodos >> adyacencias;
    
    // Vector de nodos 
    for (int i = 0; i < nodos; i++){
        std::getline(bitacora, line);
        IPtemp.push_back(line);
    } 

    std::cout << "\nCandidad de nodos guardados: " << IPtemp.size() << "\n"; 
    std::cout << "Estableciendo adyaciencias, esto puede tardar un poco...\n"; 
    
    // Vector de adyaciencias 
    int edgesAdded = 0; // Declara fuera de ciclo para poder pasar como parametro e incrementarlo
    std::string prevNodeIP = ""; // Stores IP of previous node

    // Change number to adyacencias
    while (edgesAdded < adyacencias) { 
        std::string fecha, ipNodo, ipAdy, puertoN, puertoA, falla, temp;
        std::getline(bitacora, line);
        std::istringstream iss2(line);
        
        //Fecha
        iss2 >> temp; fecha+=temp+" "; // Agrega mes
        iss2 >> temp; fecha+=temp+" "; // Agrega día
        iss2 >> temp; fecha+=temp+" "; // Agrega hora
        
        //IP nodo y puerto
        iss2 >> ipNodo;
        size_t pos = ipNodo.find(':');
        if (pos != std::string::npos) {
            puertoN = ipNodo.substr(pos + 1);
            ipNodo = ipNodo.substr(0, pos);
        }

        //IP adyacencia y puerto
        iss2 >> ipAdy;
        size_t pos2 = ipAdy.find(':');
        if (pos2 != std::string::npos) {
            puertoA = ipAdy.substr(pos2 + 1);
            ipAdy = ipAdy.substr(0, pos2);
        }
        
        //Falla
        getline(iss2,falla);

        // Hacer conexión entre origen a destino
        bool originPresent = false; 

        // Checa si ya se encuentra el nodo de origen en el vector
        for (int i = 0; i < grafoFinal.size(); i++) {
            // Grafo at index 0 with element 0 is equal to current node origen
            if (grafoFinal.at(i).at(0) == ipNodo) {
                originPresent = true; 
                grafoFinal.at(i).push_back(ipAdy);
                break; 
            }
        }

        // Si no hay nodo de origen ahorita, prints it out
        if (!originPresent) { 
            tempAdy.push_back(ipNodo); // Agrega nodo de origen
            tempAdy.push_back(ipAdy); // Agrega nodo de destino
            grafoFinal.push_back(tempAdy); // Agrega ambos a grafo
            tempAdy.clear(); 
        }

        edgesAdded++; // Cuenta que se hizo otra conexión
        
    }
    std::cout << "\nNúmero de conexiones formadas: " << edgesAdded << "\n\n";

    // Temp display of nodes, actualizando para hacer arbol binario
    ArbolBST arbolIPs; 

    // Archivo de texto para validar resultados más fácil
    std::ofstream outFile("origenDestinos.txt"); 

    for (int i = 0; i < grafoFinal.size(); i++) { 
        // Usa ip de origen para formar su árbol binario 
        outFile << "Origen:    " << grafoFinal.at(i).at(0); 
        outFile << "\nDestinos:  ";
        // Para subir todas IPs destino a archivo text
        for (int j = 1; j < grafoFinal.at(i).size(); j++) { 
            outFile << grafoFinal.at(i).at(j) << "\n";
        }
        
        // Formación del árbol; si no se utiliza el archivo texto, solo se necesita esto
        int key = grafoFinal.at(i).size() - 1; // Numero de ady para IP - 1 para excluir el origen 
        outFile << "Key: " << key;
        // Usa root del árbol binario, key, y los agrega al IP de origen
        arbolIPs.addLeaf(arbolIPs.root, key, grafoFinal.at(i).at(0));

        outFile << "\n------------------------------\n"; // New line
    }
    outFile.close(); // Cierra archivo de output
    std::cout<<"Se creo el archivo 'origenDestino' con el fan-out de cada nodo\n\n";

    arbolIPs.recorrer5grandes(arbolIPs.root); // Encontrar 5 más grandes
    arbolIPs.bootMaster(arbolIPs.root); //Boot master
    arbolIPs.deleteTree(arbolIPs.root); // Deletes tree
    //Deletes all vectors
    IPtemp.clear();
    grafoFinal.clear();
    tempAdy.clear();
    return 0;
}
