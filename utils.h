#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include<list>
#include<stack>
#include<queue>
#include<algorithm>
#include<string>


using namespace std;

template< typename elem>
void printList(list<elem> lista)
{
    for(auto a: lista)
    {
        cout << a << " ";
    }

    cout << endl;
}

template< typename elem>
void printFormatedList(list<elem> lista)
{
    cout << "[";
    for(auto a: lista)
    {
        cout << a;
        if(a != lista.back())
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

template< typename elem>
void leerLista(list<elem>& lista)
{
    elem acum;

}


#endif // UTILS_H_INCLUDED
