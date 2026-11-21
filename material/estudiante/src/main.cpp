#include <iostream>
#include <string>
#include <list>
#include "diccionario.h"
// Como Diccionario es una plantilla, la implementación debe ser visible.
// Si la tienes en diccionario.cpp (o .tpp), descomenta la línea que corresponda:
#include "diccionario.cpp"

using namespace std;

// ---------- Utilidades de impresión ----------

template <class U>
void imprimirLista(const list<U> &l) {
    cout << "[";
    for (typename list<U>::const_iterator it = l.begin(); it != l.end(); ++it) {
        if (it != l.begin()) cout << ", ";
        cout << *it;
    }
    cout << "]";
}

// Imprime usando const_iterator (diccionario const)
template <class T, class U>
void imprimirDic(const string &titulo, const Diccionario<T, U> &D) {
    cout << "--- " << titulo << " (size = " << D.size() << ") ---" << endl;
    for (typename Diccionario<T, U>::const_iterator it = D.begin(); it != D.end(); ++it) {
        cout << "  " << (*it).clave << " -> ";
        imprimirLista((*it).info_asoci);
        cout << endl;
    }
}

void titulo(const string &t) {
    cout << "\n==================== " << t << " ====================" << endl;
}

void check(const string &desc, bool cond) {
    cout << "  [" << (cond ? " OK " : "FAIL") << "] " << desc << endl;
}

