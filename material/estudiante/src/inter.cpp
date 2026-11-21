#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
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

    ifstream g(argv[2]);
    // Error si no se puede abrir el otro archivo.
    if (!g) {
        return 1;
    }

    Guia_Tlf gt1,gt2,gt3;
    f >> gt1;
    g >> gt2;
    
    gt3 = gt1.inter(gt2);
    
    cout << gt3;

    return 0;
} 