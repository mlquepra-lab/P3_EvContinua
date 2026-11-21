#include "../include/guiatlf.h"

#include <map>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

string & Guia_Tlf::operator[](const string &nombre){
    return datos[nombre];
}

string  Guia_Tlf::gettelefono(const string & nombre){
    Guia_Tlf::iterator it = datos.find(nombre);

    if (it != datos.end()){
        return it->second;
    }

    return "";
}

pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(string nombre, string tlf){
    pair<string,string> insertado;

    insertado.first = nombre;
    insertado.second = tlf;

    return datos.insert(insertado);
}

pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(pair<string,string> p){
    return datos.insert(p);
}

void Guia_Tlf::borrar(const string &nombre){
    datos.erase(nombre);
}

void Guia_Tlf::borrar(const string &nombre,const string &tlf){
    Guia_Tlf::iterator it = datos.find(nombre);

    if(it != datos.end() && it->second == tlf) {
        datos.erase(it.getIterator());
    }
}

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

void Guia_Tlf::modi(const string &nombre, const string &newtlf){
    datos[nombre] = newtlf;
}

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
ostream& operator<<(ostream& os, const Guia_Tlf& g) {
    Guia_Tlf::const_iterator it;

    for(it = g.begin(); it != g.end(); ++it) {
        os << (*it).first << " : " << (*it).second << endl;
    }

    return os;
}

istream& operator>>(istream& is, Guia_Tlf& g) {
    string nombre, telefono;

    is >> nombre >> telefono;

    pair<string, string> dato;
    dato.first=nombre;
    dato.second=telefono;

    g.insert(dato);

    return is;
}

