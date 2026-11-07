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


/**
Apunta al siguiente, para que la inserccion sea antes de ese numero
Manteniendo el orden
*/
template <typename T, typename U>
bool Diccionario<T, U>::Esta_Clave(const T &p, typename Diccionario<T,U>::iterator &it_out){
    bool result=false;
    it_out = begin();

    while (it_out != end() && (*it_out).clave < p) {
        ++it_out;
    }

    if (it_out != end() && (*it_out).clave == p) {
        result=  true;
    }

    return result;
}

template <typename T, typename U>
void Diccionario<T, U>::Insertar(const T& clave, const list<U> &info){
    typename Diccionario<T,U>::iterator it_out;
    data<T, U> dato;

    if(!Esta_Clave(clave, it_out)){
        dato.clave = clave;
        dato.info_asoci = info;

        datos.insert(it_out,dato);
    }

}

template <typename T, typename U>
void Diccionario<T, U>::AddSignificado_Palabra(const U & s, const T &p){
    typename Diccionario<T,U>::iterator it_out;

    if(Esta_Clave(p, it_out)){
        (*it_out).info_asoci.push_back(s);
    }
    else{
        list<U> info;
        info.push_back(s);
        Insertar(p, info);
    }

}
