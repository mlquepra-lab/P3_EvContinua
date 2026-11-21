/**
 * @file apariciones.cpp
 * @brief Programa que cuenta cuántas veces aparece un carácter en un diccionario.
 *
 * @details Uso: <tt>./apariciones &lt;fichero_diccionario&gt; &lt;caracter&gt;</tt>
 *
 * Lee todas las palabras del fichero en un Dictionary y muestra por pantalla el
 * número de apariciones del carácter indicado (se usa solo el primer carácter
 * del segundo argumento).
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
 * carácter a contar.
 * @return 0 si todo es correcto; 1 si el número de argumentos no es el
 * esperado o no se puede abrir el fichero.
 *
 * @pre @p argv[2] no es una cadena vacía.
 * @post Se escribe por la salida estándar el mensaje
 * <tt>El caracter X aparece N veces.</tt>
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
    char caracter = argv[2][0];

    int apariciones = d.getOccurrences(caracter);

    cout << "El caracter " << caracter << " aparece " << apariciones << " veces. \n";
    return 0;
}
