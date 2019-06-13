#include<iostream>
#include<vector>
//#include <boost/random.hpp>
//#include <random>


using namespace std;

class Nodo{

    private:
        
    public:
        Nodo(int max_cities, int max_items);
        ~Nodo();
        //int* tour;
        //int* pi_aux;
        vector<int> tour;
        vector<int> pi_aux;
        
        vector<short int> packing;

        double time;
        unsigned long profit;

        int ncities;
        int nitems;
        Nodo *aux;

        vector<Nodo*> vec;
        int ban = 0;

        // Methods
        void setTour(vector<int>);
        void setPacking(vector<short int>);

        vector<int> getInverseTour(vector<int>);

        void showTour();
        void showPacking();
        bool equalsTour(Nodo*);
        bool equalsPacking(Nodo*);
        
        vector<int> getTour();
        vector<short int> getPacking();

        int compareSolution(Nodo*);
        Nodo * getAll(Nodo *);
        void printAll();

};



Nodo::Nodo(int max_cities, int max_items)
{

    this->ncities = max_cities;
    this->nitems = max_items;

    this->profit = 0;
    time = 1797690.0;

    for(int i = 0; i < ncities; i++)
    {
        this->tour.push_back(i); // initialize 
        this->pi_aux.push_back(i); // initialize 

    }

    for(int i = 0; i < nitems; i++)
    {
        this->packing.push_back(0);
    }
    
}


Nodo::~Nodo()
{
    cout << "Nodo eliminado!\n";
}

// show this-node tour
void Nodo::showTour(){
    
    for(int i = 0; i < this->ncities; i++)
    {
        cout << this->tour[i] << " ";
    }
    
}

void Nodo::showPacking(){
    for(int i = 0; i < this->nitems; i++)
    {
        cout << this->packing[i] << " ";
    }
    
}

// true: different, false: equals
bool Nodo::equalsTour(Nodo *n){

    for(int i = 0; i < this->ncities; i++)
    {
        if(this->tour[i] != n->tour[i]){ // Different
            return false;
        }
    }

    return true;
}


bool Nodo::equalsPacking(Nodo *n){
    for(int i = 0; i < this->nitems; i++)
    {
        if(this->packing[i] != n->packing[i]){ // Different
            return false;
        }
    }

    return true;
}

void Nodo::setTour(vector<int> _pi){
    for(int i = 0; i < this->ncities; i++){
        this->tour[i] = _pi[i];
    }
}

void Nodo::setPacking(vector<short int> _z){
    for(int i = 0; i < this->nitems; i++){
        this->packing[i] = _z[i];
    }
}


vector<int> Nodo::getInverseTour(vector<int> pi){
    pi_aux[0] = pi[0];
    for(int i = this->ncities-1, j=1; i > 0; i--,j++){
        pi_aux[j] = pi[i];
    }

    return pi_aux;
}

vector<int> Nodo::getTour(){
    return this->tour;
}

vector<short int> Nodo::getPacking(){
    return this->packing;
}

// 1 if dominates, 0 non-dominated, -1 dominated or equal
int Nodo::compareSolution(Nodo* n){

    if(this->time == n->time && this->profit == n->profit)
    {
        if(this->equalsTour(n)){
            if(this->equalsPacking(n)){
                return -1;
            }else { 
                return 0; 
            }
        }else {
            return 0; 
        }
    }
    else if( this->time <= n->time && this->profit >= n->profit)
    {
        return 1; // this dominates
    }
    else if( this->time >= n->time && this->profit <= n->profit)
    {
        return -1;
    }
    else
    {
        return 0;
    }
    
}


Nodo* Nodo::getAll(Nodo *n){
    Nodo *aux = new Nodo(ncities, nitems);

    aux->setTour(n->getTour());
    aux->setPacking(n->packing);
    aux->profit = n->profit;
    aux->time = n->time;

    return aux;
}

void Nodo::printAll(){

    cout << "Tour: ";
    this->showTour();
    
    cout << "  Plan:  ";
    this->showPacking();
    cout << "\tTime: " << setprecision(15) << fixed << this->time << "\tProfit: " << this->profit;
    cout << endl;
    
}

