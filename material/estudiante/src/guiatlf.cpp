#include <map>
#include <iostream>
#include <string>
using namespace std;

string & Guia_Tlf::operator[](const string &nombre);

string  gettelefono(const string & nombre);

pair<map<string,string>::iterator,bool>  insert(string nombre, string tlf);

pair<map<string,string>::iterator,bool>  insert(pair<string,string> p);

void borrar(const string &nombre);

void borrar(const string &nombre,const string &tlf);

Guia_Tlf operator+(const Guia_Tlf & g);

Guia_Tlf operator-(const Guia_Tlf & g);

Guia_Tlf previos(const string &nombre,const string &tlf);

Guia_Tlf inter(const Guia_Tlf & g);

void modi(const string &nombre, const string &newtlf);

Guia_Tlf filtro(const string & c);

ostream & operator<<(ostream & os, Guia_Tlf & g);

istream & operator>>(istream & is, Guia_Tlf & g);





