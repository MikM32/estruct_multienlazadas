#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED

#include "nodos.h"

template <typename elem>
class Grafo
{

private:
    NodoVertice<elem>* raiz;
    int nVertices;


    NodoVertice<elem>* buscarNodoVertice(elem v)
    {
        NodoVertice<elem>* act=this->raiz;

        while(act != NULL)
        {
            if(act->getInfo() == v)
            {
                return act;
            }
            act = act->getProx();
        }

        return NULL;
    }

    NodoArco<elem>* buscarNodoArco(elem w)
    {

    }

    NodoArco<elem>* buscarNodoArco(elem w)
    {

    }


    void dfsRecur(list<elem>& recorrido, vector<bool>& visitados, elem v)
    {
        list<elem> sucesores;
        elem w;

        recorrido.push_back(v);
        visitados[v] = true;

        sucesores = getSucesores(v);

        while(!sucesores.empty())
        {
            w = sucesores.front();

            if(!visitados[w])
            {
                dfsRecur(recorrido, visitados, w);
            }

            sucesores.pop_front();
        }
    }

public:
    Grafo()
    {
        this->raiz = NULL;
        this->nVertices = 0;
    }

    void agregarVertice(elem v)
    {
        if(this->raiz == NULL)
        {
            this->raiz = new NodoVertice<elem>(v);
            this->nVertices++;
        }
        else
        {
            NodoVertice<elem>* act = this->raiz;

            bool repetido= act ? (act->getInfo() == v): false;

            while(act->getProx() != NULL) // Inserta al final para verificar durante el recorrido si el vertice ya existe.
            {
                if(act->getInfo() == v)
                {
                    repetido = true;
                    break;
                }
                act = act->getProx();
            }

            if(act != NULL && !repetido) // Si no existe (no es repetido) entonces lo inserta.
            {
                act->setProx(new NodoVertice<elem>(v));
                this->nVertices++;
            }
        }
    }

    void agregarArco(elem v, elem w, float costo=-1.0) //O(N)
    {
        if(this->raiz != NULL && this->raiz->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->raiz;
            NodoVertice<elem>* vertV = NULL;
            NodoVertice<elem>* vertW = NULL;
            bool encontrados = false;

            while(vertAct != NULL)
            {
                if(vertAct->getInfo() == v) // Como se entiende que no hay elementos repetidos entonces la verificacion es asi
                {
                    vertV = vertAct;
                }

                if(vertAct->getInfo() == w)
                {
                    vertW = vertAct;
                }

                if(vertV && vertW) // Si se encontraron ambos vertices se termina el ciclo
                {
                    encontrados = true;
                    break;
                }

                vertAct = vertAct->getProx();

            }

            if(encontrados)
            {
                NodoArco<elem>* arcoAct = vertV->getArco(), *aux=NULL;

                if(arcoAct == NULL)
                {
                    vertV->setArco(new NodoArco<elem>(costo, vertW));
                }
                else
                {
                    aux = vertV->getArco();
                    vertV->setArco(new NodoArco<elem>(costo, vertW, aux));

                }
            }
        }
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

    list<elem> getSucesores(elem v)
    {
        list<elem> sucesores;
        NodoVertice<elem>* vert = buscarNodoVertice(v);
        NodoArco<elem>* arcoAct = NULL;


        if(vert)
        {
            arcoAct=vert->getArco();

            while(arcoAct != NULL)
            {
                sucesores.push_back(arcoAct->getVertice()->getInfo());
                arcoAct = arcoAct->getProx();
            }
        }

        return sucesores;
    }

    list<elem> getPredecesores(elem vertice)
    {

    }

    void convertirNoDirigido()
    {

    }

    list<elem> dfs(elem v)
    {
        vector<bool> visitados(this->nVertices, false);
        list<elem> recorrido;

        this->dfsRecur(recorrido, visitados, v);

        return recorrido;

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

    bool existeVertice(elem v)
    {

    }

    bool existeArco(elem v, elem w)
    {
        bool res=false;
        if(this->raiz != NULL && this->raiz->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->raiz;
            NodoVertice<elem>* vertV = NULL;
            NodoVertice<elem>* vertW = NULL;
            bool encontrados = false;

            while(vertAct != NULL)
            {
                if(vertAct->getInfo() == v) // Como se entiende que no hay elementos repetidos entonces la verificacion es asi
                {
                    vertV = vertAct;
                }

                if(vertAct->getInfo() == w)
                {
                    vertW = vertAct;
                }

                if(vertV && vertW) // Si se encontraron ambos vertices se termina el ciclo
                {
                    encontrados = true;
                    break;
                }

                vertAct = vertAct->getProx();

            }

            if(encontrados)
            {
                NodoArco<elem>* arcoAct = vertV->getArco();

                while(arcoAct != NULL)
                {
                    if(arcoAct->getVertice()->getInfo() == w)
                    {
                        res=true;
                        break;
                    }

                    arcoAct = arcoAct->getProx();
                }

            }
        }

        return res;
    }

    float getCostoArco(elem v, elem w)
    {
        float res=-1.0;

        if(this->raiz != NULL && this->raiz->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->raiz;
            NodoVertice<elem>* vertV = NULL;
            NodoVertice<elem>* vertW = NULL;
            bool encontrados = false;

            while(vertAct != NULL)
            {
                if(vertAct->getInfo() == v) // Como se entiende que no hay elementos repetidos entonces la verificacion es asi
                {
                    vertV = vertAct;
                }

                if(vertAct->getInfo() == w)
                {
                    vertW = vertAct;
                }

                if(vertV && vertW) // Si se encontraron ambos vertices se termina el ciclo
                {
                    encontrados = true;
                    break;
                }

                vertAct = vertAct->getProx();

            }

            if(encontrados)
            {
                NodoArco<elem>* arcoAct = vertV->getArco();

                while(arcoAct != NULL)
                {
                    if(arcoAct->getVertice()->getInfo() == w)
                    {
                        res=arcoAct->getCosto();
                        break;
                    }

                    arcoAct = arcoAct->getProx();
                }

            }
        }

        return res;
    }

    bool esVacio()
    {
        return this->nodoRaiz == NULL;
    }


};

#endif // GRAFOS_H_INCLUDED
