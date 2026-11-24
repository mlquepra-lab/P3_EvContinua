/**
 * @file diccionario.cpp
 * @brief Implementación de la plantilla Diccionario<T,U> y de sus iteradores.
 *
 * @details Como Diccionario es una plantilla, este archivo no se compila por
 * separado: debe ser visible allí donde se instancie la plantilla (por ejemplo,
 * incluyéndolo desde main.cpp).
 *
 * Criterio de documentación: la interfaz (@c \@brief, @c \@param, @c \@return)
 * está en include/diccionario.h; aquí se documenta la implementación
 * (@c \@details), las precondiciones, las postcondiciones y la eficiencia.
 */

#include "diccionario.h"
#include <iterator>
using namespace std;

/**
 * @details Vacía primero el diccionario implícito y después recorre @p D con un
 * const_iterator, añadiendo cada registro al final de la lista interna. Como
 * @p D ya está ordenado, el resultado también lo está.
 *
 * @pre @p D es un diccionario válido (distinto del objeto implícito o no, ya
 * que el operador de asignación comprueba la autoasignación).
 * @post El objeto implícito contiene los mismos registros que @p D, en el mismo orden.
 * @note Eficiencia: lineal en el número de claves de @p D.
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
 * @details Elimina todos los registros de la lista interna con @c list::clear().
 *
 * @post El diccionario queda vacío (size() == 0).
 * @note Eficiencia: lineal en el número de claves.
 */
template <typename T, typename U>
void Diccionario<T, U>::Borrar(){
    datos.clear();
}

/**
 * @details No hace nada explícito: la lista interna se construye vacía.
 *
 * @post El diccionario tiene 0 elementos.
 */
template <typename T, typename U>
Diccionario<T, U>::Diccionario(){
}

/**
 * @details Delega en el método privado Copiar().
 *
 * @post El diccionario implícito es una copia independiente de @p D.
 */
template <typename T, typename U>
Diccionario<T, U>::Diccionario(const Diccionario &D){
    Copiar(D);
}

/**
 * @details Libera los registros llamando al método privado Borrar().
 *
 * @post El diccionario queda vacío y sus recursos liberados.
 */
template <typename T, typename U>
Diccionario<T, U>::~Diccionario(){
    Borrar();
}

/**
 * @details Comprueba la autoasignación (@c this @c != @c &D) para no vaciar el
 * diccionario antes de copiarlo; después delega en Copiar().
 *
 * @post El diccionario implícito es una copia independiente de @p D.
 * @return Referencia al propio objeto, de modo que se permiten asignaciones
 * encadenadas (@c a @c = @c b @c = @c c).
 */
template <typename T, typename U>
Diccionario<T, U> & Diccionario<T, U>::operator=(const Diccionario<T, U> &D){
    if (this != &D) {
        Copiar(D);
    }
    return *this;
}

/**
 * @details El iterador por defecto deja sin inicializar el iterador interno de
 * la lista, por lo que no debe desreferenciarse hasta asignarle un valor válido.
 */
template <typename T, typename U>
Diccionario<T,U>::iterator::iterator(){
}

/**
 * @details Avanza el iterador interno de la lista (@c ++it) y devuelve el propio objeto.
 *
 * @pre El iterador no apunta a end().
 */
template <typename T, typename U>
typename  Diccionario<T, U>::iterator&
Diccionario<T,U>::iterator::operator++(){
    ++it;
    return *this;
}

/**
 * @details Retrocede el iterador interno de la lista (@c --it) y devuelve el propio objeto.
 *
 * @pre El iterador no apunta a begin().
 */
template <typename T, typename U>
typename  Diccionario<T, U>::iterator&
Diccionario<T,U>::iterator::operator--(){
    --it;
    return *this;
}

/**
 * @details Devuelve una referencia no constante al registro, por lo que se
 * puede modificar la información asociada a través del iterador.
 *
 * @pre El iterador no apunta a end().
 * @warning Modificar el campo @c clave rompería la ordenación del diccionario.
 */
template <typename T, typename U>
data<T,U>& Diccionario<T,U>::iterator::operator*() const{
    return *it;
}

/**
 * @details Compara los iteradores internos de la lista.
 */
template <typename T, typename U>
bool Diccionario<T,U>::iterator::operator!=(const iterator& otro) const {
    return it != otro.it;
}

/**
 * @details Compara los iteradores internos de la lista.
 */
template <typename T, typename U>
bool Diccionario<T,U>::iterator::operator==(const iterator& otro) const {
    return it == otro.it;
}

/**
 * @details El iterador constante por defecto deja sin inicializar el iterador
 * interno de la lista, por lo que no debe desreferenciarse hasta asignarle un
 * valor válido.
 */
template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator(){
}

/**
 * @details Avanza el iterador interno de la lista (@c ++it_const) y devuelve el propio objeto.
 *
 * @pre El iterador no apunta a end().
 */
