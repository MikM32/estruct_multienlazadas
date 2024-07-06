#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED

#include "nodos.h"

template <typename elem>
class Grafo
{

//========================================
//      ATRIBUTOS Y METODOS PRIVADOS
//========================================
private:
    NodoVertice<elem>* raiz;
    int nVertices;


    NodoVertice<elem>* getNodoVertice(elem v)
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

    NodoArco<elem>* getNodoArco(elem v, elem w)
    {

        NodoArco<elem>* res=NULL;

        if(this->raiz != NULL && this->raiz->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->raiz;
            NodoVertice<elem>* vertV = NULL;
            //NodoVertice<elem>* vertW = NULL;
            bool encontrados = false;

            while(vertAct != NULL)
            {
                if(vertAct->getInfo() == v) // Como se entiende que no hay elementos repetidos entonces la verificacion es asi
                {
                    vertV = vertAct;
                    break;
                }

                vertAct = vertAct->getProx();

            }

            if(vertV)
            {
                res = getNodoArco(vertV, w);
            }

        }

        return res;
    }

    NodoArco<elem>* getNodoArco(NodoVertice<elem>* nodoV, elem w)
    {
        NodoArco<elem>* res=NULL;
        if(nodoV)
            {
                NodoArco<elem>* arcoAct = nodoV->getArco();

                while(arcoAct != NULL)
                {
                    if(arcoAct->getVertice()->getInfo() == w)
                    {
                        res=arcoAct;
                        break;
                    }

                    arcoAct = arcoAct->getProx();
                }

            }
        return res;
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


//========================================
//      ATRIBUTOS Y METODOS PUBLICOS
//========================================
public:
    Grafo()
    {
        this->raiz = NULL;
        this->nVertices = 0;
    }

    void copiar(Grafo<elem>& g2)
    {

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

            bool repetido= (act->getInfo() == v) ? true: false;

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

    void destruir()
    {

    }

    void modificarPesoArco(elem v, elem w, float peso)
    {
        NodoArco<elem>* arco = getNodoArco(v, w);

        if(arco)
        {
            arco->setPeso(peso);
        }
    }

    list<elem> getVecinos(elem v) // Necesario para grafos dirigidos (para no dirigidos con un getSucesores o getPredecesores basta).
    {
        list<elem> res;
        vector<bool> visitados(this->nVertices, false);
        NodoVertice<elem>* vActual = this->raiz;
        NodoArco<elem>* arcoActual =NULL;
        bool encontrado=false;

        while(vActual != NULL)
        {
            arcoActual = vActual->getArco();

            if(!encontrado)
            {
                if(vActual->getInfo() == v)
                {
                    while(arcoActual != NULL)
                    {
                        res.push_back(arcoActual->getVertice()->getInfo());

                        arcoActual = arcoActual->getProx();
                    }
                    encontrado=true;
                }
            }


            while(arcoActual != NULL)
            {
                if(arcoActual->getVertice()->getInfo() == v)
                {
                    res.push_back(vActual->getInfo());
                }

                arcoActual = arcoActual->getProx();
            }


            vActual = vActual->getProx();
        }

        return res;
    }

    list<elem> getSucesores(elem v)
    {
        list<elem> sucesores;
        NodoVertice<elem>* vert = getNodoVertice(v);
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

    list<elem> getPredecesores(elem v)
    {
        NodoVertice<elem>* act=this->raiz;
        list<elem> pred;

        while(act != NULL)
        {
            if(getNodoArco(act, v))
            {
                pred.push_back(act->getInfo());
            }
            act = act->getProx();
        }

        return pred;
    }

    void convertirNoDirigido()
    {
        NodoVertice<elem>* vActual=NULL, *vNoDirigido = this->raiz;
        NodoArco<elem>* arcoAct, *nuevoArc, *arcoAct2, *penult;


        while(vNoDirigido != NULL) // recorre todos los vertices
        {
            arcoAct = vNoDirigido->getArco();


            while(arcoAct != NULL) // Recorre cada arco del vertice actual
            {
                arcoAct2 = arcoAct->getVertice()->getArco(); // Obtengo la lista de adyacencia (o primer arco) del vertice apuntado
                penult = arcoAct2;// guardo el penultimo arco para insertar al final                          //por el arco del vertice actual
                bool repetido=false;

                while(arcoAct2 != NULL) // Recorre los arcos del vertice apuntado por el arco actual
                {
                    if(arcoAct2->getVertice()->getInfo() == vNoDirigido->getInfo()) // si hay algun arco que apunte al vertice actual
                    {                                                               // entonces no es necesario agregar el arco (porque se repetiria)
                        repetido = true;
                        break;
                    }
                    penult = arcoAct2;
                    arcoAct2 = arcoAct2->getProx();
                }

                if(!repetido) // Si el arco no esta agregado entonces lo crea e inserta al final
                {
                    nuevoArc = new NodoArco<elem>();
                    nuevoArc->setVertice(vNoDirigido);
                    penult->setProx(nuevoArc);
                }
                arcoAct = arcoAct->getProx();
            }

            vNoDirigido = vNoDirigido->getProx();
        }

    }

    void mapear()
    {

    }

    bool esConexo()
    {

    }

    bool esPuente(elem v)
    {

    }

    list<elem> getPuentes()
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
        list<elem> res, sucesores;
        vector<bool> visitados(this->nVertices, false);
        queue<elem> colaAux;
        elem actual, w;

        colaAux.push(v);
        visitados[v] = true;

        while(!colaAux.empty())
        {
            actual = colaAux.front();

            res.push_back(actual);

            sucesores = getSucesores(actual);

            while(!sucesores.empty())
            {
                w = sucesores.front();

                if(!visitados[w])
                {
                    visitados[w] = true;
                    colaAux.push(w);
                }

                sucesores.pop_front();
            }

            colaAux.pop();

        }

        return res;
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

    bool esIsomorfo(Grafo<elem> g2)
    {

    }

    bool esBipartito()
    {

    }

    list<elem> getCaminoEuleriano()
    {

    }

    list<elem> getCaminoHamiltoniano()
    {

    }

    bool existeVertice(elem v)
    {
        NodoVertice<elem>* vert = getNodoVertice(v);

        return vert != NULL;
    }

    bool existeArco(elem v, elem w)
    {
        NodoArco<elem>* arco = getNodoArco(v, w);

        return arco != NULL;
    }

    float getPesoArco(elem v, elem w)
    {
        NodoArco<elem>* arco = getNodoArco(v, w);
        float res = -1.0;
        if(arco)
        {
            res = arco->getCosto();
        }
        return res;
    }

    bool esVacio()
    {
        return this->nodoRaiz == NULL;
    }


};

#endif // GRAFOS_H_INCLUDED
