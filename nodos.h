#ifndef NODOS_H_INCLUDED
#define NODOS_H_INCLUDED

#include "utils.h"

//Declaracion de prototipos

template< typename elem>
class NodoVertice;

template< typename elem>
class NodoArco;

// Definicion de clases

template< typename elem>
class NodoArco
{
private:

    float costo;

    NodoVertice<elem>* vertice;
    NodoArco<elem>* prox;

public:

    //Constructores
    NodoArco():costo(-1.0), vertice(NULL), prox(NULL){};
    NodoArco(float costop):costo(costop), vertice(NULL), prox(NULL){};
    NodoArco(float costop, NodoVertice<elem>* vert):costo(costop), vertice(vert), prox(NULL){};
    NodoArco(float costop, NodoVertice<elem>* vert, NodoArco<elem>* proximo):costo(costop), vertice(vert), prox(proximo){};

    //Setters
    void setCosto(float costo)
    {
        this->costo = costo;
    }

    void setVertice(NodoVertice<elem>* vert)
    {
        this->vertice = vert;
    }

    void setProx(NodoArco<elem>* prox)
    {
        this->prox = prox;
    }

    //Getters
    float getCosto()
    {
        return this->costo;
    }

    NodoVertice<elem>* getVertice()
    {
        return this->vertice;
    }

    NodoArco<elem>* getProx()
    {
        return this->prox;
    }

};

template< typename elem>
class NodoVertice
{
private:
    elem info;

    NodoVertice<elem>* prox;
    NodoArco<elem>* listaAdy;

public:

    NodoVertice(): info(elem()), prox(NULL), listaAdy(NULL){};
    NodoVertice(elem inf): info(inf), prox(NULL), listaAdy(NULL){};
    NodoVertice(elem inf, NodoVertice<elem>* proximo): info(inf), prox(proximo), listaAdy(NULL){};
    NodoVertice(elem inf, NodoVertice<elem>* proximo, NodoArco<elem>* arco): info(inf), prox(proximo), listaAdy(arco){};

    //Getters
    elem getInfo()
    {
        return this->info;
    }

    NodoArco<elem>* getArco()
    {
        return this->listaAdy;
    }

    NodoVertice<elem>* getProx()
    {
        return this->prox;
    }

    //Setters
    void setProx(NodoVertice<elem>* prox)
    {
        this->prox = prox;
    }

    void setArco(NodoArco<elem>* arco)
    {
        this->listaAdy = arco;
    }

    void setInfo(elem info)
    {
        this->info = info;
    }
};


#endif // NODOS_H_INCLUDED
