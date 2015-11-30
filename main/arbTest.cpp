#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "../Clases/Lista/Lista.hpp"
#include "../Clases/Cola/Cola.hpp"
#include "../Clases/Pila/Pila.hpp"
#include "../Clases/Arbol_Binario/ArBin.hpp"
#include "../Clases/ArbolN/ArbolN.hpp"

int main(){
	ArBin<string> arbol;
	ArbolN<int> arb;
	Lista<string> a, b;
	
	a.insertar("Assets", a.longitud()+1);
	a.insertar("Scenes", a.longitud()+1);
	a.insertar("Scripts", a.longitud()+1);
	a.insertar("3DModels", a.longitud()+1);
	
	
	b.insertar("Scripts", b.longitud()+1);
	b.insertar("Scenes", b.longitud()+1);
	b.insertar("Assets", b.longitud()+1);
	b.insertar("3DModels", b.longitud()+1);
	arbol.cargaPreIn(a, b);
	
	cout << "Lista a:" << a << endl;
	cout << "Arbol:\n" << arbol << endl;
	
	
	return(0);
}
