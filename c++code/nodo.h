#include<iostream>
#include<vector>
//#include <boost/random.hpp>
#include <random>


using namespace std;

class Nodo{

    private:
        
    public:
        Nodo(); // Constructor
        Nodo(int max_cities, int max_items);
        Nodo(const Nodo &);
        ~Nodo();
        int* tour;
        int* pi_aux;
        short int * packing;
        double time;
        unsigned long profit;

        int ncities;
        int nitems;
        //Nodo *aux;
        Nodo *aux;

        vector<Nodo*> vec;
        int ban = 0;

        // Methods
        void setTour(int*);
        void setPacking(short int*);
        int* getInverseTour(int*);
        void showTour();
        void showPacking();
        bool equalsTour(Nodo*);
        bool equalsPacking(Nodo*);
        int * getTour();
        short int * getPacking();
        int compareSolution(Nodo*);
        Nodo * getAll(Nodo *, Nodo*);
        void printAll();

        void initialize();
};



Nodo::Nodo(int max_cities, int max_items)
{
    //this->ban = 0;

    this->ncities = max_cities;
    this->nitems = max_items;

    this->profit = 0;
    //time = numeric_limits<double>::max();
    time = 1797690.0;
    tour = new int[max_cities];
    packing = new short int[max_items];

    for(int i = 0; i < ncities; i++)
    {
        tour[i] = i;
    }

    for(int i = 0; i < nitems; i++)
    {
        packing[i] = 0;
    }

    this->pi_aux = (int *) malloc(this->ncities*sizeof(int));
    
}


Nodo::Nodo(const Nodo &n2)
{
    this->profit = n2.profit;
    //time = numeric_limits<double>::max();
    time = 1797690.0;
    tour = new int[MAXCITIES];
    packing = new short int[MAXITEMS];  
}

Nodo::Nodo()
{
    profit = 0;
    //time = numeric_limits<double>::max();    
    tour = new int[MAXCITIES];
    packing = new short int[MAXITEMS];  
}

Nodo::~Nodo()
{
    cout << "Nodo eliminado!\n";
}

// show this-node tour
void Nodo::showTour(){
    int i;
    for(i = 0; i < this->ncities; i++)
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

void Nodo::setTour(int* _pi){
    for(int i = 0; i < this->ncities; i++){
        this->tour[i] = _pi[i];
    }
}

void Nodo::setPacking(short int* _z){
    for(int i = 0; i < this->nitems; i++){
        this->packing[i] = _z[i];
    }
}


int * Nodo::getInverseTour(int *pi){
    pi_aux[0] = pi[0];
    for(int i = this->ncities-1, j=1; i > 0; i--,j++){
        pi_aux[j] = pi[i];
    }

    return pi_aux;
}

int * Nodo::getTour(){
    return this->tour;
}

short int * Nodo::getPacking(){
    return this->packing;
}

// 1 if dominates, 0 non-dominated, -1 dominated or equal
int Nodo::compareSolution(Nodo* n){

    if(this->time == n->time && this->profit == n->profit)
    {
        //cout << "this->time: " << this->time << "  this->profit: " << this->profit << endl;
        //cout << "n->time: " << this->time << " this->profit: " << this->profit << endl;
        if(this->equalsTour(n)){
            if(this->equalsPacking(n)){
                return -1;
            }else { 
                //cout << "\nEntrando a equalsPacking else\n";
                return 0; 
            }
        }else {
            //cout << "\nEntrando a equalsTour else\n"; 
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
        //cout << "\nelse final \n";
        return 0;
    }
    
}

void Nodo::initialize(){
    this->aux = new Nodo(ncities, nitems);
    this->ban = 19;
}

Nodo* Nodo::getAll(Nodo *n, Nodo* au){
    Nodo *aux = new Nodo(ncities, nitems);

    aux->setTour(n->getTour());
    aux->setPacking(n->packing);
    aux->profit = n->profit;
    aux->time = n->time;

    return aux;
    /*if(vec.size() == 1){
        vec.erase(vec.begin());
    }
    vec.push_back(n);
    cout << "size: " << vec.size() << endl;
    //return vec[0];

    cout << ".........................\n";

    cout << "aux->time: " << aux->time << "  aux->profit: " << aux->profit << "\n";
    cout << "vec[0]->time: " << vec[0]->time << "  vec[0]->profit: " << vec[0]->profit << "\n";

    cout << ".........................\n";

    return aux;*/
    
}

void Nodo::printAll(){

    cout << "Tour: ";
    this->showTour();
    cout << "  Plan:  ";
    this->showPacking();
    cout << "\tTime: " << this->time << "\tProfit: " << this->profit;
    cout << endl;
    
}

