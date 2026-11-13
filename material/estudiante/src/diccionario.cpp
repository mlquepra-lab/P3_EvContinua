#include "../include/diccionario.h"
#include <iterator>
using namespace std;

/**
* @brief Copia el diccionario D en nuestro diccionario
* @param Paso por referencia del diccionario que se quiere copiar
* @post Se copia el diccionario 
*/
template <typename T, typename U>
void Diccionario<T, U>::Copiar(const Diccionario<T, U>& D){
    typename Diccionario<T, U>::const_iterator iter;

    datos.clear();

    for(iter = D.begin(); iter != D.end(); ++iter){
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
* @brief Constructor del iterador
*/
template <typename T, typename U>
Diccionario<T,U>::iterator::iterator(){
}

template <typename T, typename U>
typename  Diccionario<T, U>::iterator&
Diccionario<T,U>::iterator::operator++(){
    ++it;
    return *this;
}

template <typename T, typename U>
typename  Diccionario<T, U>::iterator&
Diccionario<T,U>::iterator::operator--(){
    --it;
    return *this;
}

template <typename T, typename U>
data<T,U>& Diccionario<T,U>::iterator::operator*() const{
    return *it;
}

template <typename T, typename U>
bool Diccionario<T,U>::iterator::operator!=(const iterator& otro) const {
    return it != otro.it;
}

template <typename T, typename U>
bool Diccionario<T,U>::iterator::operator==(const iterator& otro) const {
    return it == otro.it;
}

/**
* @brief Constructor del iterador
*/
template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator(){
}

template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator&
Diccionario<T,U>::const_iterator::operator++(){
    ++it_const;
    return *this;
}

template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator&
Diccionario<T,U>::const_iterator::operator--(){
    --it_const;
    return *this;
}

template <typename T, typename U>
const data<T,U>& Diccionario<T,U>::const_iterator::operator*() const{
    return *it_const;
}

template <typename T, typename U>
bool Diccionario<T,U>::const_iterator::operator!=(const const_iterator& otro) const {
    return it_const != otro.it_const;
}

template <typename T, typename U>
bool Diccionario<T,U>::const_iterator::operator==(const const_iterator& otro) const {
    return it_const == otro.it_const;
}

/**
Apunta al siguiente, para que la inserccion sea antes de ese numero
Manteniendo el orden
*/
template <typename T, typename U>
bool Diccionario<T, U>::Esta_Clave(const T &p, typename Diccionario<T,U>::iterator &it_out){
    bool result=false;
    it_out = begin();

    // Busqueda de p
    while (it_out != end() && (*it_out).clave < p) {
        ++it_out;
    }

    // Si el iterador se ha parado en el iterador devuelve true
    if (it_out != end() && (*it_out).clave == p) {
        result = true;
    }

    return result;
}


template <typename T, typename U>
void Diccionario<T, U>::Insertar(const T& clave, const list<U> &info){
    typename Diccionario<T,U>::iterator it_out = begin();
    data<T, U> dato;

    if(!Esta_Clave(clave, it_out)){
        dato.clave = clave;
        dato.info_asoci = info;

        datos.insert(it_out.it,dato);
    }
}

template <typename T, typename U>
void Diccionario<T, U>::AddSignificado_Palabra(const U & s, const T &p){
    typename Diccionario<T,U>::iterator it_out = begin();

    if(Esta_Clave(p, it_out)){
        (*it_out).info_asoci.push_back(s);
    }
    else{
        list<U> info;
        info.push_back(s);
        Insertar(p, info);
    }
}

/**
Devuelve la información (una lista) asociada a una clave p.
devuelve una lista con la informacion asociada a la clave.
*/
template <typename T, typename U>
list<U> Diccionario<T, U>::getInfo_Asoc(const T & p){

    typename Diccionario<T,U>::iterator it_out = begin();
    list<U> resultado;

    if(Esta_Clave(p, it_out)){
         resultado = (*it_out).info_asoci;
    }

    return  resultado;

}

/**
Devuelve el tamaño del diccionario
tamaño del diccionario
*/
template <typename T, typename U>
int Diccionario<T, U>::size()const{
    return datos.size();
}

/**
borra un data del diccionario por su clave
c es la clave cuyo elemento queremos borrar. Devuelve
true si se ha borrado el elemento, false si no
*/
template <typename T, typename U>
bool Diccionario<T, U>::Borrar(const T & c){

    typename Diccionario<T,U>::iterator it_out = begin();
    bool result = false;

    if(Esta_Clave(c, it_out)){
        datos.erase(it_out.it);
        result = true;
    }

    return result;
}

/**
Union de 2 diccionarios
Si una clave aparece en ambos diccionarios en el resultante aparece una sola vez con la union
de las informaciones asociadas.
*/
template <typename T, typename U>
Diccionario<T, U> Diccionario<T, U>::union_d(const Diccionario & D){
    Diccionario<T, U> nuevoDiccionario;

    typename Diccionario<T,U>::const_iterator it1 = begin();
    typename Diccionario<T,U>::const_iterator it2 = D.begin();


    // Ponemos todo el contenido de nuestro diccionario
    while (it1 != end()) {
        nuevoDiccionario.Insertar((*it1).clave, (*it1).info_asoci);
        ++it1;
    }

    // El otro diccionario va a introducir su informacion si ya existe o crear una nueva entrada si no
    while(it2 != D.end()){
        typename list<U>::const_iterator info = (*it2).info_asoci.begin();
        T clave_actual = (*it2).clave;

        // El primer elemento tiene informacion, usamos AddSignificado_Palabra
        for(; info !=(*it2).info_asoci.end(); info++){
            nuevoDiccionario.AddSignificado_Palabra(*info, clave_actual);
        }

        ++it2;
    }

    return nuevoDiccionario;
}

/**
elimina las claves del diccionario que aprecen en D
D diccionario cuyas claves queremos eliminar
*/
template <typename T, typename U>
Diccionario<T, U> Diccionario<T, U>::diferencia(const Diccionario &D) {
    Diccionario<T, U> nuevoDiccionario;

    typename Diccionario<T,U>::const_iterator it1 = begin();
    typename Diccionario<T,U>::const_iterator it2 = D.begin();

    // Ponemos todo el contenido de nuestro diccionario
    while (it1 != end()) {
        nuevoDiccionario.Insertar((*it1).clave, (*it1).info_asoci);
        ++it1;
    }

    while(it2 != D.end()){
        typename Diccionario<T,U>::iterator it_out = nuevoDiccionario.begin();
        T clave_actual = (*it2).clave;

        if(nuevoDiccionario.Esta_Clave(clave_actual, it_out)){
            nuevoDiccionario.Borrar(clave_actual);
        }

        ++it2;
    }
    
    return nuevoDiccionario;
}

template <typename T, typename U>
Diccionario<T, U> Diccionario<T, U>::interseccion(const Diccionario<T, U> & D) {

    Diccionario<T,U> copiaD(D);

    Diccionario<T,U> resultado = union_d(D);
    Diccionario<T,U> dif = diferencia(D);
    Diccionario<T,U> dif2 = copiaD.diferencia(*this);
    
    dif = dif.union_d(dif2);
    resultado = resultado.diferencia(dif);

    return resultado;
}

template <typename T, typename U>
template <typename I>
Diccionario<T,U> Diccionario<T,U>::Devolver_rango(const I &i, const I &f) const {
    Diccionario<T, U> nuevo_diccionario;
    
    I it = i;
    while (it != f) {
        nuevo_diccionario.datos.push_back(*it);
        it++;
    }

    return nuevo_diccionario;
}

/** Funciones begin y end para los iteradores**/
template <typename T, typename U>
typename  Diccionario<T, U>::iterator
Diccionario<T, U>::begin() { 
    iterator i ; 
    i.it = datos.begin() ; 
    return i ; 
};

template <typename T, typename U>
typename  Diccionario<T, U>::iterator
Diccionario<T, U>::end() { 
    iterator i ; 
    i.it = datos.end() ; 
    return i ; 
};

template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator
Diccionario<T, U>::begin() const { 
    const_iterator i ; 
    i.it_const = datos.begin() ; 
    return i ; 
};

template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator
Diccionario<T, U>::end() const { 
    const_iterator i ; 
    i.it_const = datos.end() ; 
    return i ; 
};

