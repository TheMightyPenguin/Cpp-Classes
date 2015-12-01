#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "../Clases/Lista/Lista.hpp"
#include "../Clases/Cola/Cola.hpp"
#include "../Clases/Pila/Pila.hpp"
#include "../Clases/Grafo/Grafo.hpp"

Lista<int> ordenamientoTopologico(Grafo<int>);
Lista<char> ordenamientoTopologico(Grafo<char>);

int main(){	
	Grafo<string> g, g2;
	float costo;

	//lectura formato arco (a b)
	string vertice1, vertice2;
	while(cin >> vertice1){
		cin.get();
		cin >> vertice2;
		cin >> costo;
		g.agregarArco(vertice1, vertice2, costo);
	}
	g.agregarVertice("ciudad3");
	g.modIds();

	if(g.esVacio()) cout << "Grafo 1 vacio" << endl;
	else cout << "Grafo 1 no vacio" << endl;
	cout << "grafo 1:\n" << g << endl;
	
	cout << endl;
	// if(g2.esVacio()) cout << "Grafo 2 vacio" << endl;
	// else cout << "Grafo 2 no vacio" << endl;
	// cout << "grafo 2: " << g2 << endl;
	
	// if(g == g2) cout << "grafo 1 y grafo 2 son iguales\n" << endl;
	// else cout << "grafo 1 y grafo 2 son distintos\n" << endl;
	cout << "Lista de vertices del grafo 1" << endl << g.listaVertices() << endl << endl;
	cout << "Lista de fuentes del grafo 1:" << endl << g.fuentes() << endl << endl;
	cout << "Lista de vertices sumideros del grafo 1:" << endl << g.sumideros() << endl << endl;
	cout << "numero de vertices del grafo: " << g.orden() << endl;
	
	string v;
	Lista<string> l = g.listaVertices();
	while(!l.esVacia()){
		v = l.consultar(1);
		l.eliminar(1);
		cout << "--------VERTICE " << v << "---------------------" << endl;
		cout << "Lista de sucesores del vertice:" << v << endl << g.sucesores(v) << endl;
		cout << "Lista de predecesores del vertice:" << v << endl << g.predecesores(v) << endl << endl;
		cout << "Vecindad del vertice:" << v << endl << g.vecindad(v) << endl << endl;
		cout << "Grado interior del vertice:" << v << endl << g.gradoInterior(v) << endl;
		cout << "Grado exterior del vertice:" << v << endl << g.gradoExterior(v) << endl;
		cout << "Grado del vertice:" << v << endl << g.grado(v) << endl;
		if(g.esSumidero(v)) cout << "El vertice " << v << " es sumidero" << endl;
		else cout << "El vertice " << v << " no es sumidero" << endl;
		if(g.esFuente(v)) cout << "El vertice " << v << " es fuente" << endl;
		else cout << "El vertice " << v << " no es fuente" << endl;
		if(g.estaAislado(v)) cout << "El vertice " << v << " esta aislado" << endl;
		else cout << "El vertice " << v << " no esta aislado" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	}
	
	v = "ciudad1";
	string w = "ciudad4";
	
	if(g.existeVertice(v)) cout << "El vertice " << v << " esta en el arco" << endl;
	else cout << "El vertice " << v << " no esta en el arco" << endl;
	
	if(g.existeArco(v, w)) cout << "El arco (" << v << ", " << w << ") esta en el arco" << endl;
	else cout << "El arco (" << v << ", " << w << ") no esta en el arco" << endl;
	
	if(g.existeArco(w, v)) cout << "El arco (" << w << ", " << v << ") esta en el arco" << endl;
	else cout << "El arco (" << w << ", " << v << ") no esta en el arco" << endl;
	
	cout << "Costo del arco (" << v << ", " << w << ") = " << g.costoArco(v, w) << "\n" << endl;
	
	if(g.adyacentes(v, w)) cout << "Existe adyacencia entre " << v << " y " << w << endl;
	else cout << "No existe adyacencia entre " << v << " y " << w << endl;
	
	if(g.adyacentes(w, v)) cout << "Existe adyacencia entre " << w << " y " << v << endl;
	else cout << "No existe adyacencia entre " << w << " y " << v << "\n" << endl;
	
	if(g.esHamiltoniano()) cout << "El grafo es hamiltoniano" << endl;
	else cout << "El grafo no es hamiltoniano" << endl;

	if(g.esEuleriano()) cout << "El grafo es euleriano" << endl;
	else cout << "El grafo no es euleriano" << endl;

	cout << "Camino mas corto entre " << v << " y " << w;
	cout << "(Grafo 1):\n" << g.camino(v, w) << endl << endl;
	// cout << "Camino mas corto entre " << v << " y " << w << "(Grafo 2):\n" << g2.camino(v, w) << endl;
	//~ Lista<int> caca = ordenamientoTopologico(g);
	//~ cout << "Ordenamiento Topologico del grafo: \n" << caca << endl;
	
	string x = "ciudad1";
	cout << "\n---RECORRIDO BFS (Vi=" << x << ")----------" << endl;
	g.BFS(x);
	cout << "\n\n";
	cout << "---RECORRIDO DFS----------" << endl;
	g.DFS();
	return(0);
}

Lista<int> ordenamientoTopologico(Grafo<int> g){
	Lista<int> res, fuentes, sucesores;
	int v, u;
	fuentes = g.fuentes();
	while(!fuentes.esVacia()){
		u = fuentes.consultar(1);
		fuentes.eliminar(1);
		res.insertar(u, res.longitud() + 1);
		sucesores = g.sucesores(u);
		g.eliminarVertice(u);
		while(!sucesores.esVacia()){
			v = sucesores.consultar(1);
			sucesores.eliminar(1);
			if(g.gradoInterior(v) == 0){
				fuentes.insertar(v, fuentes.longitud() + 1);
			}
		}
	}
	return(res);
}

Lista<char> ordenamientoTopologico(Grafo<char> g){
	Lista<char> res, fuentes, sucesores;
	char v, u;
	fuentes = g.fuentes();
	while(!fuentes.esVacia()){
		u = fuentes.consultar(1);
		fuentes.eliminar(1);
		res.insertar(u, res.longitud() + 1);
		sucesores = g.sucesores(u);
		g.eliminarVertice(u);
		while(!sucesores.esVacia()){
			v = sucesores.consultar(1);
			sucesores.eliminar(1);
			if(g.gradoInterior(v) == 0){
				fuentes.insertar(v, fuentes.longitud() + 1);
			}
		}
	}
	return(res);
}
