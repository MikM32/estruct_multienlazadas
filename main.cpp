#include <iostream>
#include "Grafos.h"

using namespace std;

int main()
{
    Grafo<string> test;

    test.agregarVertice("hola");
    test.agregarVertice("adios");
    test.agregarVertice("waza");
    test.agregarVertice("pedro");

    test.agregarArco("hola", "adios", 10);
    test.agregarArco("hola", "waza", 2);
    test.agregarArco("waza", "adios", 1);
    test.agregarArco("adios", "pedro", 1);
    test.agregarArco("waza", "pedro", 18);



    vector<string> elemMapeados;
    //test.convertirNoDirigido();
    Grafo<int> testMapeado = test.mapear(&elemMapeados);

    //testMapeado.caminoMasCorto(0, 3);
    //printListaMapeada(testMapeado.caminoMasCorto(0, 4), elemMapeados);




    return 0;
}
