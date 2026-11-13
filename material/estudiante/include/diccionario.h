#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>

/*Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
no se repite (DNI p.ej.) y list<U> es una lista de datos (string p.ej) asociados a la clave
de tipo T. El diccionario está ordenado de menor a mayor clave.
 */
template <class T, class U>
struct data {
    T clave;
    std::list<U> info_asoci;
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

    std::list<data<T, U> > datos;

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

        typename std::list<data<T, U>>::iterator it;

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
        * @brief Destructor.
        */
        ~iterator(){}

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

        /**
        * @brief Comprueba si iteradores no apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator!=(const iterator &otro) const;

        /**
        * @brief Comprueba si iteradores apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator==(const iterator &otro) const;

        friend class Diccionario <T ,U>;

    };
    class const_iterator{
        private:

        typename std::list<data<T, U>>::const_iterator it_const;

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
        * @brief Destructor
        */
        ~const_iterator(){}

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

        /**
        * @brief Comprueba si iteradores no apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator!=(const const_iterator &otro) const;

        /**
        * @brief Comprueba si iteradores apuntan al mismo elemento.
        * @return Variable booleana con la comparación.
        */
        bool operator==(const const_iterator &otro) const;

        friend class Diccionario <T ,U>;

    };

    /**
    * @brief Busca la clave p en el diccionario.
    * @param p Indica la clave a buscar.
    * @param it_out Apuntará al elemento con esa clave.
    * Si no existe apuntará a donde debería estar.
    */
    bool Esta_Clave(const T &p, typename Diccionario<T,U>::iterator &it_out);

    /**
    * @brief Inserta un nuevo registro en el diccionario.
    * @param clave Clave usada para insertar en el diccionario.
    * @param info Información asociada a la clave que se inserta junto con clave.
    */
    void Insertar(const T& clave, const std::list<U> &info);

    /**
    * @brief Añade una nueva informacion asocida a una clave que está en el diccionario.
    * La nueva información se inserta al final de la lista de información.
    * Si no esta la clave la inserta y añade la informacion asociada.
    * @param p Clave del diccionario.
    * @param s Significado de la palabra.
    */
    void AddSignificado_Palabra(const U & s, const T &p);

    /**
    * @brief Devuelve la información (una lista) asociada a una clave p.
    * @return Devuelve una lista con la informacion asociada a la clave.
    */
    std::list<U> getInfo_Asoc(const T & p);

    /**
    * @brief Devuelve el tamaño del diccionario.
    * @return Tamaño del diccionario.
    */
    int size()const;

    /**
    * @brief Borra un data del diccionario por su clave.
    * @param c Es la clave cuyo elemento queremos borrar.
    * @return Devuelve true si se ha borrado el elemento, false si no.
    */
    bool Borrar(const T & c);

    /**
    * @brief Une dos diccionarios.
    * Si una clave aparece en ambos diccionarios en el resultante 
    * aparece una sola vez con la union de las informaciones asociadas.
    * @param D Diccionario con el que se une.
    * @return Unión de 2 diccionarios.
    */
    Diccionario<T,U> union_d(const Diccionario<T,U> & D);

    /**
    * @brief Elimina las claves del diccionario que aparecen en D.
    * @param D Diccionario con el que se une.
    * @return D diccionario cuyas claves queremos eliminar.
    */
    Diccionario<T,U> diferencia(const Diccionario<T,U> &D);

    /**
    * @brief Intersecion d 2 diccionarios.
    * @param D Diccionario con el que se une.
    * @return Diccionario con el que se interseca.
    */
    Diccionario<T,U> interseccion(const Diccionario<T,U> & D);

    /**
    * @brief Devuelve un diccionario con las claves en el
    * intervalo [i,f) 
    * @param i Comienzo del intervalo. Es un iterador.
    * @param f Final del intervalo. Es un iterador.
    * @return Diccionario con las claves.
    */
    template <typename I>
    Diccionario<T,U> Devolver_rango(const I &i, const I &f) const;

    /** Funciones begin y end para los iteradores**/

    /**
    * @brief Devuelve iterador al principio.
    * @return iterador al principio.
    */
    iterator begin();

    /**
    * @brief Devuelve iterador al final.
    * @return iterador al final.
    */
    iterator end();

    /**
    * @brief Devuelve iterador al principio.
    * @return iterador al principio.
    */
    const_iterator begin() const;

    /**
    * @brief Devuelve iterador al final.
    * @return iterador al final.
    */
    const_iterator end() const;
};


#endif
