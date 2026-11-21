/**
 * @file dictionary.cpp
 * @brief Implementación del TDA Dictionary (conjunto ordenado de palabras).
 *
 * @details La interfaz (@c \@brief, @c \@param, @c \@return) está documentada
 * en include/dictionary.h. Aquí se documenta la implementación, las
 * precondiciones, las postcondiciones y la eficiencia. Las palabras se guardan
 * en un @c std::set<string>, por lo que están ordenadas alfabéticamente y sin
 * repeticiones.
 */

#include "dictionary.h"
#include <iterator>
#include <set>
#include <string>
#include <vector>
using namespace std;

/**
 * @details El conjunto interno se construye vacío.
 *
 * @post size() == 0.
 */
Dictionary::Dictionary(){
}

/**
 * @details Copia el conjunto interno con la asignación de @c std::set.
 *
 * @post El nuevo diccionario tiene las mismas palabras que @p other.
 * @note Eficiencia: lineal en el número de palabras.
 */
Dictionary::Dictionary(const Dictionary& other){
    words = other.words;
}

/**
 * @details Vacía el conjunto interno antes de destruir el objeto.
 */
Dictionary::~Dictionary()
{
    words.clear();
}

/**
 * @details Llama a @c set::clear().
 *
 * @post size() == 0 y empty() == @c true.
 */
void Dictionary::clear(){
    words.clear();
}

/**
 * @details Devuelve el tamaño del conjunto interno.
 *
 * @note Eficiencia: constante.
 */
unsigned int Dictionary::size() const{
    return words.size();
}

/**
 * @details Recorre todo el conjunto (en orden alfabético) y guarda en un vector
 * las palabras cuya longitud coincide con @p length. Por tanto, el vector
 * resultante también está ordenado alfabéticamente.
 *
 * @post Si ninguna palabra tiene esa longitud, el vector devuelto está vacío.
 * @note Eficiencia: lineal en el número de palabras.
 * @warning En include/dictionary.h el método está declarado como @c const y
 * aquí no: ambas firmas deben coincidir para que compile y Doxygen asocie la
 * documentación.
 */
vector<string> Dictionary::wordsOfLength(int length){
    vector<string> resultado;
    set<string>::iterator it;

    for (it = words.begin(); it != words.end(); it++) {
        if(it->length() == length){
            resultado.push_back(*it);
        }
    }

    return resultado;
}

/**
 * @details Recorre cada palabra del diccionario y, dentro de ella, cada
 * carácter, incrementando un contador cuando coincide con @p c. La comparación
 * distingue entre mayúsculas y minúsculas.
 *
 * @note Eficiencia: lineal en el número total de caracteres del diccionario.
 */
int Dictionary::getOccurrences(const char c) const
{
    int n = 0;
    string w;
    for(const_iterator it = words.begin();it != words.end();it++) {
        w = *it;
        for (size_t i = 0; i < w.length(); ++i)
            if (w[i] == c)
            ++n;
    }

    return n;
}

/**
 * @details Recorre @p dic con un const_iterator y añade al conjunto cada
 * palabra que todavía no existe. Como @c set no admite repetidos, la
 * comprobación con exists() es redundante, pero deja explícita la intención.
 *
 * @post El objeto implícito contiene la unión de sus palabras anteriores y las
 * de @p dic. @p dic no se modifica.
 * @note Eficiencia: @c O(m·log(n+m)), con @c m el tamaño de @p dic y @c n el
 * del objeto implícito.
 */
void Dictionary::anade(const Dictionary &dic){
    Dictionary::const_iterator it;

    for(it = dic.begin(); it != dic.end(); it++){
        if(!exists(*it)){
            words.insert(*it);
        }
    }
}


/**
 * @details Inserta la palabra en el conjunto. @c set::insert devuelve un par
 * cuyo segundo elemento indica si la inserción se ha producido; ese valor es
 * el que se devuelve.
 *
 * @post Si el resultado es @c true, size() aumenta en uno y @p val pertenece al
 * diccionario. Si es @c false, el diccionario no cambia.
 * @note Eficiencia: logarítmica en el número de palabras.
 */
bool Dictionary::insert(const string &val){
    pair<set<string>::iterator, bool> b = words.insert(val);
    return b.second;
}

/**
 * @details Vacía el diccionario implícito con clear() y copia el contenido de
 * @p dic con anade().
 *
 * @post El diccionario implícito tiene las mismas palabras que @p dic.
 * @return Referencia al propio objeto, para permitir asignaciones encadenadas.
 * @warning En una autoasignación (@c d @c = @c d) clear() vacía @p dic antes de
 * copiarlo, por lo que el diccionario se perdería. Si se quiere soportar,
 * habría que comprobar @c this @c != @c &dic.
 */
Dictionary& Dictionary::operator=(const Dictionary &dic){
    clear();
    anade(dic);
    return *this;
}

/**
 * @details Lee palabras separadas por espacios o saltos de línea hasta el final
 * del flujo y las inserta en el conjunto. No vacía el diccionario antes de
 * leer: las palabras se acumulan sobre las que ya había.
 *
 * @pre @p is es un flujo de entrada abierto y válido.
 * @post El flujo queda en estado de fin de fichero (eof/fail), que es la
 * condición que termina el bucle de lectura.
 * @note Eficiencia: @c O(k·log(n)), con @c k el número de palabras leídas.
 */
istream& operator>>(istream &is, Dictionary &dic){
    string palabra;
    while (is >> palabra)
        dic.words.insert(palabra);
    return is;
}

/**
 * @details Recorre el diccionario con un const_iterator y escribe una palabra
 * por línea, en orden alfabético.
 *
 * @pre @p os es un flujo de salida abierto y válido.
 * @note Eficiencia: lineal en el número de palabras.
 */
ostream& operator<<(ostream &os, const Dictionary &dic){
    Dictionary::const_iterator it;

    for(it = dic.begin(); it != dic.end(); it++){
        os << *it;
        os << "\n";
    }

    return os;
}


// bool exists(const string& val)const{return words.count(val) > 0;}
// Definición inline en .h

//bool erase(const string &val){return words.erase(val) > 0;}
// Definición inline en .h

//bool empty()const{return words.empty();}
// Definición inline en .h
