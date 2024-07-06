#include <iostream>
#include "Grafos.h"

using namespace std;

int main()
{
    Grafo<int> test;

    test.agregarVertice(1);
    test.agregarVertice(2);
    test.agregarVertice(3);
    test.agregarVertice(1);

    test.agregarArco(1, 2);
    test.agregarArco(1, 3);

    printFormatedList(test.dfs(1));


    return 0;
}
