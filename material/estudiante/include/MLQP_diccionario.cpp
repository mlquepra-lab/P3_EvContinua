#include "diccionario_Manu.h"
#include <iterator>
using namespace std;

/**
* @brief Copia el diccionario D en nuestro diccionario
* @param Paso por referencia del diccionario que se quiere copiar
* @post Se copia el diccionario 
*/
template <typename T, typename U>
void Diccionario<T, U>::Copiar(const Diccionario<T, U>& D){
    typename list<data<T, U>>::const_iterator iter;

    datos.clear();

    for(iter = D.datos.begin(); iter != D.datos.end(); ++iter){
        datos.push_back(*iter);
    }
}

/**
* @brief Borra todo el contenido del diccionario
* @post El diccionario queda borrado
*/
template <typename T, typename U>
void Diccionario<T, U>::Borrar(){
    datos.clear();
}

/**
* @brief Constructor vacio
* @post El diccionario tiene 0 elementos
*/
template <typename T, typename U>
Diccionario<T, U>::Diccionario(){
}

/**
* @brief Constructor de copia
* @param Paso por referencia del diccionario que se quiere copiar
* @post Se copia el diccionario 
*/
template <typename T, typename U>
Diccionario<T, U>::Diccionario(const Diccionario &D){
    Copiar(D);
}

/**
* @brief Destructor
* @post Borra el diccionario
*/
template <typename T, typename U>
Diccionario<T, U>::~Diccionario(){
    Borrar();
}

/**
* @brief Sobrecarga de =
* @param Paso por referencia del diccionario que se quiere copiar
* @post Se copia el diccionario 
*/
template <typename T, typename U>
Diccionario<T, U> & Diccionario<T, U>::operator=(const Diccionario<T, U> &D){
    if (this != &D) {
        Copiar(D);
    }
    return *this;
}


