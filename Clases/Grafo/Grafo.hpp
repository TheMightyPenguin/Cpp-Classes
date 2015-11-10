#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>
#include "../NodoV/NodoV.hpp"
#include "../NodoA/NodoA.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

template <class T, class C = float>
class Grafo{
protected:
	NodoV<T,C> *g, *fin; //g es un apuntador al primer vertice, y fin al ultimo.
	int vertices, arcos; //numero de vertices y numero de arcos.

protected:
	//Metodos Auxiliares
	NodoV<T,C>* agregarAlFinal(const T&);
	void eliminarTodosArcos(NodoV<T,C>*);
	void eliminarArcoDe(const T&, NodoV<T,C>*);
	void ubicarAmbos(const T&, const T&, NodoV<T,C>*&, NodoV<T,C>*&);
	NodoV<T,C>* ubicar(const T&) const;
	NodoA<T,C>* ubicar(NodoA<T,C> *actW, const T &w) const;
	void copiarVertices(const Grafo<T,C>&);
	void copiarArcos(const Grafo<T,C>&);
	T distanciaMin(Lista<T>&, int*) const;
	
public:
	//Constructores
	inline Grafo(): g(0), fin(0), vertices(0), arcos(0) {}
	inline Grafo(const Grafo<T,C> &g2): g(0), fin(0){ *this = g2; }
	
	//Observadores
	inline bool esVacio() const{ return(!g); }
	inline int orden() const{ return(vertices); }
	inline int nArcos() const{ return(arcos); }
	bool existeVertice(const T&) const;
	bool existeArco(const T&, const T&) const;
	C costoArco(const T&, const T&) const;
	bool esFuente(const T&) const;
	bool esSumidero(const T&) const;
	bool estaAislado(const T&) const;
	void mostrar(std::ostream&) const;
	inline void mostrar() const;
	inline T obtUltimo() const{ return(this->fin ? this->fin->obtInfo() : T()); }
	int gradoInterior(const T&) const;
	int gradoExterior(const T&) const;
	int grado(const T&) const;
	bool adyacentes(const T&, const T&);
	Lista<T> listaVertices() const;
	Lista<T> sucesores(const T&) const;
	Lista<T> predecesores(const T&) const;
	Lista<T> fuentes() const;
	Lista<T> sumideros() const;
	Lista<T> vecindad(const T&) const;
	Lista<T> camino(const T&, const T&) const;
	bool igual(const Grafo<T,C>&) const;
	bool obtMarca(const T&) const;
	void BFS(const T&, T*, T*);
	void BFS(const T&);	
	void DFS();
	void DFS(const T, T*, T*, T*, std::string*, int&);
	bool esArborescencia();
	
	//Modificadores
	void agregarVertice(const T&);
	void agregarArco(const T&, const T&, const C& = 0);
	void eliminarArco(const T&, const T&);
	void eliminarVertice(const T&);
	void nulo();
	void marcar(const T&);
	void desmarcar(const T&);
	void copiar(const Grafo<T,C>&);
	
	//Operadores
	Grafo<T,C>& operator = (const Grafo<T,C>&);
	bool operator == (const Grafo<T,C>&);
	
	template <class t, class c>
	friend std::ostream& operator << (std::ostream&, const Lista<t>&);
	
	//Destructor
	~Grafo();
};


/***Constructores*/

/***Fin de Constructores*/


/**Observadores**/
template <class T, class C>
bool Grafo<T,C>::existeVertice(const T &v) const{
	NodoV<T,C> *actV;
	actV = this->ubicar(v);
	return(actV ? true : false);
}

template <class T, class C>
bool Grafo<T,C>::existeArco(const T &v, const T &w) const{
	NodoV<T,C> *actV;
	NodoA<T,C> *actW;
	actV = this->ubicar(v);
	if(actV){
		actW = this->ubicar(actV->obtPri(), w);
		return(actW ? true : false);
	}else{
		return(false);
	}
}

template <class T, class C>
C Grafo<T,C>::costoArco(const T &v, const T &w) const{
	NodoV<T,C> *actV;
	NodoA<T,C> *actW;
	actV = this->ubicar(v);
	if(actV){
		actW = this->ubicar(actV->obtPri(), w);
		return(actW ? actW->obtCosto() : C());
	}else{
		return(C());
	}
}

