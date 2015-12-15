#ifndef ARBOLN_H
#define ARBOLN_H

#include <iostream>
#include <cmath>
#include "../NodoArb/NodoArb.hpp"
#include "../Lista/Lista.hpp"
#include "../Cola/Cola.hpp"
#include "../Pila/Pila.hpp"

template <class T>
class ArbolN{
protected:
	NodoArb<T> *raizArb;
	int pesoArb;
	
protected:
	//Metodos Auxiliares
	void nulo(NodoArb<T>*);																	//Para borrar la instancia (Podar el arbol)
	void impArbol(NodoArb<T>*, int, bool&, bool*, std::ostream&) const;
	
public:
	//Constructores
	inline ArbolN();
	
	//Observadores
	inline void impArbol() const;
	
	//Modificadores
	
	
	//Sobrecarga de operadores
	
	//~ template <class t>
	//~ friend std::ostream& operator << (std::ostream&, const ArbolN<t>&);
	
	//Destructor
	~ArbolN();
};

/*Constructores*/
template <class T>
inline ArbolN<T>::ArbolN() : raizArb(0), pesoArb(0) {}

template <class T>
std::ostream& operator << (std::ostream &o, const ArbolN<T> &a){
	bool f = false;
	bool *arr = new bool[a.peso];	
	a.impArbol(a.raizArb, 0, f, arr, o);
	return(o);
}
/*Fin de Sobrecarga*/


/*Observadores*/
template <class T>
inline void ArbolN<T>::impArbol() const{
	bool f = false;
	bool *arr = new bool[this->peso];
	impArbol(raizArb, 0, f, arr, std::cout);
}

template <class T>
void ArbolN<T>::impArbol(NodoArb<T> *act, int n, bool &f, bool *arr, std::ostream &o) const{
	if(act){
		for(int i = 0; i < n; i++){
			o << (arr[i] ? "|  " : "   ");
		}
		
		impArbol(act->obtHi(), n + 1, f, arr, o);
		impArbol(act->obtHd(), n + 1, f, arr, o);
	}
}
/*Fin de Observadores*/


/*Observadores*/

/*Fin de Modificadores*/


//Destructor
template <class T>
ArbolN<T>::~ArbolN(){
	//~ this->nulo(); 
}
#endif
