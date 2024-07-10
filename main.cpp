#include <iostream>
#include "Grafos.h"

using namespace std;

int main()
{

    Grafo<int> test;
    test.agregarVertice(0);
    test.agregarVertice(1);
    test.agregarVertice(2);
    test.agregarVertice(3);
    test.agregarVertice(4);

    test.agregarArcoNoDirigido(0, 1, 1);
    test.agregarArcoNoDirigido(0, 3, 6);
    test.agregarArcoNoDirigido(0, 4, 2);
    test.agregarArcoNoDirigido(0, 2, 4);
    test.agregarArcoNoDirigido(1, 4, 2);
    test.agregarArcoNoDirigido(1, 2, 3);
    test.agregarArcoNoDirigido(4, 2, 2);
    test.agregarArcoNoDirigido(4, 3, 4);
    test.agregarArcoNoDirigido(1, 2, 1);
    test.agregarArcoNoDirigido(3, 2, 5);



    Grafo<int> arbol = test.arbolExpandidoMin(0);
    printFormatedList(arbol.dfs(0));




    return 0;
}
