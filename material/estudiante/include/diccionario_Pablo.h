#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>


using namespace std;



/*Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
no se repite (DNI p.ej.) y list<U> es una lista de datos (string p.ej) asociados a la clave
de tipo T. El diccionario está ordenado de menor a mayor clave.
 */
template <class T, class U>
struct data {
    T clave;
    list<U> info_asoci;
};



/*Comparador de datos. Ordena 2 registros de acuerdo a la clave de tipo T. Puede usarse como
un funtor.
 */
template <class T, class U>
bool operator<(const data<T, U> &d1, const data <T, U>&d2) {
    if (d1.clave < d2.clave)
        return true;
    return false;

}


template <class T, class U>
class Diccionario {
private:

    list<data<T, U> > datos;

    /**
    * @brief Copia el diccionario de entrada en el objeto implicito.
    */
    void Copiar(const Diccionario<T, U>& D);

    /**
    * @brief Borra todos los datos que contiene el diccionario.
    */
    void Borrar();

public:


    /**
    * @brief Constructor por defecto.
    */
    Diccionario();

    /**
    * @brief Constructor de copia.
    */
    Diccionario(const Diccionario &D);

    /**
    * @brief Destructor.
    */
    ~Diccionario();

    /**
    * @brief Operador de asignación.
    */
    Diccionario<T, U> & operator=(const Diccionario<T, U> &D);

    class iterator{
        private:

        typename list<data<T, U>>::iterator it;

        public:
        
        /**
        * @brief Constructor por defecto.
        */
        iterator ();

        /**
        * @brief Constructor parametrizado.
        */
        iterator (const typename std::list<data<T, U>>::iterator& iter);

        /**
        * @brief Avanza el iterador hasta la siguiente posición (Pre-Incremento: ++it)
        * @return Referencia al iterador tras el incremento.
        */
        iterator& operator++();

        /**
        * @brief Avanza el iterador hasta la siguiente posición (Post-incremento: it++)
        * @param int Sirve para indicar que se trata de it++
        * @return Copia del iterador en la posición anterior
        */
        iterator operator++(int);

        /**
        * @brief Comprueba si iteradores apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator==(const iterator &otro) const;

        /**
        * @brief Comprueba si iteradores no apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator!=(const iterator &otro) const;
        /**
        * @brief Retrasa el iterador hasta la posición anterior (Pre-decremento: --it)
        * @return Refencia al iterador tras el decremento.
        */
        iterator& operator--();

        /**
        * @brief Retrasa el iterador hasta la posición anterior (Post-decremento: it--)
        * @param int Indica que se trata de it--.
        * @return Copia del iterador en la posición anterior al decremento.
        */
        iterator operator--(int);

        /**
        * @brief Accede al elemento al que referencia el iterador.
        * @return El objeto al que referencia.
        */        
        data<T,U>& operator*() const;

        friend class const_iterator;

    };
    class const_iterator{
        private:

        typename list<data<T, U>>::const_iterator it;

        public:
        
        /**
        * @brief Constructor por defecto.
        */
        const_iterator ();

        /**
        * @brief Constructor parametrizado.
        */
        const_iterator (const typename std::list<data<T, U>>::const_iterator& iter);

        /**
        * @brief Constructor para transformar iterator en const_iterator.
        */
        const_iterator(const iterator& otro);


        /**
        * @brief Avanza el iterador hasta la siguiente posición (Pre-Incremento: ++it)
        * @return Referencia al iterador tras el incremento.
        */
        const_iterator& operator++();

        /**
        * @brief Avanza el iterador hasta la siguiente posición (Post-incremento: it++)
        * @param int Sirve para indicar que se trata de it++
        * @return Copia del iterador en la posición anterior
        */
        const_iterator operator++(int);

        /**
        * @brief Comprueba si iteradores apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator==(const const_iterator &otro) const;

        /**
        * @brief Comprueba si iteradores no apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator!=(const const_iterator &otro) const;
        /**
        * @brief Retrasa el iterador hasta la posición anterior (Pre-decremento: --it)
        * @return Refencia al iterador tras el decremento.
        */
        const_iterator& operator--();

        /**
        * @brief Retrasa el iterador hasta la posición anterior (Post-decremento: it--)
        * @param int Indica que se trata de it--.
        * @return Copia del iterador en la posición anterior al decremento.
        */
        const_iterator operator--(int);

        /**
        * @brief Accede al elemento al que referencia el iterador.
        * @return El objeto al que referencia.
        */        
        const data<T,U>& operator*() const;      

    };

    /**
     Busca la clave p en el diccionario.
      p es la clave a buscar. it_out apuntara al elemento con esa clave y en caso
      contrario de que no este la clave it_out apuntara a donde debería estar.
    */
    bool Esta_Clave(const T &p, typename Diccionario<T,U>::iterator &it_out);


    /**
     Inserta un nuevo registro en el diccionario.
     clave clave usada para insertar en el diccionario
     info informacion asociada a la clave que se inserta junto con clave
     el diccionario se supone ordenado, ya que insertar inserta en orden
     */
    void Insertar(const T& clave, const list<U> &info);


    /**
     Añade una nueva informacion asocida a una clave que está en el diccionario.
     La nueva información se inserta al final de la lista de información.
     Si no esta la clave la inserta y añade la informacion asociada.
     */
    void AddSignificado_Palabra(const U & s, const T &p);


    /**
     Devuelve la información (una lista) asociada a una clave p.
     devuelve una lista con la informacion asociada a la clave.
     */

    list<U> getInfo_Asoc(const T & p);

    /**
     Devuelve el tamaño del diccionario
     tamaño del diccionario
     */
    int size()const;


    /**
     borra un data del diccionario por su clave
     c es la clave cuyo elemento queremos borrar. Devuelve
     true si se ha borrado el elemento, false si no
     */
    bool Borrar(const T & c);

    /**
     Union de 2 diccionarios
     Si una clave aparece en ambos diccionarios en el resultante aparece una sola vez con la union
     de las informaciones asociadas.
     */
    Diccionario union_d(const Diccionario & D);

    /**
     elimina las claves del diccionario que aprecen en D
     D diccionario cuyas claves queremos eliminar
     */
    Diccionario diferencia(const Diccionario &D);

    /**
     Interssecion d 2 diccionarios;
     diccionario con el que se interseca
     */
    Diccionario interseccion(const Diccionario & D);


    /**
     Devuelve un diccionario con las claves en el
     * 	intervalo [i,f)

     */

    Diccionario Devolver_rango(const T &i, const T & f);


    /** Funciones begin y end para los iteradores**/

    iterator begin();

    iterator end();

    const_iterator begin();

    const_iterator end();

};

#endif