template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator&
Diccionario<T,U>::const_iterator::operator++(){
    ++it_const;
    return *this;
}

/**
 * @details Retrocede el iterador interno de la lista (@c --it_const) y devuelve el propio objeto.
 *
 * @pre El iterador no apunta a begin().
 */
template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator&
Diccionario<T,U>::const_iterator::operator--(){
    --it_const;
    return *this;
}

/**
 * @details Devuelve una referencia constante al registro: solo permite lectura.
 *
 * @pre El iterador no apunta a end().
 */
template <typename T, typename U>
const data<T,U>& Diccionario<T,U>::const_iterator::operator*() const{
    return *it_const;
}

/**
 * @details Compara los iteradores internos de la lista.
 */
template <typename T, typename U>
bool Diccionario<T,U>::const_iterator::operator!=(const const_iterator& otro) const {
    return it_const != otro.it_const;
}

/**
 * @details Compara los iteradores internos de la lista.
 */
template <typename T, typename U>
bool Diccionario<T,U>::const_iterator::operator==(const const_iterator& otro) const {
    return it_const == otro.it_const;
}

/**
 * @details Recorre la lista (ordenada de menor a mayor clave) mientras la clave
 * del registro sea menor que @p p. Al terminar, @p it_out queda apuntando al
 * primer registro con clave mayor o igual que @p p, es decir, al registro que
 * tiene la clave buscada o al que sigue a la posición donde habría que
 * insertarla. Así, @c list::insert(it_out.it, ...) coloca el nuevo registro
 * antes de ese elemento manteniendo el orden.
 *
 * @post @p it_out apunta al registro con clave @p p si el resultado es @c true;
 * en caso contrario apunta a la posición de inserción (puede ser end()).
 * @note Eficiencia: lineal en el número de claves (búsqueda secuencial).
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

/**
 * @details Usa Esta_Clave() para localizar la posición de inserción. Si la
 * clave ya existe no se hace nada (no se admiten claves repetidas); si no, se
 * crea un registro con la clave y la información y se inserta antes de la
 * posición encontrada, de modo que el diccionario sigue ordenado.
 *
 * @post Si @p clave no estaba, size() aumenta en uno y el diccionario sigue
 * ordenado. Si ya estaba, el diccionario no cambia.
 * @note Eficiencia: lineal en el número de claves.
 */
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

/**
 * @details Si la clave existe, añade @p s al final de su lista de información.
 * Si no existe, crea una lista con @p s como único elemento y la inserta
 * mediante Insertar().
 *
 * @post La clave @p p está en el diccionario y @p s es el último elemento de
 * su información asociada.
 * @note Eficiencia: lineal en el número de claves.
 */
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
 * @details Busca la clave con Esta_Clave() y, si existe, devuelve una copia de
 * su lista de información asociada. Si no existe, devuelve una lista vacía.
 *
 * @note Eficiencia: lineal en el número de claves (más la copia de la lista).
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
 * @details Devuelve el tamaño de la lista interna.
 *
 * @note Eficiencia: constante (@c list::size() en C++11 o posterior).
 */
template <typename T, typename U>
int Diccionario<T, U>::size()const{
    return datos.size();
}

/**
 * @details Busca la clave con Esta_Clave() y, si existe, elimina su registro
 * con @c list::erase().
 *
 * @post Si el resultado es @c true, size() disminuye en uno y la clave @p c
 * deja de estar en el diccionario.
 * @note Eficiencia: lineal en el número de claves.
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
 * @details Primero copia en un diccionario nuevo todos los registros del objeto
 * implícito. Después recorre @p D y, para cada elemento de la información
 * asociada de cada clave, llama a AddSignificado_Palabra(): si la clave ya
 * existía se concatena la información y, si no, se crea una entrada nueva.
 * Ninguno de los dos diccionarios originales se modifica.
 *
 * @post Cada clave de cualquiera de los dos diccionarios aparece una sola vez
 * en el resultado, con la información del objeto implícito seguida de la de @p D.
 * @note Eficiencia: cuadrática en el número de claves, porque cada inserción
 * es lineal.
 */
