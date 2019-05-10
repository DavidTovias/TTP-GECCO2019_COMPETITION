#include<iostream>
#include<vector>
#include "lista.h"

#define MaxNodes 10

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "\n LISTA ENLAZADA\n";
    
    Lista *lista = new Lista();  // list
    Nodo *nodo_lista = new Nodo(); // node

    //nodo_lista->tour[0] = 991;
    //lista->addNode(nodo_lista);

    for(unsigned long i = 0; i < 4; i++){
        if(i==2){
            nodo_lista->tour[3] = 888;
        }
        nodo_lista->profit = i;
        nodo_lista->time = i+1;
        lista->addNode(nodo_lista);
        nodo_lista = new Nodo();
    }
    
    //nodo_lista->tour[0] = 888;
    //lista->addNode(nodo_lista);
    cout << "\n Elementos de la lista\n";
    lista->showList();
    cout << endl;

    Nodo *solucion = new Nodo();
    //solucion->tour[0] = 99;
    //solucion->showTour();
    cout << "\n\n Checando si hay uno diferente\n";
    lista->checkTours(solucion);

    cout << "\n\n Volviendo a mostrar la lista\n";
    lista->showList();

    
    
    
    return 0;
}