template <class T, class C>
bool Grafo<T,C>::esFuente(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				return(false);
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(true);
}

template <class T, class C>
bool Grafo<T,C>::esSumidero(const T &v) const{
	NodoV<T,C> *actV;
	actV = this->ubicar(v);
	return(actV ? (actV->obtPri() ? false : true) : false);
}

template <class T, class C>
bool Grafo<T,C>::estaAislado(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	while(actV){
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				if(actA->obtVert()->obtInfo() != v){
					return(false);
				}
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					return(false);
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(true);
}

template <class T, class C>
void Grafo<T,C>::mostrar(std::ostream &o) const{
	NodoV<T,C> *act = this->g;
	NodoA<T,C> *aux;
	Cola< NodoA<T,C>* > c1, c2;
	C costoAux;
	bool flag = false;
	std::cout << std::setfill(' ');	//setting fill character for output stream.
	while(act){
		std::cout << act->obtInfo() << " ----> ";
		c1.encolar(act->obtPri());
		if(!flag)
			flag = act->obtPri() ? true : false;
		act = act->obtSig();
	}
	std::cout << std::endl;
	while(flag){
		flag = false;
		while(!c1.esVacia()){
			aux = c1.frente();
			c1.desencolar();
			if(aux){
				costoAux = aux->obtCosto();
				std::cout << "|";
				if(costoAux != 0){
					std::cout << "(";
					std::cout << std::setw(3) << std::setprecision(2);
					std::cout << std::left << costoAux;
					std::cout << ")  ";
				}else{
					std::cout << std::setw(7) << std::setprecision(2);
					std::cout << " ";
				}
				flag = true;
			}else{
				std::cout << std::setw(8) << " ";
			}
			c2.encolar(aux);
		}
		std::cout << std::endl;
		while(!c2.esVacia() && flag){
			aux = c2.frente();
			c2.desencolar();
			if(aux){
				std::cout << std::setw(8) << std::setprecision(2);
				std:: cout << std::left;
				std::cout << aux->obtVert()->obtInfo();
				aux = aux->obtSig();
			}else{
				std::cout << std::setw(8) << " ";
			}
			c1.encolar(aux);
		}
		std::cout << std::endl;
	}
}

template <class T, class C>
inline void Grafo<T,C>::mostrar() const{
	this->mostrar(std::cout);
}

template <class T, class C>
int Grafo<T,C>::gradoInterior(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	while(actV){		
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				grado++;
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(grado);
}

template <class T, class C>
int Grafo<T,C>::gradoExterior(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	actV = ubicar(v);
	if(actV){
		actA = actV->obtPri();
		while(actA){
			grado++;
			actA = actA->obtSig();
		}
	}
	return(grado);
}

template <class T, class C>
int Grafo<T,C>::grado(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	int grado = 0;
	while(actV){		
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					grado++;
				}
				grado++;
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					grado++;
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(grado);
}

template <class T, class C>
bool Grafo<T,C>::adyacentes(const T &v, const T &w){
	NodoV<T,C> *actV, *actW;
	NodoA<T,C> *actA;
	ubicarAmbos(v, w, actV, actW);
	if(actV && actW){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == w){
				return(true);
			}
			actA = actA->obtSig();
		}
		actA = actW->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				return(true);
			}
			actA = actA->obtSig();
		}
	}
	return(false);
}

