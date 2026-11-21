/**
 * @file guiatlf.cpp
 * @brief Implementación del TDA Guia_Tlf (guía de teléfonos).
 *
 * @details La interfaz (@c \@brief, @c \@param, @c \@return) está documentada
 * en include/guiatlf.h. Aquí se documenta la implementación, las
 * precondiciones, las postcondiciones y la eficiencia. La guía se representa
 * con un @c std::map<string,string> (nombre → teléfono), por lo que está
 * ordenada por nombre y no admite nombres repetidos.
 */

#include "guiatlf.h"

#include <map>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

/**
 * @details Usa @c map::operator[]: si el nombre no existe, se crea una entrada
 * nueva con teléfono vacío.
 *
 * @post El nombre @p nombre pertenece a la guía.
 * @return Referencia modificable al teléfono asociado a @p nombre.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
string & Guia_Tlf::operator[](const string &nombre){
    return datos[nombre];
}

/**
 * @details Busca el nombre con @c map::find (sin crear entradas nuevas, a
 * diferencia de operator[]()).
 *
 * @param nombre Nombre del que se quiere conocer el teléfono.
 * @return El teléfono asociado a @p nombre o la cadena vacía si no existe.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
string  Guia_Tlf::gettelefono(const string & nombre){
    Guia_Tlf::iterator it = datos.find(nombre);

    if (it != datos.end()){
        return it->second;
    }

    return "";
}

/**
 * @details Construye el par (nombre, teléfono) y lo inserta en el mapa. Si el
 * nombre ya existía, no se modifica su teléfono.
 *
 * @post Si el segundo elemento del resultado es @c true, size() aumenta en uno.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(string nombre, string tlf){
    pair<string,string> insertado;

    insertado.first = nombre;
    insertado.second = tlf;

    return datos.insert(insertado);
}

/**
 * @details Inserta directamente el par en el mapa. Si el nombre ya existía, no
 * se modifica su teléfono.
 *
 * @post Si el segundo elemento del resultado es @c true, size() aumenta en uno.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(pair<string,string> p){
    return datos.insert(p);
}

/**
 * @details Llama a @c map::erase con la clave. Si el nombre no existe, no hace
 * nada.
 *
 * @post @p nombre ya no pertenece a la guía.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
void Guia_Tlf::borrar(const string &nombre){
    datos.erase(nombre);
}

/**
 * @details Localiza el nombre y solo borra la entrada si el teléfono asociado
 * coincide con @p tlf. Para borrar se necesita el iterador del mapa, que se
 * obtiene con Guia_Tlf::iterator::getIterator().
 *
 * @post Si existía la entrada exacta (@p nombre, @p tlf), se ha borrado; en
 * otro caso la guía no cambia.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
void Guia_Tlf::borrar(const string &nombre,const string &tlf){
    Guia_Tlf::iterator it = datos.find(nombre);

    if(it != datos.end() && it->second == tlf) {
        datos.erase(it.getIterator());
    }
}

/**
 * @details Inserta primero todas las entradas del objeto implícito y después
 * las de @p g. Como insert() no sobrescribe, si un nombre está en ambas guías
 * se conserva el teléfono del objeto implícito.
 *
 * @post El resultado contiene todos los nombres de ambas guías. Ninguna de las
 * dos guías originales se modifica.
 * @note Eficiencia: @c O((n+m)·log(n+m)).
 */
Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf & g){
    Guia_Tlf result;

    Guia_Tlf::iterator it;
    Guia_Tlf::const_iterator it2;

    for(it = datos.begin(); it != datos.end(); it++){
        result.insert(*it);
    }

    for(it2 = g.datos.begin(); it2 != g.datos.end(); it2++){
        result.insert(*it2);
    }

    return result;
}

/**
 * @details Recorre las entradas del objeto implícito y copia al resultado las
 * que no tienen su nombre en @p g. Solo se compara el nombre, no el teléfono.
 *
 * @post El resultado contiene los nombres del objeto implícito que no están en
 * @p g. Ninguna de las dos guías originales se modifica.
 * @note Eficiencia: @c O(n·log(m)).
 */
Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf & g){
    Guia_Tlf result;

    Guia_Tlf::iterator it;
    Guia_Tlf::const_iterator it2;

    for(it = datos.begin(); it != datos.end(); it++){
        it2=g.datos.find(it->first);
        if(it2 == g.datos.end()){
            result.insert(*it);
        }
    }

    return result;
}

