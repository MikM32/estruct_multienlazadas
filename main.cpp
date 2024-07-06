#include <iostream>
#include "Grafos.h"

using namespace std;

int main()
{
    Grafo<int> test;

    test.agregarVertice(1);
    test.agregarVertice(2);
    test.agregarVertice(3);
    test.agregarVertice(4);
    test.agregarVertice(5);

    test.agregarArco(1, 2);
    test.agregarArco(1, 3);
    test.agregarArco(2, 5);
    test.agregarArco(5, 1);
    test.agregarArco(3, 4);
    test.agregarArco(4, 2);


    test.convertirNoDirigido();
    printFormatedList(test.getPredecesores(4));
    printFormatedList(test.getSucesores(4));


    return 0;
}
