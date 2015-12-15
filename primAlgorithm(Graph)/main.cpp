#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "../Clases/Lista/Lista.hpp"
#include "../Clases/Cola/Cola.hpp"
#include "../Clases/Pila/Pila.hpp"
#include "../Clases/Grafo/Grafo.hpp"

void leerGrafo(Grafo<char>&);

int main(){	
	Grafo<string> g;
	string v, w;
	float costo;
	
	//lectura formato arco (a b)
	int vertice1, vertice2;
	while(cin >> v >> w >> costo){
		cin >> vertice2;
		g.agregarArco(vertice1, vertice2);
	}
	g.modIds();

}

void leerGrafo(Grafo<char>&);