/**
 * @details Busca la entrada (@p nombre, @p tlf). Si existe, copia al resultado
 * todas las entradas que la preceden en el orden del mapa, sin incluirla. Si no
 * existe o el teléfono no coincide, el resultado es una guía vacía.
 *
 * @post El resultado contiene los nombres estrictamente menores que @p nombre.
 * @note Eficiencia: lineal en el número de entradas copiadas.
 */
Guia_Tlf Guia_Tlf::previos(const string &nombre,const string &tlf){
    Guia_Tlf result;

    Guia_Tlf::iterator tope = datos.find(nombre);
    Guia_Tlf::iterator it;

    if((tope != datos.end()) && (tope->second == tlf)){
        for(it = datos.begin(); it != tope; it++){
            result.insert(*it);
        }
    }

    return result;
}

/**
 * @details Recorre las entradas del objeto implícito y copia al resultado las
 * que tienen su nombre en @p g. Solo se compara el nombre; el teléfono que se
 * conserva es el del objeto implícito.
 *
 * @post El resultado contiene los nombres comunes a ambas guías. Ninguna de las
 * dos guías originales se modifica.
 * @note Eficiencia: @c O(n·log(m)).
 */
Guia_Tlf Guia_Tlf::inter(const Guia_Tlf & g){
    Guia_Tlf result;

    Guia_Tlf::iterator it;
    Guia_Tlf::const_iterator it2;

    for(it = datos.begin(); it != datos.end(); it++){
        it2=g.datos.find(it->first);
        if(it2 != g.datos.end()){
            result.insert(*it);
        }
    }

    return result;
}

/**
 * @details Asigna el nuevo teléfono con @c operator[] del mapa.
 *
 * @post @p nombre pertenece a la guía y su teléfono es @p newtlf. Si el nombre
 * no existía, se crea la entrada.
 * @note Eficiencia: logarítmica en el número de entradas.
 */
void Guia_Tlf::modi(const string &nombre, const string &newtlf){
    datos[nombre] = newtlf;
}

/**
 * @details Recorre las entradas y copia al resultado aquellas cuyo nombre
 * empieza por el prefijo @p c, comparando los primeros @c c.size() caracteres
 * con @c substr.
 *
 * @post Si @p c es la cadena vacía, el resultado es una copia de toda la guía.
 * @note Eficiencia: lineal en el número de entradas.
 */
Guia_Tlf Guia_Tlf::filtro(const string & c){
    Guia_Tlf result;

    Guia_Tlf::iterator it;

    for(it = datos.begin(); it != datos.end(); it++){
        if (it->first.substr(0, c.size()) == c) {
            result.insert(*it);
        }
    }

    return result;
}

/**
 * @brief Escribe la guía en un flujo de salida.
 * @param os Flujo de salida (es modificado).
 * @param g Guía que se escribe.
 * @return El flujo @p os, para poder encadenar el operador.
 *
 * @details Escribe una entrada por línea con el formato <tt>nombre : telefono</tt>,
 * en el orden alfabético del mapa.
 *
 * @note Eficiencia: lineal en el número de entradas.
 * @warning En include/guiatlf.h la declaración de este @c friend usa un
 * parámetro no constante (@c Guia_Tlf&); debe ser @c const @c Guia_Tlf& para
 * que coincida con esta definición.
 */
ostream& operator<<(ostream& os, const Guia_Tlf& g) {
    Guia_Tlf::const_iterator it;

    for(it = g.begin(); it != g.end(); ++it) {
        os << (*it).first << " : " << (*it).second << endl;
    }

    return os;
}

/**
 * @brief Lee una entrada de la guía desde un flujo de entrada.
 * @param is Flujo de entrada (es modificado).
 * @param g Guía en la que se inserta la entrada leída (es modificada).
 * @return El flujo @p is, para poder encadenar el operador.
 *
 * @details Lee un nombre y un teléfono (dos palabras separadas por blancos) y
 * los inserta con insert(). Cada llamada lee una sola entrada, no el flujo
 * completo.
 *
 * @pre @p is es un flujo de entrada abierto y válido.
 * @post Si el nombre ya existía en la guía, su teléfono no se modifica.
 */
istream& operator>>(istream& is, Guia_Tlf& g) {
    string nombre, telefono;

    while(is >> nombre >> telefono){
        g.insert(nombre, telefono);
    }

    return is;
}

