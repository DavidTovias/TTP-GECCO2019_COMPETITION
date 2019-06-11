//#include <boost/random.hpp>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdint>
#include <stdlib.h>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>

#define MAXCITIES 33810
#define MAXITEMS  338090

//#include "nodo.h"
#include "nonDominated.h"
#include "readFile.h"
#include "eval.h"
#include "permutation.h"

#include "simulatedAnnealing4.h"
#include "writeInFile.h"

using namespace std;


int main(int argc, char const *argv[])
{   

    int MAXIMUM; // MAXIMUM NUMBER OF SOLUTIONS

    // Save the distance matrix
    cout << argv[1] << endl;
    readFile *fileData = new readFile(argv[1], argv[2], argv[3]);
    cout << "Despues de constructor\n";
    float *distanceMatrix = fileData->getDistances();

    int ncities = fileData->getNcities();
    int nitems = fileData->getNitems();
    int capacity = fileData->getCapacity();
    int * optimal_Tour;
    optimal_Tour = fileData->getOptimalTour();
    cout << "\n optimal tour \n";
    /*for(int i = 0; i < ncities; i++)
    {
        cout << optimal_Tour[i] << " ";
    }*/
    
    // Know the number of non-dominated solutions
    switch(ncities){
        case 280:
            MAXIMUM = 100;
            break;
        case 4461:
            MAXIMUM = 50;
            break;
        case 33810:
            MAXIMUM = 20;
            break;
        case 4:
            MAXIMUM = 10;
            break;
    }
    
    cout << "MAXIMUM number of solutions " << MAXIMUM << endl;
    cout << "ncities " << ncities << endl;
    cout << "nitems " << nitems << endl;
    cout << "capacity " << capacity << endl;

    vector<vector<int> > items_in_city;
    items_in_city = fileData->getItems_in_city();

    unsigned long ** _items;
    _items = fileData->getItems();


    
    /*for (size_t i = 0; i < ncities; i++)
    {
        cout << "Ciudad: " << i << " Objetos: ";
        for (std::vector<int>::iterator it = items_in_city[i].begin() ; it != items_in_city[i].end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }*/
    

    vector<int> optimal_plan = fileData->getOptimalPlan();
    /*for (std::vector<short int>::iterator it = optimal_plan.begin() ; it != optimal_plan.end(); ++it)
    {
        //cout << *it << " ";
    }*/

    // Print all items

    
    vector<Nodo*> ParetoOptimal;
    delete fileData;
    simulatedAnnealing *sa = new simulatedAnnealing(ncities);
    ParetoOptimal = sa->sa_algorithm(optimal_plan, optimal_Tour, ncities, nitems, capacity, distanceMatrix, _items, items_in_city);
    cout << "\n Pareto Optimal - LISTA COMPLETA\n";
    

    for(size_t i = 0; i < ParetoOptimal.size(); i++)
    {
        cout << ParetoOptimal[i]->tour.size() << "  " << ParetoOptimal[i]->packing.size() << endl;
        if(ParetoOptimal[i]->tour.size() != 280){ 
        cout << "Diferente a 280 - main! " << endl;
        //exit(0);
        }
    }

    cout << "\nSoluciones no dominadas: " << ParetoOptimal.size() << endl << endl;
    
    for(int i = 0; i < ParetoOptimal.size(); i++)
    {
        ParetoOptimal[i]->printAll();
    }


    cout << "\n";
    for(int i = 0; i < ParetoOptimal.size(); i++)
    {
        cout << ParetoOptimal[i]->time << " " << ParetoOptimal[i]->profit << endl;
    }
    
    
    writeInFile *write = new writeInFile(ncities, nitems);

    write->write_in_file(ParetoOptimal);
    
    /*for(size_t i = 0; i < 3; i++)
    {
        for(size_t j = 0; j < nitems; j++)
        {
            //cout << p[i][j] << " ";
        }
        //cout << endl;
    }*/
    
    
    
    // print distance matrix
    /*for (int i = 0; i < ncities; ++i)
    {
        for (int j = 0; j < ncities; ++j)
        {
            cout << distanceMatrix[i* ncities + j]<<'\t';
        }
        cout<<endl;
    }*/


    // free space
    delete [] distanceMatrix;
    delete [] _items;
    delete sa;
    //delete write;


    return 0;
}
