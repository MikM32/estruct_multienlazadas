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
    NodoVertice<elem>* primero;
    int nVertices, nArcos;


    NodoVertice<elem>* getNodoVertice(elem v)
    {
        NodoVertice<elem>* act=this->primero;

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

        if(this->primero != NULL && this->primero->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->primero;
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

    //============================
    //=======Constructores
    //============================
    Grafo()
    {
        this->primero = NULL;
        this->nVertices = 0;
    }

    //============================



    int getNVertices()
    {
        return this->nVertices;
    }

    void copiar(Grafo<elem>& g2)
    {

    }

    void agregarVertice(elem v)
    {
        if(this->primero == NULL)
        {
            this->primero = new NodoVertice<elem>(v);
            this->nVertices++;
        }
        else
        {
            NodoVertice<elem>* act = this->primero;

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
        if(this->primero != NULL && this->primero->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->primero;
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

                this->nArcos++;
            }
        }
    }

    void agregarArcoNoDirigido(elem v, elem w, float peso=-1.0)
    {
        if(this->primero != NULL && this->primero->getProx() != NULL) // Si el grafo no es vacio y tiene mas de 1 vertice
        {
            NodoVertice<elem>* vertAct = this->primero;
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
                    vertV->setArco(new NodoArco<elem>(peso, vertW));
                }
                else
                {
                    aux = vertV->getArco();
                    vertV->setArco(new NodoArco<elem>(peso, vertW, aux));

                }

                arcoAct = vertW->getArco();
                if(arcoAct == NULL)
                {
                    vertW->setArco(new NodoArco<elem>(peso, vertV));
                }
                else
                {
                    aux = vertW->getArco();
                    vertW->setArco(new NodoArco<elem>(peso, vertV, aux));

                }

                this->nArcos++;

            }
        }
    }

    void eliminarArco(elem v, elem w)
    {
        NodoVertice<elem>* vert = getNodoVertice(v);
        NodoArco<elem>* arcoAct = vert->getArco(), *anterior = vert->getArco();

        while(arcoAct!=NULL)
        {
            if(arcoAct->getVertice()->getInfo() == w)
            {
                anterior->setProx(arcoAct->getProx());
                delete arcoAct;
                break;
            }

            arcoAct = arcoAct->getProx();
        }
    }

    void eliminarVertice(elem v)
    {
        NodoVertice<elem>* nodoEliminar = NULL, *antEliminar=NULL, *nodoAct=this->primero, *vanterior=NULL;
        NodoArco<elem>* arcAct=NULL, *anterior=NULL;

        while(nodoAct != NULL)
        {
            arcAct = nodoAct->getArco();

            if(nodoAct->getInfo() == v)
            {
                antEliminar = vanterior;
                nodoEliminar = nodoAct;
            }

            while(arcAct != NULL)
            {

                if(arcAct->getVertice()->getInfo() == v)
                {
                    if(anterior)
                    {
                        anterior->setProx(arcAct->getProx());
                        delete arcAct;
                    }
                    else
                    {
                        nodoAct->setArco(arcAct->getProx());
                        delete arcAct;
                    }
                    break;
                }

                anterior = arcAct;
                arcAct = arcAct->getProx();
            }

            vanterior = nodoAct;
            nodoAct = nodoAct->getProx();
        }

        arcAct = nodoEliminar->getArco();
        list<NodoArco<elem>*> arcos;
        while(arcAct != NULL)
        {
            arcos.push_front(arcAct);
            arcAct = arcAct->getProx();
        }

        while(!arcos.empty())
        {
            delete arcos.front();
            arcos.pop_front();
        }

        if(antEliminar)
        {
            antEliminar->setProx(nodoEliminar->getProx());
            delete nodoEliminar;
        }
        else
        {
            this->primero = nodoEliminar->getProx();
            delete nodoEliminar;
        }


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
        NodoVertice<elem>* vActual = this->primero;
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
        NodoVertice<elem>* act=this->primero;
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
        NodoVertice<elem>* vActual=NULL, *vNoDirigido = this->primero;
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
                    if(penult)
                    {
                        nuevoArc = new NodoArco<elem>();
                        nuevoArc->setVertice(vNoDirigido);
                        penult->setProx(nuevoArc);
                    }
                    else
                    {
                        nuevoArc = new NodoArco<elem>();
                        nuevoArc->setVertice(vNoDirigido);
                        arcoAct->getVertice()->setArco(nuevoArc);
                    }

                }
                arcoAct = arcoAct->getProx();
            }

            vNoDirigido = vNoDirigido->getProx();
        }

    }

    int getMapIndice(vector<elem> elemMap, elem valor)
    {
        for(int i=0; i<elemMap.size(); i++)
        {
            if(elemMap[i] == valor)
            {
                return i;
            }
        }

        return -1;
    }

    Grafo<int> mapear(vector<elem>* elemMap)
    {
        Grafo<int> grafoMapeado;
        NodoVertice<elem>* act=NULL;
        NodoArco<elem>* arcAct=NULL;

        act = this->primero;

        int cont =0;
        while(act != NULL)
        {
            elemMap->emplace(elemMap->end(), act->getInfo());
            grafoMapeado.agregarVertice(cont);
            act = act->getProx();

            cont++;

        }

        cont =0;
        act = this->primero;
        while(act != NULL)
        {
            arcAct = act->getArco();
            while(arcAct != NULL)
            {
                int indice = getMapIndice(*elemMap, arcAct->getVertice()->getInfo());
                if(indice >= 0)
                {
                    grafoMapeado.agregarArco(cont, indice, arcAct->getPeso());
                }

                arcAct = arcAct->getProx();
            }

            cont++;
            act = act->getProx();
        }

        return grafoMapeado;
    }

    list<elem> getVertices()
    {
        list<elem> res;

        NodoVertice<elem>* act = this->primero;

        while(act != NULL)
        {
            res.push_back(act->getInfo());

            act = act->getProx();
        }

        return res;
    }

    Grafo<elem> desmapear(vector<elem>& elemMap)
    {

    }

    bool esConexo()
    {
        return componentesConexas() == 1;
    }

    int componentesConexas()
    {
        return 0;
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

    int pesoMinIndice(list<float> pesos)
    {

    }

    Grafo<elem> arbolExpandidoMin(elem inicio)
    {
        Grafo<elem> res;
        list<elem> partida, llegada, sucesores;
        list<float> pesos;
        vector<bool> visitados(this->nVertices, false);

        sucesores = this->getSucesores(inicio);
        llegada = sucesores;

        int cont=0;
        while(!sucesores.empty())
        {
            partida.push_back(inicio);
            pesos.push_back(this->getPesoArco(inicio, sucesores.front()));
            sucesores.pop_front();
        }

        visitado[inicio] = true;

        res.agregarVertice(inicio);

        while(!pesos.empty())
        {
            int minIndice = pesoMinIndice(pesos);
            elem vLlegada = llegada[minIndice];

            if(visitados[llegada[minIndice]])
            {

                res.agregarVertice(vLlegada);

                res.agregarArco(partida[minIndice], vLlegada, pesos[minIndice]);

                sucesores = this->getSucesores();

                while(!sucesores.empty())
                {
                    if(!visitados)
                }
            }
        }

    }

    bool esSumidero(elem v)
    {
        list<elem> sucesores = this->getSucesores(v);
        return sucesores.empty();
    }

    bool esFuente(elem v)
    {
        list<elem> pred = this->getPredecesores(v);
        return pred.empty();
    }

    list<elem> caminoMasCorto(elem v, elem w)
    {
        vector<bool> visitados(this->nVertices, false);
        vector<float> costos(this->nVertices, -1.0);
        vector<elem> predecesores(this->nVertices);

        queue<elem> colaAux;
        list<elem> sucesores, camino;

        costos[v] = 0.0;
        visitados[v] = true;
        float costoActual;

        if(v >= this->nVertices || w >= this->nVertices)
        {
            return camino;
        }

        colaAux.push(v);
        elem act, act2=v;
        while(!colaAux.empty())
        {
            act = colaAux.front();
            colaAux.pop();


            sucesores = this->getSucesores(act);
            visitados[act2] = true;

            while(!sucesores.empty())
            {
                act2 = sucesores.front();


                costoActual = costos[act] + this->getPesoArco(act, act2);

                if(costoActual < costos[act2] || costos[act2] == -1)
                {

                    if(!visitados[act2])
                    {
                        costos[act2] = costoActual;
                        predecesores[act2] = act;
                        colaAux.push(act2);
                    }
                }
                sucesores.pop_front();

            }

        }

        act = w;
        camino.push_front(act);


        while(act != v )
        {
            act = predecesores[act];
            camino.push_front(act);
        }

        if(camino.back()!=w || camino.front() != v)
        {
            return list<elem>();
        }

        return camino;
    }

    list<elem> caminoMasCorto(elem v, elem h, elem w)
    {

    }

    list<elem> caminoMasCortoSin(elem v, list<elem> h, elem w)
    {
        vector<bool> visitados(this->nVertices, false);
        vector<float> costos(this->nVertices, -1.0);
        vector<elem> predecesores;

        queue<elem> colaAux;
        list<elem> sucesores, camino;


        if(v >= this->nVertices || w >= this->nVertices)
        {
            return camino;
        }

        while(!h.empty())
        {
            if(h.front() >= this->nVertices)
            {
                return camino;
            }

            visitados[h.front()] = true;

            h.pop_front();
        }

        costos[v] = 0.0;
        visitados[v] = true;
        float costoActual;


        colaAux.push(v);
        elem act, act2=v;
        while(!colaAux.empty())
        {
            act = colaAux.front();
            colaAux.pop();

            sucesores = this->getSucesores(act);
            visitados[act2] = true;

            while(!sucesores.empty())
            {
                act2 = sucesores.front();

                costoActual = costos[act] + this->getPesoArco(act, act2);

                if(costoActual < costos[act2] || costos[act2] == -1)
                {
                    if(!visitados[act2])
                    {

                        costos[act2] = costoActual;
                        predecesores[act2] = act;
                        colaAux.push(act2);
                    }
                }
                sucesores.pop_front();

            }
        }

        act = w;
        camino.push_front(act);

        while(act != v )
        {
            act = predecesores[act];
            camino.push_front(act);
        }

        if(camino.back()!=w || camino.front() != v)
        {
            return list<elem>();
        }


        return camino;
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
            res = arco->getPeso();
        }
        return res;
    }

    bool esVacio()
    {
        return this->primero == NULL;
    }


};

#endif // GRAFOS_H_INCLUDED
