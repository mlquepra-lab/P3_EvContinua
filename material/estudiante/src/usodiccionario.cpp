/**
 * @file usodiccionario.cpp
 * @brief Programa de ejemplo de uso de Diccionario<string,string>.
 *
 * @details Lee dos diccionarios de la entrada estándar y escribe su unión,
 * su diferencia y su intersección. Después lee dos claves y muestra las claves
 * del primer diccionario que quedan en el rango entre ambas.
 *
 * Uso con un fichero de ejemplo (por ejemplo, data/data.txt):
 * <tt>./usodiccionario &lt; data.txt</tt>
 */

#include "diccionario.h"
#include "diccionario.cpp"  
#include <iostream>
using namespace std;
/**
 * @brief Escribe un diccionario en un flujo de salida.
 * @param os Flujo de salida (es modificado).
 * @param D Diccionario que se escribe.
 * @return El flujo @p os, para poder encadenar el operador.
 *
 * @details Se usan dos tipos de iteradores: un const_iterator sobre el
 * diccionario (una lista de registros) y un @c list<string>::const_iterator
 * sobre la información asociada de cada clave (una lista de cadenas). Para
 * cada clave escribe la clave, el texto <tt>informacion asociada:</tt>, cada
 * elemento de la información en su propia línea y una línea de asteriscos.
 */
ostream &operator<<(ostream &os, const Diccionario<string, string> &D) {

  Diccionario<string, string>::const_iterator it;

  for (it = D.begin(); it != D.end(); ++it) {

    list<string>::const_iterator it_s;

    os << endl << (*it).clave << endl << " informacion asociada:" << endl;
    for (it_s = (*it).info_asoci.begin(); it_s != (*it).info_asoci.end();
         ++it_s) {
      os << (*it_s) << endl;
    }
    os << "**************************************" << endl;
  }

  return os;
}

/**
 * @brief Lee un diccionario desde un flujo de entrada.
 * @param is Flujo de entrada (es modificado).
 * @param D Diccionario que se rellena; su contenido anterior se pierde.
 * @return El flujo @p is, para poder encadenar el operador.
 *
 * @details El formato de la entrada es:
 *  - número de claves en la primera línea;
 *  - para cada clave: la clave (línea completa), el número de informaciones
 *    asociadas en la línea siguiente y después una línea por cada información.
 *
 * Se lee primero en un diccionario auxiliar y al final se asigna a @p D.
 *
 * @pre El flujo respeta el formato descrito.
 */

istream &operator>>(istream &is, Diccionario<string, string> &D) {
  int np;
  is >> np;
  is.ignore(); // quitamos \n
  Diccionario<string, string> Daux;
  for (int i = 0; i < np; i++) {
    string clave;

    getline(is, clave);

    int ns;
    is >> ns;
    is.ignore(); // quitamos \n
    list<string> laux;
    for (int j = 0; j < ns; j++) {
      string s;
      getline(is, s);

      // cout<<"Significado leido "<<s<<endl;
      laux.insert(laux.end(), s);
    }
    Daux.Insertar(clave, laux);
  }
  D = Daux;
  return is;
}

/**
 * @brief Escribe por la salida estándar la información asociada a una clave.
 * @param l Lista de informaciones (significados) de la clave.
 *
 * @post Cada elemento de @p l se escribe en una línea distinta.
 */
void EscribeSigni(const list<string> &l) {
  list<string>::const_iterator it_s;

  for (it_s = l.begin(); it_s != l.end(); ++it_s) {
    cout << *it_s << endl;
  }
}

/**
 * @brief Función principal: lee dos diccionarios y muestra las operaciones
 * entre ellos.
 * @return Sin valor de retorno explícito (equivale a 0 en @c main).
 *
 * @details Lee D1 y D2 de la entrada estándar y escribe D1, D2, su unión
 * (Diccionario::union_d), su diferencia D1-D2 (Diccionario::diferencia) y su
 * intersección (Diccionario::interseccion). A continuación lee dos claves y
 * escribe las claves de D1 que están en el intervalo entre ambas
 * (Diccionario::Devolver_rango).
 *
 * @note Hay un fichero de ejemplo, data.txt. Para ejecutar el programa con él:
 * <tt>./usodiccionario &lt; data.txt</tt>
 */
int main() {
  Diccionario<string, string> D1;
  Diccionario<string, string> D2;
  Diccionario<string, string> Union;
  Diccionario<string, string> Diferencia;
  Diccionario<string, string> Interseccion;
  Diccionario<string, string> Rango;
  string clave_1;
  string clave_2;
  Diccionario<string, string>::iterator it;

  cin >> D1;
  cout << D1;
  cin >> D2;
  cout << D2;

  Union = D1.union_d(D2);

  cout << "La union de D1 y D2 es: " << endl;
  cout << Union;

  Diferencia = D1.diferencia(D2);

  cout << "La diferencia D1-D2 es: " << endl;
  cout << Diferencia;

  Interseccion = D1.interseccion(D2);

  cout << "La interseccion D1 y D2 es: " << endl;
  cout << Interseccion;

  // cout << "Introduzca la primera clave del rango a buscar en el diccionario
  // 1: ";
  cin >> clave_1;

  // cout << "Introduzca la ultima clave del rango a buscar en el diccionario 1:
  // ";
  cin >> clave_2;

  Rango = D1.Devolver_rango(clave_1, clave_2);

  cout << "Las claves en ese rango son: " << endl;

  for (it = Rango.begin(); it != Rango.end(); ++it)
    cout << (*it).clave << endl;

  /*string a;

  cout<<"Introduce una palabra"<<endl;
  cin>>a;

  list<string>l=D.getInfo_Asoc(a);

  if (l.size()>0)
          EscribeSigni(l);
  */
}
