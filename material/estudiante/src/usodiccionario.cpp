#include <iostream>
#include "diccionario.h"



/*Operator<<. Obsérvese el uso de 2 tipos diferentes de iteradores. Uno sobre 
listas de listas y otro sobre listas
*/
ostream & operator<<(ostream & os, const Diccionario<string,string> & D){
	  
	  Diccionario<string,string>::const_iterator it;
	  
	  for (it=D.cbegin(); it!=D.cend(); ++it){
	  
		    list<string>::const_iterator it_s;
		    
		    os<<endl<<(*it).clave<<endl<<" informacion asociada:"<<endl;
		    for (it_s=(*it).info_asoci.begin();it_s!=(*it).info_asoci.end();++it_s){
			      os<<(*it_s)<<endl;
		    }
		    os<<"**************************************"<<endl;
	  }
	  
	  return os;
}

/*Operator >>. El formato de la entrada es:
     numero de claves en la primera linea
     clave-iésima retorno de carro
     numero de informaciones asociadas en la siguiente linea
     y en cada linea obviamente la informacion asociada
*/

istream & operator >>(istream & is,Diccionario<string,string> &D){
          typename list<data<string, string> >::iterator useless;
	  int np;
	  is>>np;
	  is.ignore();//quitamos \n
	  Diccionario<string,string> Daux;
	  for (int i=0;i<np; i++){
		    string clave;

		    getline(is,clave); 
		    
		    int ns;
		    is>>ns; 
		    is.ignore();//quitamos \n
		    list<string>laux;
		    for (int j=0;j<ns; j++){
			      string s;
			      getline(is,s);
			      
			      // cout<<"Significado leido "<<s<<endl;
			      laux.insert(laux.end(),s);
		    }
		    Daux.Insertar(clave,laux,useless);		      
		    
	  }
	  D=Daux;
	  return is;
}

/*Recorre la lista de información asociada a una clave y la imprime*/
void EscribeSigni(const list<string>&l){		 
	  list<string>::const_iterator it_s;
	  
	  for (it_s=l.begin();it_s!=l.end();++it_s){
		    cout<<*it_s<<endl;
	  }
}	


/*Lee un diccioario e imprime datos asociados a una clave. 
Hay un fichero ejemplo de prueba: data.txt.Para lanzar el programa con ese fichero se escribe: 
                  ./usodiccionario < data.txt 
*/
int main(){
	Diccionario<string,string> D1;
	Diccionario<string,string> D2;
	Diccionario<string,string> Union;
	Diccionario<string,string> Diferencia;
	Diccionario<string,string> Interseccion;
	Diccionario<string,string> Rango;
	string clave_1;
	string clave_2;
	Diccionario<string,string>::iterator it;

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
	
	//cout << "Introduzca la primera clave del rango a buscar en el diccionario 1: ";
	cin >> clave_1;
	
	//cout << "Introduzca la ultima clave del rango a buscar en el diccionario 1: ";
	cin >> clave_2;
	
	Rango = D1.Devolver_rango(clave_1,clave_2);

	cout << "Las claves en ese rango son: " << endl;
	
	for(it = Rango.begin(); it!= Rango.end(); ++it)
		cout << (*it).clave << endl;
	
	/*string a;

	cout<<"Introduce una palabra"<<endl;
	cin>>a;

	list<string>l=D.getInfo_Asoc(a);

	if (l.size()>0)
		EscribeSigni(l);
	*/
}
