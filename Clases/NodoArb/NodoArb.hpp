#ifndef NODO_ARB_H
#define NODO_ARB_H

#include <iostream>

template <class T>
class NodoArb{
private:
	NodoArb<T> *hi, *hd;
	T info;
	
public:
	//Constructores
	NodoArb();
	NodoArb(const T);
	NodoArb(NodoArb<T>*, const T, NodoArb<T>*);
	
	//Observadores
	NodoArb<T>* obtHi() const;
	NodoArb<T>* obtHd() const;
	NodoArb<T>*& obtHi();
	NodoArb<T>*& obtHd();
	T obtInfo() const;
	
	//Modificadores
	void modHi(NodoArb<T>*);
	void modHd(NodoArb<T>*);
	void modInfo(const T);
	
	//Destructor
};

/*Constructores*/
template <class T>
NodoArb<T>::NodoArb() : hi(0), hd(0), info(T()) {}

template <class T>
NodoArb<T>::NodoArb(const T e) : hi(0), hd(0), info(e) {}

template <class T>
NodoArb<T>::NodoArb(NodoArb<T> *i, const T e, NodoArb<T> *d) : hi(i), hd(d), info(e) {}
/*Fin de Constructores*/

/*Observadores*/
template <class T>
NodoArb<T>* NodoArb<T>::obtHi() const
{ return(this->hi); }

template <class T>
NodoArb<T>* NodoArb<T>::obtHd() const
{ return(this->hd); }

template <class T>
NodoArb<T>*& NodoArb<T>::obtHi()
{ return(this->hi); }

template <class T>
NodoArb<T>*& NodoArb<T>::obtHd()
{ return(this->hd); }

template <class T>
T NodoArb<T>::obtInfo() const{ return(this->info); }
/*Fin de Observadores*/

/*Modificadores*/
template <class T>
void NodoArb<T>::modHi(NodoArb<T> *i){ this->hi = i; }

template <class T>
void NodoArb<T>::modHd(NodoArb<T> *d){ this->hd = d; }

template <class T>
void NodoArb<T>::modInfo(const T e){ this->info = e; }
/*Fin de Modificadores*/

#endif
