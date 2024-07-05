#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED

#include "nodos.h"

template <typename elem>
class Grafo
{

private:
    NodoVertice<elem>* nodoRaiz;

public:
    Grafo()
    {
        this->nodoRaiz = NULL;
    }

    void agregarVertice(elem v) // O(1)
    {

    }

    void agregarArco(elem v, elem w) //O(N)
    {

    }

    void eliminarArco(elem v, elem w)
    {

    }

    void eliminarVertice(elem v)
    {

    }

    void modificarPesoArco(elem v, elem w)
    {

    }

    list<elem> getVecinos()
    {

    }

    list<elem> getSucesores(elem vertice)
    {

    }

    list<elem> getPredecesores(elem vertice)
    {

    }

    void convertirNoDirigido()
    {

    }

    list<elem> dfs(elem v)
    {

    }

    list<elem> bfs(elem v)
    {

    }

    list<elem> niveles(elem)
    {

    }

    list<elem> ordenamientoTopologico(list<elem> lista)
    {

    }

    Grafo<elem> arbolExpandidoMin(Grafo<elem> g)
    {

    }

    list<elem> caminoMasCorto(elem v, elem w)
    {

    }

    list<elem> caminoMasCorto(elem v, elem h, elem w)
    {

    }

    void construirHipercubo(int dimension)
    {

    }

    void esIsomorfo(Grafo<elem> g2)
    {

    }

    bool existeArco(elem v, elem w)
    {

    }

    float getPesoArco(elem v, elem w)
    {

    }

    bool esVacio()
    {
        return this->nodoRaiz == NULL;
    }


};

#endif // GRAFOS_H_INCLUDED
