/* function evaluation class*/

#include<iostream>
//#include <boost/random.hpp>
//#include <random>
#include <ctime>
#include <cstdint>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>

using namespace std;

class eval
{
private:
    float max_speed;
    float min_speed;
    unsigned long weight;
    /*
    unsigned long ganancia;
    double tiempo0, tiempo1;
    */
    Nodo* aux;
    Nodo *n2;
    vector<Nodo*> VEC;

public:
    eval(int, int);
    ~eval();

    //Methods
    Nodo* evaluateFX(Nodo*&, vector<int>, vector<short int>, int, int, int, float *, double, double, unsigned long, unsigned long**, vector<vector<int> >);
};

eval::eval(int ncities, int nitems)
{
    this->max_speed = 1.0;
    this->min_speed = 0.1;
    this->weight = 0;
    this->aux = new Nodo(ncities, nitems);
    this->n2 = new Nodo(ncities, nitems);
}

eval::~eval()
{
}

Nodo* eval::evaluateFX(Nodo*& solution,vector<int> pi, vector<short int>z, int ncities, int nitems, int capacity, float *distances, double time0, double time1 ,unsigned long profit, unsigned long **items, vector<vector<int> > items_in_city)
{

    //Nodo *aux = new Nodo(ncities,nitems);
    if(VEC.size() == 1){ VEC.erase(VEC.begin()); }

    /*if(pi.size() != 280){ 
        cout << "Diferente a 280! - eval" << endl;
        exit(0);
    }*/
    // the values that are evaluated in this function
    this->weight = 0;
    // attributes in the beginning of the tour
    unsigned long weights[ncities];
    // iterate over all possible cities
    for (int i = 0; i < ncities; i++) {
        weights[pi[i]] = 0;
        // for each item index this city
        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
        {
            if (z[*it]) {
                // update the current weight and profit
                this->weight += items[*it][1];
                weights[pi[i]]+= items[*it][1];
                profit += items[*it][0];
            }
            
        }
        // if the maximum capacity constraint is reached
        if (this->weight > (unsigned long)capacity) {
            //cout << "L --- R: Penalizado..\n";
            //cout << "weight: " << this->weight << endl;
            //exit(0);
            //time0 = numeric_limits<double>::max(); // Valor máximo de un double: 1.79769e+308
            time0 = 1797690.0;
            time1 = time0;
            profit = 0.0; // -1
            break;
        }        
        
        //cout << "pi size: " << pi.size() << endl;
        //exit(0);
        // update the speed accordingly
        double speed = max_speed - ((double) weight / capacity) * (max_speed - min_speed);
        if (i == ncities-1)
            time0 += (double) distances[pi[i] * ncities + pi[0]] / speed;
        else
            time0 += (double) distances[pi[i] * ncities + pi[i + 1]] / speed;
    }
    

    this->weight = 0;
    time1 = (double) distances[pi[0] * ncities + pi[ncities-1]];
    //cout << pi[0] << " - ";
    
    //cout << "time1 evaluate-def: " << time1 << endl;
    //cout << "\n\n";
    for (int i = ncities-1; i >0; --i) {
        this->weight +=  weights[pi[i]]; 
        double speed = max_speed - ((double) this->weight / capacity) * (max_speed - min_speed);
        time1 += (double) distances[pi[i] * ncities + pi[i - 1]] / speed;

        // if the maximum capacity constraint is reached
        if (this->weight > (unsigned long)capacity) {
            //cout << "R --- L: Penalizado..\n";
            //cout << "weight: " << this->weight << endl;
            //exit(0);
            //time0 = numeric_limits<double>::max();
            time0 = 1797690.0;
            time1 = time0;
            profit = 0.0; // -1
            break;
        }
        
        
    }

    //cout << "weight: " << this->weight << endl;
            
    // profit and packing
    aux->setPacking(z);
    aux->profit = profit;
    
    // Select the best time
    if(time0 <= time1){
        aux->time = time0;
        aux->setTour(pi);
        //cout << "Tour NORMAL\n";
        //cout << "left to right\n";
    }else{ // inverse tour
        aux->time = time1;
        //cout << "inverse tour\n";
        aux->setTour(aux->getInverseTour(pi));
        //cout << "Tour inverso\n";
    }

    //cout << "\n final evaluateFX \n";
    solution = solution->getAll(aux); 
    //solution = aux;

    
    return solution;
    
}


//  g++ -Wall -g write.cpp -o write
