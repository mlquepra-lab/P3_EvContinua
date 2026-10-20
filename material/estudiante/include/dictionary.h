#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */
class Dictionary{
private:
  set<string> words;
public:

  /**
   * @brief Constructor por defecto
   *
   * Crea un Dictionary vacío
   */
  Dictionary();

  /**
   * @brief Constructor de copia
   *
   * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
   *
   * @param other Dictionary que se quiere copiar
   */
  Dictionary(const Dictionary& other);

  /**
   * @brief Destructor
   *
   * Limpia todos los elementos del Dictionary antes de borrarlo
   */
  ~Dictionary();

  /**
   *  \brief Limpia el Dictionary
   *
   *  Elimina todas las palabras contenidas en el conjunto
   */
  void clear();

  /**
   * @brief Tamaño del diccionario
   *
   * @return Número de palabras guardadas en el diccionario
   */
  unsigned int size()const;

  /**
   * @brief Devuelve las palabras en el diccionario con una longitud dada
   * @param length Longitud de las palabras buscadas
   * @return Vector de palabras con la longitud desdeada
   */
  vector<string> wordsOfLength(int length);

  /**
   * @brief Indica si una palabra esta en el diccionario o no.
   *
   * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
   *
   * @param palabra: la palabra que se quiere buscar.
   * @return Booleano indicando si la palabra existe o no en el diccionario
   */
  bool exists(const string& val)const{return words.count(val) > 0;}

  /**
   * @brief Indica el numero de apariciones de una letra.
   * @param c letra a buscar.
   * @return Un entero indicando el numero de apariciones.
   */
  int getOccurrences(const char c);

  /**
   * @brief Añade al diccionario actual el que se pasa como argumento
   * @param dic diccionario pasado como argumento.
   */
  void anade(const Dictionary &dic);

  /**
   * @brief Comprueba si el diccionario está vacio.
   * @return true si el diccionario está vacío, false en caso contrario
   */
  bool empty()const{return words.empty();}

  /**
   * @brief Elimina una palabra del diccionario
   *
   * @param val Palabra a borrar del diccionario
   *
   * @return Booleano que indica si la palabra se ha borrado del diccionario
   */
  bool erase(const string &val){return words.erase(val) > 0;}

  /**
   * @brief Inserta una palabra en el diccionario
   *
   * @param val palaba a insertar en el diccionario
   * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
   * con éxito si no existía previamente en el diccionario
   */
  bool insert(const string &val);


  /**
   * @brief Sobrecarga del operador de asignación
   */
  Dictionary& operator=(const Dictionary &dic);

  /**
   * @brief Sobrecarga del operador de entrada
   *
   * Permite leer las palabras de un fichero de texto e introducirlas en el
   * diccionario
   *
   * @param is Flujo de entrada
   * @param dic Diccionario a rellenar
   * @return Flujo de entrada para poder encadenar el operador
   */
  friend istream& operator>>(istream &is, Dictionary &dic);

  /**
   * @brief Sobrecarga del operador de salida
   *
   * Permite imprimir el diccionario completo a un flujo de salida
   *
   * @param os Flujo de salida, donde imprimir el diccionario
   * @param dic Diccionario a imprimir
   * @return Flujo de salida, para poder encadenar el operador
   */
  friend ostream& operator<<(ostream &os, const Dictionary &dic);

  class iterator{
  private:
    set<string>::iterator it;
  public:
    iterator(){}
    iterator(const set<string>::iterator& otro):it(otro){}
    iterator(const iterator& otro):it(otro.it){}
    ~iterator(){}
    iterator& operator=(const set<string>::iterator& otro){it=otro;return *this;}
    iterator& operator=(const iterator& otro){it=otro.it;return *this;}
    string operator*()const{return *it;}
    iterator& operator++(){++it;return *this;}
    iterator& operator--(){--it;return *this;}
    iterator& operator++(int){it++;return *this;}
    iterator& operator--(int){it--;return *this;}
    bool operator!=(const iterator& otro){return it != otro.it;}
    bool operator==(const iterator& otro){return it == otro.it;}
  };

  /**
   * @brief Class const_iterator
   * @details Se hace para poder iterar sobre los elementos de tipo LettersSet que sean constantes
   */
  class const_iterator{
  private:
    set<string>::const_iterator const_it;
  public:
    const_iterator(){}
    const_iterator(const set<string>::const_iterator& otro):const_it(otro){}
    const_iterator(const const_iterator& otro):const_it(otro.const_it){}
    ~const_iterator(){}
    const_iterator& operator=(const set<string>::const_iterator& otro){const_it = otro;return *this;}
    const_iterator& operator=(const const_iterator& otro){const_it = otro.const_it;return *this;}
    const string operator*()const{return *const_it;}
    const_iterator& operator++(){++const_it;return *this;}
    const_iterator& operator--(){--const_it;return *this;}
    const_iterator& operator++(int){const_it++;return *this;}
    const_iterator& operator--(int){const_it--;return *this;}
    bool operator!=(const const_iterator& otro){return const_it != otro.const_it;}
    bool operator==(const const_iterator& otro){return const_it == otro.const_it;}
  };

  iterator begin(){iterator i = words.begin();return i;}
  iterator end(){iterator i = words.end();return i;}
  const_iterator begin()const{const_iterator i = words.begin();return i;}
  const_iterator end()const{const_iterator i = words.end();return i;}

};

#endif
