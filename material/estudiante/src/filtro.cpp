#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include "guiatlf.h"

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

    Guia_Tlf gt,gtn;
    f >> gt;
    
    string nombre = argv[2];
    // Distingue mayúsculas y minúsculas
    gtn = gt.filtro(nombre);

    cout << gtn;

    return 0;
} 