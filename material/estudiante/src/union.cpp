/**
 * @file union.cpp
 * @brief Programa que calcula la unión de dos diccionarios y la guarda en un fichero.
 *
 * @details Uso: <tt>./union &lt;diccionario1&gt; &lt;diccionario2&gt;</tt>
 *
 * Lee las palabras de los dos ficheros en sendos Dictionary, calcula su unión
 * (sin palabras repetidas) y pide por teclado el nombre del fichero de salida.
 * El resultado se escribe, una palabra por línea y en orden alfabético, en el
 * fichero <tt>&lt;nombre&gt;.txt</tt>.
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
 * @param argv Argumentos: nombre del programa y los dos ficheros con los
 * diccionarios que se unen.
 * @return 0 si todo es correcto; 1 si el número de argumentos no es el
 * esperado o no se puede abrir alguno de los ficheros (entrada o salida).
 *
 * @post Se crea el fichero <tt>&lt;nombre&gt;.txt</tt> con la unión de ambos
 * diccionarios. Los ficheros de entrada no se modifican.
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
