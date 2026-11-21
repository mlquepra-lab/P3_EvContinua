#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include "dictionary.h"

using namespace std;

int main (int argc, char *argv[])
{
    // Error si el número de argumentos no es el requerido.
    if(argc != 3)
        return 1;

    ifstream f(argv[1]);

    // Error si no se puede abrir el archivo.
    if (!f) {
        return 1;
    }

    ifstream g(argv[2]);
    // Error si no se puede abrir el otro archivo.
    if (!g) {
        return 1;
    }

    Dictionary d1,d2;
    f >> d1;
    g >> d2;
    
    Dictionary dn(d1);
    dn.anade(d2);
    
    string nombre;
    cout << "Introduzca el nombre del fichero a crear: ";
    cin >> nombre;
    ofstream salida(nombre+".txt");
    // Comprobamos que se ha podido crear el fichero
    if (!salida) {
        return 1;
    }
    salida << dn;
    salida.close();
    return 0;
} 