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

    Dictionary d;
    f >> d;
    int tamanio = atoi(argv[2]);

    vector<string> v = d.wordsOfLength(tamanio);

    for(vector<string>::iterator it=v.begin();it!=v.end();it++)
        cout << *it << "\n";

    return 0;
} 