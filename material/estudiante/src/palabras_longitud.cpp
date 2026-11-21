/**
 * @file palabras_longitud.cpp
 * @brief Programa que muestra las palabras de un diccionario con una longitud dada.
 *
 * @details Uso: <tt>./palabras_longitud &lt;fichero_diccionario&gt; &lt;longitud&gt;</tt>
 *
 * Lee todas las palabras del fichero en un Dictionary y escribe por pantalla,
 * una por línea y en orden alfabético, las que tienen exactamente la longitud
 * indicada.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <set>
#include "dictionary.h"

using namespace std;

/**
 * @brief Función principal del programa.
 * @param argc Número de argumentos de la línea de órdenes (debe ser 3).
 * @param argv Argumentos: nombre del programa, fichero con el diccionario y
 * longitud buscada (entero).
 * @return 0 si todo es correcto; 1 si el número de argumentos no es el
 * esperado o no se puede abrir el fichero.
 *
 * @post Se escribe por la salida estándar cada palabra encontrada seguida de un
 * salto de línea. Si no hay ninguna, no se escribe nada.
 * @note La longitud se convierte con @c atoi, por lo que un argumento no
 * numérico equivale a 0.
 */
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
