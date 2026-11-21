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
    if(argc != 4)
        return 1;

    ifstream f(argv[1]);

    // Error si no se puede abrir el archivo.
    if (!f) {
        return 1;
    }

    Guia_Tlf gt;
    f >> gt;
    
    string nombre = argv[2];
    string num = argv[3];
    gt.modi(nombre, num);

    cout << gt;

    return 0;
} 