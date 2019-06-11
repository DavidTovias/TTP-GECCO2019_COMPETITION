#include<iostream>
#include "nodo.h"

using namespace std;

class nonDominated
{
private:
    int ncities;
    int nitems;
public:
    nonDominated(int, int);
    ~nonDominated();
    vector<Nodo*> SOL;
    vector<Nodo*> AllSol;

    // Methods
    void addSolution(Nodo*);
    void addAll(Nodo*);
    vector<Nodo*> solutions();
};

nonDominated::nonDominated(int ncities, int nitems)
{
    this->ncities = ncities;
    this->nitems = nitems;
}

nonDominated::~nonDominated()
{
}

void nonDominated::addSolution(Nodo* solution)
{
    int add = 1;
    
    // add solution
    for(size_t i = 0; i < SOL.size(); i++)
    {           
        if(solution->compareSolution(SOL[i]) == 1){
            SOL.erase(SOL.begin()+i);
        }
        if(solution->compareSolution(SOL[i]) == -1){
            add = 0;
            break;
        }
    }
    
    if(add == 1) { SOL.push_back(solution); }

}


// Add all solution, if are equal that solution is not added
void nonDominated::addAll(Nodo* solution)
{
    int add = 1;
    // add solution
    for(size_t i = 0; i < AllSol.size(); i++)
    {   
        if(solution->time == AllSol[i]->time && solution->profit == AllSol[i]->profit){
            if(solution->equalsTour(AllSol[i])){
                if(solution->equalsPacking(AllSol[i])){
                    add = 0;
                    break;
                }
            }   
        }
    }
    
    if(add == 1) {  AllSol.push_back(solution); }

}

vector<Nodo*> nonDominated::solutions(){
    return this->SOL;
}