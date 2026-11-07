



template <class T, class U>
void Diccionario<T, U>::Copiar(const Diccionario<T, U>& D) {
    datos.clear();
    const_iterator it_o = D.begin();
    const_iterator it_f = D.end();
    for(; it_o != it_f; it_o++){
        datos.push_back(*it_o);
    }
}

template <class T, class U>
void Diccionario<T, U>::Borrar() {
    datos.clear();
}

template <class T, class U>
Diccionario<T, U>::Diccionario() {}

template <class T, class U>
Diccionario<T, U>::Diccionario(const Diccionario<T, U> &D) {
    Copiar(D);
}

template <class T, class U>
Diccionario<T, U>::~Diccionario() {
    Borrar();
}

template <class T, class U>
Diccionario<T, U> & Diccionario<T, U>::operator=(const Diccionario<T, U> &D) {
    if (this != &D)
        Copiar(D);
    return *this;
}


///////////////////////////////////////////////////////// CLASS ITERATOR
template <class T, class U>
Diccionario<T, U>::iterator::iterator ();

///////////////////////////////////////////////////////// CLASS CONST_ITERATOR