int main() {
    typedef Diccionario<string, string> Dic;

    // =====================================================
    titulo("1. Constructor por defecto y size()");
    Dic d1;
    imprimirDic("d1 vacio", d1);
    check("size() == 0 en diccionario vacio", d1.size() == 0);
    check("begin() == end() en diccionario vacio", d1.begin() == d1.end());

    // =====================================================
    titulo("2. Insertar (se inserta desordenado, debe quedar ordenado)");
    list<string> l;

    l.push_back("fruta roja");
    l.push_back("redonda");
    d1.Insertar("manzana", l);

    l.clear();
    l.push_back("fruta amarilla");
    d1.Insertar("platano", l);

    l.clear();
    l.push_back("fruta citrica");
    l.push_back("acida");
    d1.Insertar("limon", l);

    l.clear();
    l.push_back("fruta pequena");
    d1.Insertar("cereza", l);

    imprimirDic("d1 tras 4 inserciones", d1);
    check("size() == 4", d1.size() == 4);

    // Orden de menor a mayor clave
    {
        Dic::iterator it = d1.begin();
        check("primera clave es 'cereza'", (*it).clave == "cereza");
        ++it; ++it; ++it;
        check("ultima clave es 'platano'", (*it).clave == "platano");
    }

    // =====================================================
    titulo("3. Esta_Clave");
    Dic::iterator itE;
    bool esta = d1.Esta_Clave("limon", itE);
    check("Esta_Clave('limon') == true", esta);
    if (esta) {
        cout << "     apunta a: " << (*itE).clave << " -> ";
        imprimirLista((*itE).info_asoci);
        cout << endl;
    }

    esta = d1.Esta_Clave("kiwi", itE);
    check("Esta_Clave('kiwi') == false", !esta);
    if (itE != d1.end())
        cout << "     apunta a donde deberia estar (siguiente clave): " << (*itE).clave << endl;
    else
        cout << "     apunta a end()" << endl;

    esta = d1.Esta_Clave("zanahoria", itE);
    check("Esta_Clave('zanahoria') == false", !esta);
    check("para clave mayor que todas apunta a end()", itE == d1.end());

    // =====================================================
    titulo("4. AddSignificado_Palabra");
    // Clave existente: se anade al final de la lista
    d1.AddSignificado_Palabra("con pepitas", "manzana");
    // Clave inexistente: se inserta la clave con ese significado
    d1.AddSignificado_Palabra("fruta tropical", "pina");
    imprimirDic("d1 tras AddSignificado_Palabra", d1);
    check("size() == 5", d1.size() == 5);
    {
        list<string> m = d1.getInfo_Asoc("manzana");
        check("'manzana' tiene 3 significados", m.size() == 3);
        check("el ultimo significado de 'manzana' es 'con pepitas'", m.back() == "con pepitas");
    }

    // =====================================================
    titulo("5. getInfo_Asoc");
    {
        list<string> info = d1.getInfo_Asoc("limon");
        cout << "  getInfo_Asoc('limon') = ";
        imprimirLista(info);
        cout << endl;
        check("'limon' tiene 2 significados", info.size() == 2);

        list<string> vacia = d1.getInfo_Asoc("inexistente");
        cout << "  getInfo_Asoc('inexistente') = ";
        imprimirLista(vacia);
        cout << endl;
        check("clave inexistente devuelve lista vacia", vacia.empty());
    }

    // =====================================================
    titulo("6. Borrar(const T&)");
    check("Borrar('platano') == true", d1.Borrar("platano"));
    check("Borrar('platano') otra vez == false", !d1.Borrar("platano"));
    check("Borrar('inexistente') == false", !d1.Borrar("inexistente"));
    check("size() == 4", d1.size() == 4);
    imprimirDic("d1 tras borrar", d1);

    // =====================================================
    titulo("7. Constructor de copia");
    Dic d2(d1);
    imprimirDic("d2 (copia de d1)", d2);
    check("d2.size() == d1.size()", d2.size() == d1.size());
    d2.Borrar("cereza");
    check("copia independiente: borrar en d2 no afecta a d1",
          d1.size() == 4 && d2.size() == 3);

    // =====================================================
    titulo("8. Operador de asignacion");
    Dic d3;
    d3.Insertar("basura", list<string>(1, "dato que debe desaparecer"));
    d3 = d1;
    imprimirDic("d3 (d3 = d1)", d3);
    check("d3.size() == d1.size()", d3.size() == d1.size());
    d3.AddSignificado_Palabra("extra", "limon");
    check("asignacion independiente: d1 no cambia",
          d1.getInfo_Asoc("limon").size() == 2 && d3.getInfo_Asoc("limon").size() == 3);

    // Autoasignacion
    d3 = d3;
    check("autoasignacion mantiene el tamano", d3.size() == 4);

    // Asignacion encadenada
    Dic d4, d5;
    d4 = d5 = d1;
    check("asignacion encadenada", d4.size() == d1.size() && d5.size() == d1.size());

    // =====================================================
    titulo("9. Iteradores (iterator)");
    {
        Dic::iterator it = d1.begin();
        cout << "  Recorrido hacia delante: ";
        for (Dic::iterator i = d1.begin(); i != d1.end(); ++i)
            cout << (*i).clave << " ";
        cout << endl;

        cout << "  Recorrido hacia atras:   ";
        Dic::iterator fin = d1.end();
        while (fin != d1.begin()) {
            --fin;
            cout << (*fin).clave << " ";
        }
        cout << endl;

        // Pre y post incremento
        Dic::iterator a = d1.begin();
        Dic::iterator b = a++;
        check("post-incremento devuelve copia anterior", (*b).clave == "cereza");
        check("post-incremento avanza el iterador", (*a).clave == "limon");

        Dic::iterator c = ++a;
        check("pre-incremento devuelve el iterador avanzado", (*c).clave == "manzana");
        check("pre-incremento avanza el iterador", (*a).clave == "manzana");

        // Pre y post decremento
        Dic::iterator e = a--;
        check("post-decremento devuelve copia anterior", (*e).clave == "manzana");
        check("post-decremento retrocede el iterador", (*a).clave == "limon");

        Dic::iterator f = --a;
        check("pre-decremento devuelve el iterador retrocedido", (*f).clave == "cereza");
        check("pre-decremento retrocede el iterador", (*a).clave == "cereza");

        // == y !=
        check("it == begin()", it == d1.begin());
        check("it != end()", it != d1.end());
        check("a == b (ambos en 'cereza')", a == b);

        // Constructor por defecto y parametrizado
        Dic::iterator def;
        (void)def;
        Dic::iterator copia(it);
        check("iterador copiado es igual al original", copia == it);

        // Modificacion a traves del iterador (operator* devuelve referencia no const)
        (*it).info_asoci.push_back("modificada via iterator");
        check("modificar via iterator funciona",
              d1.getInfo_Asoc("cereza").back() == "modificada via iterator");
    }

    // =====================================================
    titulo("10. Iteradores (const_iterator)");
    {
        const Dic &cd = d1;
        cout << "  Recorrido hacia delante: ";
        for (Dic::const_iterator i = cd.begin(); i != cd.end(); ++i)
            cout << (*i).clave << " ";
        cout << endl;

        cout << "  Recorrido hacia atras:   ";
        Dic::const_iterator fin = cd.end();
        while (fin != cd.begin()) {
            --fin;
            cout << (*fin).clave << " ";
        }
        cout << endl;

        Dic::const_iterator a = cd.begin();
        Dic::const_iterator b = a++;
        check("const: post-incremento devuelve copia anterior", (*b).clave == "cereza");
        check("const: post-incremento avanza", (*a).clave == "limon");

        Dic::const_iterator c = ++a;
        check("const: pre-incremento", (*c).clave == "manzana" && (*a).clave == "manzana");

        Dic::const_iterator e = a--;
        check("const: post-decremento devuelve copia anterior", (*e).clave == "manzana");
        check("const: post-decremento retrocede", (*a).clave == "limon");

        Dic::const_iterator f = --a;
        check("const: pre-decremento", (*f).clave == "cereza" && (*a).clave == "cereza");

        check("const: == y !=", (a == cd.begin()) && (a != cd.end()));

        Dic::const_iterator def;
        (void)def;
    }

    // =====================================================
    titulo("11. union_d");
    Dic A, B;
    A.Insertar("a", list<string>(1, "A-a1"));
    A.Insertar("b", list<string>(1, "A-b1"));
    A.Insertar("c", list<string>(1, "A-c1"));

    B.Insertar("b", list<string>(1, "B-b1"));
    B.Insertar("c", list<string>(1, "B-c1"));
    B.Insertar("d", list<string>(1, "B-d1"));

    imprimirDic("A", A);
    imprimirDic("B", B);

    Dic U = A.union_d(B);
    imprimirDic("A.union_d(B)", U);
    check("union tiene 4 claves (a,b,c,d)", U.size() == 4);
    check("clave comun 'b' tiene la union de informaciones (2 elementos)",
          U.getInfo_Asoc("b").size() == 2);
    check("clave comun 'c' tiene la union de informaciones (2 elementos)",
          U.getInfo_Asoc("c").size() == 2);
    check("clave solo en A ('a') se conserva", U.getInfo_Asoc("a").size() == 1);
    check("clave solo en B ('d') se conserva", U.getInfo_Asoc("d").size() == 1);

    // Union con vacio
    Dic vacio;
    check("A union vacio == size de A", A.union_d(vacio).size() == A.size());
    check("vacio union A == size de A", vacio.union_d(A).size() == A.size());

    // =====================================================
    titulo("12. diferencia");
    Dic Dif = A.diferencia(B);
    imprimirDic("A.diferencia(B) (claves de A que no estan en B)", Dif);
    check("diferencia tiene 1 clave ('a')", Dif.size() == 1);
    check("la clave restante es 'a'", Dif.begin() != Dif.end() && (*Dif.begin()).clave == "a");

    Dic Dif2 = A.diferencia(vacio);
    check("A - vacio == A (mismo tamano)", Dif2.size() == A.size());
    Dic Dif3 = A.diferencia(A);
    check("A - A == vacio", Dif3.size() == 0);

    // =====================================================
    titulo("13. interseccion");
    Dic Inter = A.interseccion(B);
    imprimirDic("A.interseccion(B)", Inter);
    check("interseccion tiene 2 claves (b,c)", Inter.size() == 2);
    check("contiene 'b'", Inter.getInfo_Asoc("b").size() > 0);
    check("contiene 'c'", Inter.getInfo_Asoc("c").size() > 0);
    check("no contiene 'a'", Inter.getInfo_Asoc("a").empty());
    check("no contiene 'd'", Inter.getInfo_Asoc("d").empty());

    check("A interseccion vacio == vacio", A.interseccion(vacio).size() == 0);

    // =====================================================
    titulo("14. Devolver_rango (intervalo [i,f))");
    Dic R;
    const char *claves[] = {"a", "b", "c", "d", "e", "f"};
    for (int i = 0; i < 6; ++i)
        R.Insertar(claves[i], list<string>(1, string("info-") + claves[i]));
    imprimirDic("R", R);

    // Con iterator
    {
        Dic::iterator i = R.begin();
        ++i;                          // 'b'
        Dic::iterator f = i;
        ++f; ++f; ++f;                // 'e' (excluido)
        Dic rango = R.Devolver_rango(i, f);
        imprimirDic("R.Devolver_rango(b, e) con iterator", rango);
        check("rango [b,e) tiene 3 claves (b,c,d)", rango.size() == 3);
        check("'e' no esta incluido (intervalo abierto por la derecha)",
              rango.getInfo_Asoc("e").empty());
    }

    // Con const_iterator
    {
        const Dic &cR = R;
        Dic::const_iterator i = cR.begin();
        Dic::const_iterator f = cR.end();
        Dic completo = cR.Devolver_rango(i, f);
        imprimirDic("R.Devolver_rango(begin, end) con const_iterator", completo);
        check("rango completo == R", completo.size() == R.size());

        Dic::const_iterator j = cR.begin();
        Dic vacioRango = cR.Devolver_rango(j, j);
        check("rango [i,i) esta vacio", vacioRango.size() == 0);
    }

    // =====================================================
    titulo("15. Otro tipo de clave (int, int)");
    {
        Diccionario<int, int> di;
        di.Insertar(30, list<int>(1, 300));
        di.Insertar(10, list<int>(1, 100));
        di.Insertar(20, list<int>(1, 200));
        di.AddSignificado_Palabra(101, 10);
        imprimirDic("di (int,int)", di);
        check("orden ascendente de claves enteras", (*di.begin()).clave == 10);
        check("size() == 3", di.size() == 3);
        check("Borrar(20)", di.Borrar(20) && di.size() == 2);
    }

    // =====================================================
    titulo("16. Operador < de data (comparador)");
    {
        data<string, string> x, y;
        x.clave = "aaa";
        y.clave = "bbb";
        check("x < y (aaa < bbb)", x < y);
        check("!(y < x)", !(y < x));
        check("!(x < x)", !(x < x));
    }

    // =====================================================
    titulo("17. Destructor");
    {
        Dic *p = new Dic();
        p->Insertar("temp", list<string>(1, "temporal"));
        delete p;   // Ejecuta ~Diccionario() (Borrar() privado internamente)
        cout << "  Dic dinamico creado y destruido sin errores" << endl;
    }

    cout << "\nFin de las pruebas." << endl;
    return 0;
}