template <typename T, typename U>
Diccionario<T, U> Diccionario<T, U>::union_d(const Diccionario & D){
    Diccionario<T, U> nuevoDiccionario;

    typename Diccionario<T,U>::iterator it1 = begin();
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
 * @details Copia en un diccionario nuevo todos los registros del objeto
 * implícito y, a continuación, borra de esa copia cada clave que aparece en
 * @p D. El objeto implícito y @p D no se modifican.
 *
 * @post El resultado contiene exactamente las claves del objeto implícito que
 * no están en @p D, con su información asociada.
 * @note Eficiencia: cuadrática en el número de claves.
 */
template <typename T, typename U>
Diccionario<T, U> Diccionario<T, U>::diferencia(const Diccionario &D) {
    Diccionario<T, U> nuevoDiccionario;

    typename Diccionario<T,U>::iterator it1 = begin();
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

/**
 * @details Se calcula como @c (A @c ∪ @c B) @c − @c ((A @c − @c B) @c ∪ @c (B @c − @c A)),
 * reutilizando union_d() y diferencia():
 *  -# @c resultado = union de ambos diccionarios.
 *  -# @c dif = claves solo del objeto implícito; @c dif2 = claves solo de @p D
 *     (se usa una copia de @p D porque diferencia() no es constante).
 *  -# Se quitan de @c resultado las claves de @c dif ∪ @c dif2, quedando solo
 *     las claves comunes.
 *
 * @post Las claves del resultado son las comunes a ambos diccionarios; su
 * información asociada es la unión de la de ambos (la del objeto implícito
 * seguida de la de @p D).
 * @note Eficiencia: cuadrática en el número de claves.
 */
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

/**
 * @details Es una plantilla sobre el tipo de iterador @p I, por lo que
 * funciona tanto con iterator como con const_iterator. Recorre @p i hasta @p f
 * (excluido) añadiendo cada registro al final de un diccionario nuevo. Al estar
 * el diccionario origen ordenado, el resultado también lo está.
 *
 * @pre @p i y @p f son iteradores del mismo diccionario y @p f es alcanzable
 * desde @p i.
 * @post Si @p i == @p f, el resultado es un diccionario vacío.
 * @note Eficiencia: lineal en la longitud del intervalo.
 */
template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::Devolver_rango(const T &i, const T &f) const {

    Diccionario<T, U> nuevo_diccionario;

    typename Diccionario<T,U>::const_iterator it;
    it = begin();

    while (it != end() && (*it).clave <= f) {

        if ((*it).clave >= i) {
            nuevo_diccionario.datos.push_back(*it);
        }

        ++it;
    }

    return nuevo_diccionario;
}

/**
 * @details Construye un iterator cuyo iterador interno apunta al principio de
 * la lista.
 */
template <typename T, typename U>
typename  Diccionario<T, U>::iterator
Diccionario<T, U>::begin() {
    iterator i ;
    i.it = datos.begin() ;
    return i ;
};

/**
 * @details Construye un iterator cuyo iterador interno apunta a la posición
 * siguiente al último registro de la lista. No se puede desreferenciar.
 */
template <typename T, typename U>
typename  Diccionario<T, U>::iterator
Diccionario<T, U>::end() {
    iterator i ;
    i.it = datos.end() ;
    return i ;
};

/**
 * @details Versión constante de begin(): el iterador solo permite lectura.
 */
template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator
Diccionario<T, U>::begin() const {
    const_iterator i ;
    i.it_const = datos.begin() ;
    return i ;
};

/**
 * @details Versión constante de end(): el iterador solo permite lectura y no
 * se puede desreferenciar.
 */
template <typename T, typename U>
typename  Diccionario<T, U>::const_iterator
Diccionario<T, U>::end() const {
    const_iterator i ;
    i.it_const = datos.end() ;
    return i ;
};

/**
 * @details Inicializa el iterador interno con el iterador de lista @p iter.
 */
template <typename T, typename U>
Diccionario<T,U>::iterator::iterator(const typename std::list<data<T, U>>::iterator& iter) {
    it = iter;
}

/**
 * @details Inicializa el iterador interno con el iterador constante de lista @p iter.
 */
template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator(const typename std::list<data<T, U>>::const_iterator& iter) {
    it_const = iter;
}

/**
 * @details Crea una copia con el iterador interno avanzado a la vez que se
 * incrementa el original: la copia devuelta se construye con el valor previo
 * de @c it (@c it++).
 *
 * @pre El iterador no apunta a end().
 */
template <typename T, typename U>
typename Diccionario<T,U>::iterator
Diccionario<T,U>::iterator::operator++(int) {
  iterator iter(it++);
  return iter;
}

/**
 * @details Crea una copia con el valor previo del iterador interno y después
 * avanza el original (@c it_const++).
 *
 * @pre El iterador no apunta a end().
 */
template <typename T, typename U>
typename Diccionario<T,U>::const_iterator
Diccionario<T,U>::const_iterator::operator++(int) {
  const_iterator iter(it_const++);
  return iter;
}

/**
 * @details Crea una copia con el valor previo del iterador interno y después
 * retrocede el original (@c it--).
 *
 * @pre El iterador no apunta a begin().
 */
template <typename T, typename U>
typename Diccionario<T,U>::iterator
Diccionario<T,U>::iterator::operator--(int) {
  iterator iter(it--);
  return iter;
}

/**
 * @details Crea una copia con el valor previo del iterador interno y después
 * retrocede el original (@c it_const--).
 *
 * @pre El iterador no apunta a begin().
 */
template <typename T, typename U>
typename Diccionario<T,U>::const_iterator
Diccionario<T,U>::const_iterator::operator--(int) {
  const_iterator iter(it_const--);
  return iter;
}