template <class T, class C>
Lista<T> Grafo<T,C>::listaVertices() const{
	NodoV<T,C> *act = this->g;
	Lista<T> l;
	while(act){
		l.insertar(act->obtInfo(), l.longitud() + 1);
		act = act->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::sucesores(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	actV = this->ubicar(v);
	if(actV){
		actA = actV->obtPri();
		while(actA){
			l.insertar(actA->obtVert()->obtInfo(), l.longitud() + 1);
			actA = actA->obtSig();
		}
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::predecesores(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			if(actA->obtVert()->obtInfo() == v){
				l.insertar(actV->obtInfo(), l.longitud() + 1);
			}
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::fuentes() const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		while(actA){
			actA->obtVert()->marcar();
			actA = actA->obtSig();
		}
		actV = actV->obtSig();
	}
	actV = this->g;
	while(actV){
		if(!actV->obtMarca()){
			l.insertar(actV->obtInfo(), l.longitud() + 1);
		}
		actV->desmarcar();
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::sumideros() const{
	NodoV<T,C> *actV = this->g;
	Lista<T> l;
	while(actV){
		if(!actV->obtPri()){
			l.insertar(actV->obtInfo(), l.longitud() + 1);
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::vecindad(const T &v) const{
	NodoV<T,C> *actV = this->g;
	NodoA<T,C> *actA;
	Lista<T> l;
	while(actV){
		actA = actV->obtPri();
		if(actV->obtInfo() == v){
			while(actA){
				l.insertar(actA->obtVert()->obtInfo(), l.longitud() + 1);
				actA = actA->obtSig();
			}
		}else{
			while(actA){
				if(actA->obtVert()->obtInfo() == v){
					l.insertar(actV->obtInfo(), l.longitud() + 1);
				}
				actA = actA->obtSig();
			}
		}
		actV = actV->obtSig();
	}
	return(l);
}

template <class T, class C>
Lista<T> Grafo<T,C>::camino(const T &v, const T &w) const{
	Lista<T> res, q, sucesores;
	T u, k;
	if(arcos == 0){
		return(res);
	}
	bool *visitados = new bool[vertices];
	int *distancia = new int[vertices];
	int *predecesor = new int[vertices];
	for(int i = 0; i < vertices; i++){
		visitados[i] = false;
		distancia[i] = std::numeric_limits<int>::max();
		predecesor[i] = -1;
		q.insertar(i , q.longitud() + 1);
	}
	distancia[v-1] = 0;
	while(!q.esVacia()){
		u = distanciaMin(q, distancia);
		if(u + 1 == w){
			while(true){
				res.insertar(u + 1, 1);
				if(u + 1 == v){
					return(res);
				}
				u = predecesor[u] - 1;
			}
		}
		sucesores = this->sucesores(u + 1);		
		while(!sucesores.esVacia()){
			k = sucesores.consultar(1) - 1;
			sucesores.eliminar(1);
			if(distancia[u] < distancia[k]){
				distancia[k] = distancia[u] + 1;
				predecesor[k] = u + 1;
			}
			
		}
	}
	//~ for(int i = 0; i < vertices; i++){
		//~ std::cout << "dist[ " << i+1 << "] = " << distancia[i] << std::endl;
	//~ }	
	//~ for(int i = 0; i < vertices; i++){
		//~ cout << "pred[ " << i+1 << "] = " << predecesor[i] << endl;
	//~ }
	return(res);
}

template <class T, class C>
T Grafo<T,C>::distanciaMin(Lista<T> &l, int *dist) const{
	int tam = l.longitud();
	T min = 0, aux;
	int minVar = std::numeric_limits<int>::max();
	for(int i = 0; i < tam; i++){
		aux = l.consultar(i+1);
		if(dist[aux] < minVar){
			min = aux;
			minVar = dist[aux];
		}
	}
	l.eliminar(l.obtPos(min));
	return(min);
}

template <class T, class C>
bool Grafo<T,C>::igual(const Grafo<T,C> &g2) const{
	NodoV<T,C> *actV1, *actV2;
	NodoA<T,C> *actA1, *actA2;
	actV1 = this->g;
	actV2 = g2.g;
	while(actV1 && actV2){
		if(actV1->obtInfo() != actV2->obtInfo()){
			return(false);
		}
		actA1 = actV1->obtPri();
		actA2 = actV2->obtPri();
		while(actA1 && actA2){
			if(actA1->obtVert()->obtInfo() != actA2->obtVert()->obtInfo() ||
				actA1->obtCosto() != actA2->obtCosto()){
				return(false);
			}
			actA1 = actA1->obtSig();
			actA2 = actA2->obtSig();
		}
		if(actA1 || actA2){
			return(false);
		}
		actV1 = actV1->obtSig();
		actV2 = actV2->obtSig();
	}
	if(actV1 || actV2){
		return(false);
	}
	return(true);
}

template <class T, class C>
bool Grafo<T,C>::obtMarca(const T &v) const{
	NodoV<T,C> *actV = this->ubicar(v);
	if(actV){
		return(actV->obtMarca());
	}else{
		return(false);
	}
}

template <class T, class C>
void Grafo<T,C>::BFS(const T &s, T *dist, T *pred){
	Lista<T> l;
	Cola<T> c;
	std::string *color = new std::string[this->vertices];
	T u, v;
	for(int i = 0; i < this->vertices; i++){
		dist[i] = std::numeric_limits<int>::max();
		color[i] = "blanco";
		pred[i] = 0;
	}
	color[s-1] = "gris";
	dist[s-1] = 0;
	c.encolar(s);
	while(!c.esVacia()){
		u = c.frente();
		c.desencolar();
		l = this->sucesores(u);
		while(!l.esVacia()){
			v = l.consultar(1);
			l.eliminar(1);
			if(color[v-1] == "blanco"){
				color[v-1] = "gris";
				dist[v-1] = dist[u-1] + 1;
				pred[v-1] = u;
				c.encolar(v);
			}
		}
		color[u-1] = "negro";
	}
	for(int i = 0; i < vertices; i++){
		std::cout << "dist[" << i+1 << "] = " << dist[i] << std::endl;
		std::cout << "pred[" << i+1 << "] = " << pred[i] << std::endl;
		std::cout << "color[" << i+1 << "] = " << color[i] << std::endl;
		std::cout << "---------------------------" << std::endl;
	}
	delete[] color;
}

template <class T, class C>
void Grafo<T,C>::BFS(const T &v){
	int tam = this->vertices;
	if(tam > 0){
		T *dist = new T[tam];
		T *pred = new T[tam];
		this->BFS(v, dist, pred);
		delete[] dist;
		delete[] pred;
	}
}

template <class T, class C>
void Grafo<T,C>::DFS(){
	Lista<T> l = this->listaVertices();
	T s;
	std::string *color = new std::string[vertices];
	int *tdesc = new int[vertices];
	int *pred = new int[vertices];
	int *tfinal = new int[vertices];
	int tiempo = 0;
	for(int i = 0; i < vertices; i++){
		color[i] = "blanco";
		pred[i] = 0;
	}
	while(!l.esVacia()){
		s = l.consultar(1);
		l.eliminar(1);
		if(color[s-1] == "blanco"){
			this->DFS(s, pred, tdesc, tfinal, color, tiempo);
		}
	}
	for(int i = 0; i < vertices; i++){
		std::cout << "pred[" << i+1 << "] = " << pred[i] << std::endl;
		std::cout << "tfinal[" << i+1 << "] = " << tfinal[i] << std::endl;
		std::cout << "tdesc[" << i+1 << "] = " << tdesc[i] << std::endl;
		std::cout << "color[" << i+1 << "] = " << color[i] << std::endl;
		std::cout << "---------------------------" << std::endl;
	}
	delete[] color;
	delete[] tdesc;
	delete[] pred;
	delete[] tfinal;
}

//Se resta 1 a v para indice en vector de 0 hasta instancia.orden()-1
template <class T, class C>
void Grafo<T,C>::DFS(const T v, T *pred, T *tdesc, T *tfinal, std::string *color, int &tiempo){
	Lista<T> sucesores;
	T u;
	tiempo += 1;
	tdesc[v-1] = tiempo;
	color[v-1] = "gris";
	sucesores = this->sucesores(v);
	while(!sucesores.esVacia()){
		u = sucesores.consultar(1);
		sucesores.eliminar(1);
		if(color[u-1] == "blanco"){
			pred[u-1] = v;
			this->DFS(u, pred, tdesc, tfinal, color, tiempo);
		}
	}
	color[v-1] = "negro";
	tiempo += 1;
	tfinal[v-1] = tiempo;
}

template <class T, class C>
bool Grafo<T,C>::esArborescencia(){
	return(false);
}

//Esta funcion busca los nodos que contienen a los vertices v y w
//y guarda apuntadores a ellos por referencia
template <class T, class C>
void Grafo<T,C>::ubicarAmbos(const T &v, const T &w, NodoV<T,C> *&actV, NodoV<T,C> *&actW){
	NodoV<T,C> *act = g;
	actV = actW = 0;
	while(act && (!actV || !actW)){
		if(act->obtInfo() == v){
			actV = act;
		}
		if(act->obtInfo() == w){
			actW = act;
		}
		act = act->obtSig();
	}
}

//Esta funcion busca el nodo que contiene al vertice v
//y guarda un apuntador a el por referencia.
template <class T, class C>
NodoV<T,C>* Grafo<T,C>::ubicar(const T &v) const{
	NodoV<T,C> *act = g;
	while(act){
		if(act->obtInfo() == v){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}

template <class T, class C>
NodoA<T,C>* Grafo<T,C>::ubicar(NodoA<T,C> *actW, const T &w) const{
	NodoA<T,C> *act = actW;
	while(act){
		if(act->obtVert()->obtInfo() == w){
			return(act);
		}
		act = act->obtSig();
	}
	return(0);
}
/**Fin de Observadores**/


/**Modificadores**/
template <class T, class C>
void Grafo<T,C>::agregarVertice(const T &v){
	NodoV<T,C> *ant, *act, *nuevo;
	ant = 0;
	act = this->g;
	while(act && act->obtInfo() != v){
		ant = act;
		act = act->obtSig();
	}
	if(!act){
		nuevo = new NodoV<T,C>(v);
		if(!ant)
			this->g = nuevo;
		else
			ant->modSig(nuevo);
		this->fin = nuevo;
		this->vertices++;
	}
}

template <class T, class C>
void Grafo<T,C>::agregarArco(const T &v, const T &w, const C &p){
	NodoV<T,C> *act, *actV, *actW;
	NodoA<T,C> *arcV, *arcW, *nuevo;
	actV = actW = 0;
	arcV = arcW = 0;
	act = this->g;
	while(act && (!actV || !actW)){
		if(act->obtInfo() == v)
			actV = act;
		if(act->obtInfo() == w)
			actW = act;
		act = act->obtSig();
	}
	if(!actV){
		actV = this->agregarAlFinal(v);
	}
	if(!actW){
		actW = (w == v ? actV : this->agregarAlFinal(w));
	}
	arcV = actV->obtPri();
	while(arcV && arcV->obtVert()->obtInfo() != w){
		arcW = arcV;
		arcV = arcV->obtSig();
	}
	if(!arcV){
		nuevo = new NodoA<T,C>(actW, p);
		if(!arcW){
			actV->modPri(nuevo);
		}else{
			arcW->modSig(nuevo);
		}
		this->arcos++;
	}
}

template <class T, class C>
void Grafo<T,C>::eliminarArco(const T &v, const T &w){
	NodoV<T,C> *actV;
	NodoA<T,C> *arc, *arcAnt;
	bool flag = true;
	actV = 0;
	actV = this->ubicar(v);
	if(actV){		
		arc = actV->obtPri();
		while(arc && flag){
			if(arc->obtVert()->obtInfo() == w){
				if(arcAnt){
					arcAnt->modSig(arc->obtSig());
				}else{
					actV->modPri(arc->obtSig());
				}
				delete(arc);
				this->arcos--;
				flag = false;
			}else{				
				arcAnt = arc;
				arc = arc->obtSig();
			}
		}
	}
}

//Este metodo elimina el vertice v del grafo
template <class T, class C>
void Grafo<T,C>::eliminarVertice(const T &v){
	NodoV<T,C> *act, *ant, *actV, *antV;
	ant = actV = antV = 0;
	act = g;
	while(act){
		if(act->obtInfo() == v){
			eliminarTodosArcos(act);
			antV = ant;
			actV = act;
		}else{
			eliminarArcoDe(v, act);
		}
		ant = act;
		act = act->obtSig();
	}
	if(actV){
		if(antV){
			antV->modSig(actV->obtSig());			
			this->fin = (actV->obtInfo() == this->fin->obtInfo() ? antV : this->fin);
		}else{
			this->g = actV->obtSig();
			this->fin = (this->g ? this->fin : 0);
		}
		
		delete(actV);
		this->vertices--;
	}
}

//elimina todos los arcos que tenga el vertice al que apunta act
template <class T, class C>
void Grafo<T,C>::eliminarTodosArcos(NodoV<T,C> *act){
	NodoA<T,C> *arc, *arcAux;
	arc = act->obtPri();
	while(arc){
		arcAux = arc;
		arc = arc->obtSig();
		delete(arcAux);
		this->arcos--;
	}
	act->modPri(arc);
}

//Esta funcion elimina el arco v del vertice al que apunta act
template <class T, class C>
void Grafo<T,C>::eliminarArcoDe(const T &v, NodoV<T,C> *act){
	NodoA<T,C> *arcAux, *arc;
	bool flag = true;
	arcAux = 0;
	arc = act->obtPri();
	while(arc && flag){
		if(arc->obtVert()->obtInfo() == v){
			if(arcAux){
				arcAux->modSig(arc->obtSig());
			}else{
				act->modPri(arc->obtSig());
			}
			delete(arc);
			this->arcos--;
			flag = false;
		}else{
			arcAux = arc;
			arc = arc->obtSig();
		}
	}
}

//Este metodo agrega un nuevo vertice al final de la "lista"
//y retorna un apuntador a este.
template <class T, class C>
NodoV<T,C>* Grafo<T,C>::agregarAlFinal(const T &v){
	NodoV<T,C> *nuevo = new NodoV<T,C>(v);
	if(this->fin){
		this->fin->modSig(nuevo);
		this->fin = this->fin->obtSig();
	}else{
		this->g = this->fin = nuevo;
	}
	this->vertices++;
	return(this->fin);
}

template <class T, class C>
void Grafo<T,C>::nulo(){
	NodoV<T,C> *actV = this->g, *auxV;
	NodoA<T,C> *actA, *auxA;
	while(actV){
		auxV = actV;
		actA = actV->obtPri();	//Obteniendo primer arco del vertice actV
		actV = actV->obtSig();	//Moviendose al siguiente vertice
		while(actA){
			auxA = actA;
			actA = actA->obtSig();	//Obteniendo siguiente arco
			delete(auxA);
		}
		delete(auxV);
	}
	this->g = this->fin = 0;
	this->vertices = this->arcos = 0;
}

template <class T, class C>
void Grafo<T,C>::copiar(const Grafo<T,C> &g2){
	this->nulo();
	this->copiarVertices(g2);
	this->copiarArcos(g2);
	this->vertices = g2.vertices;
	this->arcos = g2.arcos;
}

template <class T, class C>
void Grafo<T,C>::copiarVertices(const Grafo<T,C> &g2){
	NodoV<T,C> *actVg2, *actV, *nuevo;
	actVg2 = g2.g;
	actV = 0;
	while(actVg2){
		nuevo = new NodoV<T,C>(actVg2->obtInfo());
		if(this->g){
			actV->modSig(nuevo);
			actV = actV->obtSig();
		}else{
			actV = nuevo;
			this->g = actV;
		}
		actVg2 = actVg2->obtSig();
	}
	this->fin = actV;
}

//Copia todos los arcos de g2 a la instancia, suponiendo que la
//instancia ya posee los vertices.
template <class T, class C>
void Grafo<T,C>::copiarArcos(const Grafo<T,C> &g2){
	NodoV<T,C> *actVg2, *actV;
	NodoA<T,C> *actAg2, *actA, *nuevo;
	actVg2 = g2.g;
	actV = this->g;
	while(actVg2){
		actAg2 = actVg2->obtPri();
		while(actAg2){
			nuevo = new NodoA<T,C>(this->ubicar(actAg2->obtVert()->obtInfo()), actAg2->obtCosto());
			if(actV->obtPri()){
				actA->modSig(nuevo);
				actA = actA->obtSig();
			}else{
				actA = nuevo;
				actV->modPri(actA);
			}
			actAg2 = actAg2->obtSig();
		}
		actV = actV->obtSig();
		actVg2 = actVg2->obtSig();
	}
}

template <class T, class C>
void Grafo<T,C>::marcar(const T &v){
	NodoV<T,C> *actV = this->ubicar(v);
	if(actV){
		actV->marcar();
	}
}

template <class T, class C>
void Grafo<T,C>::desmarcar(const T &v){
	NodoV<T,C> *actV = this->ubicar(v);
	if(actV){
		actV->desmarcar();
	}
}
/**Fin de Modificadores**/


/**Sobrecarga de Operadores**/
template <class T, class C>
Grafo<T,C>& Grafo<T,C>::operator = (const Grafo<T,C> &g2){
	this->copiar(g2);
	return(*this);
}

template <class T, class C>
bool Grafo<T,C>::operator == (const Grafo<T,C> &g2){
	return(this->igual(g2));
}

template <class t, class c>
std::ostream& operator << (std::ostream &o, const Grafo<t, c> &g){
	g.mostrar(o);
	return(o);
}
/**Fin deSobrecarga de Operadores**/


/**Destructor**/
template <class T, class C>
Grafo<T,C>::~Grafo(){
	this->nulo();
}
/**Fin de Destructor**/
#endif
