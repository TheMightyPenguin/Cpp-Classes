#include <iostream>
using namespace std;

#include "../Clases/Lista/Lista.hpp"
#include "../Clases/Grafo/Grafo.hpp"

//Struct auxiliar para guardar un arco de v a w.
struct arista{
	char v, w;
};

Lista<arista> arbolDFS(Grafo<char>&);
void arbolDFS(Grafo<char>&, char, Lista<arista>&);
void imprimirListaAristas(Lista<arista>&, int);
void leerGrafo(Grafo<char>&);

int main(){
	Grafo<char> g;
	int nCasos;
	Lista<arista> l;
	
	cin >> nCasos;
	for(int i = 0; i < nCasos; i++){
		leerGrafo(g);
		l = arbolDFS(g);
		imprimirListaAristas(l, i+1);
		g.nulo();
	}
	
	return(0);
}


Lista<arista> arbolDFS(Grafo<char> &g){
	Lista<char> l = g.listaVertices();
	Lista<arista> res;
	char v;
	while(!l.esVacia()){
		v = l.consultar(1);
		l.eliminar(1);
		arbolDFS(g, v, res);
	}
	return(res);
}

//Los metodos marcar y obtMarca de la clase Grafo se usan para
//marcar y ver si ya hemos pasado por algun vertice.
void arbolDFS(Grafo<char> &g, char v, Lista<arista> &l){
	Lista<char> sucesores = g.sucesores(v);
	char u;
	arista arco;
	arco.v = v;
	g.marcar(v);
	while(!sucesores.esVacia()){
		u = sucesores.consultar(1);
		sucesores.eliminar(1);
		if(!g.obtMarca(u)){
			arco.w = u;
			l.insertar(arco, l.longitud() + 1); //Insertamos la arista en el arco
			arbolDFS(g, u, l);
		}
	}
}

void imprimirListaAristas(Lista<arista> &l, int n){
	arista arco;
	cout << "Caso #" << n << endl;
	while(!l.esVacia()){
		arco = l.consultar(1);
		l.eliminar(1);
		cout << arco.v << " " << arco.w << endl;
	}
	cout << endl;
}

void leerGrafo(Grafo<char> &g){
	char v, w;
	bool flag = true;
	while(flag && cin >> v){
		cin.get();
		cin >> w;
		if(v == '*' && w == '*'){
			flag = false;
		}else{
			g.agregarArcoNoDirigido(v, w);
		}
	}
}
