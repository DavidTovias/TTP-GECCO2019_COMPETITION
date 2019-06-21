
//#include <random>
#include<iostream>
#include <ctime>
#include <cstdint>
#include<iomanip>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>
//#include "permutation.h"


using namespace std;

class simulatedAnnealing
{
private:
    
    //int *pi;
    vector<int> pi;
    //short int *z;
    vector<short int> z;
    
    double time0;
    double time1;
    unsigned long profit;
    unsigned long CAPACIDAD; // Capacidad por ciudad

    /* SA Parameters */
    double p; // probability
    double t_start;
    double t_end;
    double t_current;
    double alpha;
    double beta;
    
    double t_cool;
    double t_greedy;
    double t_v;

    int G;


public:

    //Constructor
    simulatedAnnealing(int, int);
    ~simulatedAnnealing();

    // sa method
    vector<Nodo*> sa_algorithm(vector<int>, int*,int, int, int, float *, unsigned long **, vector<vector<int> >);
    
};


//Constructor
simulatedAnnealing::simulatedAnnealing(int ncities, int nitems)
{
    this->t_start = 350;
    this->t_end = 0.0025;
    this->t_current = this->t_start;
    this->alpha = 1600;
    this->beta = 0.333333;
    
    
    this->t_cool = 0.999; 
    this->t_greedy = 100; 

    this->G = 0;

    switch (nitems)
    {
    case 279:
        CAPACIDAD = 1619UL;
        break;
    case 1395:
        CAPACIDAD = 5035UL;
        break;
    case 2790:
        CAPACIDAD = 7830UL;
        break;
    
    case 4460:
        CAPACIDAD = 1549UL;
        break;
    case 22300:
        CAPACIDAD = 5035UL;
        break;
    case 44600:
        CAPACIDAD = 7870UL;
        break;
    
    case 33809:
        CAPACIDAD = 1547UL;
        break;
    case 169045:
        CAPACIDAD = 5030UL;
        break;
    case 338090:
        CAPACIDAD = 7890UL;
        break;

    default:
        CAPACIDAD = 2000UL;
        break;
    }


}

simulatedAnnealing::~simulatedAnnealing()
{
    cout << "simuleatedAnnealing obj deleted!\n";
}


vector<Nodo*> simulatedAnnealing::sa_algorithm(vector<int> optimal_plan, int* optimal_tour,int ncities, int nitems, int capacity, float *distances, unsigned long **items, vector<vector<int> > items_in_city)
{    

    // Se inicializa z con 0
    for (int i = 0; i < nitems; i++){
        z.push_back(0);
    }

    // Se inicializa pi con -1
    for (int i = 0; i < ncities; i++)
    {
        this->pi.push_back(-1); // initialize pi
    }

    // Se inicializa optPlan con 0, tendrá los items del plan optimo
    vector<short int> optPlan;
    for (int i = 0; i < nitems; ++i){
        optPlan.push_back(0);
    }

    // profit, time0 and time1
    this->profit = 0.0;
    this->time0 = 0.0;
    this->time1 = 0.0;
    
    cout<<ncities<<" "<< nitems << " " <<capacity <<endl;
    
    // nonDominated object
    nonDominated* sol = new nonDominated(ncities, nitems);
    // permutation object
    permutation *perMutation = new permutation();
    // init solution with optimal tour
    for(int i = 0; i < ncities; i++){
        this->pi[i] = optimal_tour[i];
        cout << this->pi[i] << " ";
    }
    
    
    ////////////////////////////
    
    // SOLUCION CON EL TOUR Y PLAN ÓPTIMOS
    
    // evaluation of function
    eval *evaluate = new eval(ncities, nitems); // Create an eval instance
    Nodo *optPlan_and_tour = new Nodo(ncities, nitems);
    
    cout << "seg\n";
    // select the best items
    for (int i = 0; i < ncities; i++)
    {
        for (std::vector<int>::iterator it = items_in_city[this->pi[i]].begin() ; it != items_in_city[this->pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan.size(); k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    optPlan[optimal_plan[k]] = (short int)1;
                    //cout << *it << " ";
                }
            }
        }
    }

    optPlan_and_tour = evaluate->evaluateFX(optPlan_and_tour, this->pi, optPlan, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\nprint all\n";
    //optPlan_and_tour->printAll();
    sol->addSolution(optPlan_and_tour); // add to COP
    
    

    // TOUR ÓPTIMO CON LOS ITEMS EN LA SEGUNDA MITAD DEL PLAN ÓPTIMO
    Nodo *optTour_lastItems = new Nodo(ncities, nitems);
    
    size_t optimal_plan_size = optimal_plan.size();
    for (int i = ncities-1; i >= ncities/2; i--)
    {
        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan_size; k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    z[*it] = 1;
                    //cout << *it << " ";
                }   
            }
        }
    }

    optTour_lastItems = evaluate->evaluateFX(optTour_lastItems, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\n\n";
    //optTour_lastItems->printAll();
    sol->addSolution(optTour_lastItems);

    
    // Regresar Z = [0,,,0];
    for (int i = 0; i < nitems; i++)
    {
        z[i] = 0;
    }
    

    // TOUR ÓPTIMO CON LOS ITEMS EN LA PRIMERA MITAD DEL PLAN ÓPTIMO
    Nodo *optTour_firstItems = new Nodo(ncities, nitems);
    for (int i = 0; i <= ncities/2; i++)
    {
        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan_size; k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    z[*it] = 1;
                    //cout << *it << " ";
                }   
            }
        }
    }
    optTour_firstItems = evaluate->evaluateFX(optTour_firstItems, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\n\noptTour_firstItems\n";
    //optTour_firstItems->printAll();
    sol->addSolution(optTour_firstItems);


    fill(begin(z),end(z),0); // regresar a z

    // TOUR ÓPTIMO CON NINGÚN ITEM SELECCIONADO (GANANCIA CERO)
    Nodo *solution = new Nodo(ncities, nitems); // solution Node (init solution)
    cout << " despues de Nodo \n";
    solution = evaluate->evaluateFX(solution, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    solution->printAll();

    
    // ***************** At this point we already have three solution ******************

    cout << "We have the first solution\n";

    int counter = 0;

    //int prob;
    int takeSol;
    Nodo *solutionPrime = new Nodo(ncities, nitems);
    int mutate;
    Nodo *GreedyBest = new Nodo(ncities, nitems); // greedy solution    
    //Nodo * aux = new Nodo(ncities, nitems);
    int nonD = 0, dominates = 0, dominated = 0, t_count = 0;
    
    
    
    vector<unsigned long> peso;
    vector<unsigned long> ganancia;
    vector<int> objetos;
    vector<short int> knp;
    
    unsigned long peso_total = 0;
    
    while(t_current > 5.0){ // Temperature  

        peso_total = 0;
        
        // generate new solution
        mutate = perMutation->rndint(1,10);
        if(mutate <= 9){
            this->pi = perMutation->block_reverse(ncities,this->pi); // made on this->pi
        }else{
            this->pi = perMutation->vertex_insert(ncities, this->pi);
        }
        
        // Regresar Z = [0,,,0];
        /*for (int i = 0; i < nitems; i++)
        {
            z[i] = 0;
        }*/

        fill(begin(z),end(z),0);

        /*for (size_t i = 0; i < nitems; i++)
        {
            mutate = perMutation->rndint(1,10);
            if(mutate == 10){
                z[i] = (short int) 1;
            }
        }*/

        
        for (int i = ncities-1; i >= ncities-(ncities/6); i--) // Seleccionar ciudades aleatoriamente
        {   
            mutate = perMutation->rndint(1,10);
            if(mutate > 8){ // 20%
                for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
                {
                    ganancia.push_back(items[*it][0]);
                    peso.push_back(items[*it][1]);
                    peso_total += items[*it][1];

                    objetos.push_back(*it);
                }
                
                if(peso_total > (unsigned long)capacity){  // Se viola la restricción de peso
                    peso_total = 0;
                    // Se eliminan todos los elementos
                    peso.clear();
                    ganancia.clear();
                    objetos.clear();
                    knp.clear();
                    break; 
                }
            

                knp = perMutation->knapsack_dp(peso, ganancia, CAPACIDAD, peso.size());

                for (int j = 0; j < knp.size(); j++)
                {   
                    if(knp[j] == 1){
                        z[objetos[j]] = (short int)1;
                    }
                }
                
                // Se eliminan todos los elementos
                peso.clear();
                ganancia.clear();
                objetos.clear();
                knp.clear();
            }// end if
        }// end for
        
        
        // evaluation of function
        solutionPrime = evaluate->evaluateFX(solutionPrime, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
            
        
                
        if(solution->compareSolution(solutionPrime) == 0 ) // nonDominated solutions
        {
            // add solution
            nonD++;
            nonD++;
            sol->addSolution(solution);
            sol->addSolution(solutionPrime);

            //sol->addAll(solution);
            //sol->addAll(solutionPrime);
            
            //solution = solution->getAll(solutionPrime);
            solution = solutionPrime;

            counter++;
            counter++;
            this->G = 0;
        }
        else if( solution->compareSolution(solutionPrime) == -1 )
        {   
            //SP DOMINATES S
            dominated++;
            
            //solution = solution->getAll(solutionPrime);
            // add solutionPrime
            sol->addSolution(solutionPrime);
            solution = solutionPrime;
            
            
            
            
            
            //sol->addAll(solutionPrime);
            this->G = 0;
            counter++;
        }else // greedy search  (S DOMINATES SP)
        {
            //cout << "s dominates sp!\n";
            this->G++;
            dominates++;
            if(GreedyBest->compareSolution(solutionPrime) == -1  ||  GreedyBest->compareSolution(solutionPrime) == 0)
            {
                //GreedyBest = GreedyBest->getAll(solutionPrime);
                GreedyBest = solutionPrime;
                
            }
            
            if(this->G >= this->t_greedy){
                cout << "G is complete! ---------------------------------------------------\n";
                
                p = exp(-1/this->t_current);
                //cout << "t_current: " << t_current << endl;
                
                if(p >= 0.5){ // (add greedyBest, let solution = greedySolution)
                    
                    //sol->addSolution(GreedyBest);
                    //solution = solution->getAll(GreedyBest);

                    solution = GreedyBest;
                    
                    counter++;
                    this->G = 0;

                    for(int i = 0; i < ncities; i++)
                    {
                        this->pi[i] = solution->tour[i];
                    }
        
        
                    t_current *= t_cool;
                    t_count++;
                    continue;
                    
                    
                }
            }
            for(int i = 0; i < ncities; i++)
            {
            this->pi[i] = GreedyBest->tour[i];
            }
            continue;
        }
        
        // Take randomly a solution from pareto optimal set
        if(sol->SOL.size() > 1){
            takeSol = perMutation->rndint(0, sol->SOL.size()-1);
            //solution = solution->getAll(sol->SOL[takeSol], solution);
            solution = sol->SOL[takeSol];
        }

        /*if(sol->AllSol.size() > 1){
            takeSol = perMutation->rndint(0, sol->AllSol.size()-1);
            //solution = solution->getAll(sol->SOL[takeSol], solution);
            solution = sol->AllSol[takeSol];
        } */  
        
        

        for(int i = 0; i < ncities; i++)
        {
            this->pi[i] = solution->tour[i];
        }
        
        
        t_current *= t_cool;//0.8;// update T
        t_count++;
        cout << "T_current: " << t_current << endl;

    }


    cout << "\n\n TERMINA SIMULATED ANNEALING\n";
    cout << "nonDominated times: " << nonD << endl;
    cout << "dominated times: " << dominated << endl;
    cout << "dominates times: " << dominates << endl;
    cout << "SUM: " << (nonD + dominated + dominates) << endl;
    cout << "t_counter: " << t_count << endl;
    cout << "no. de nodos: " << counter << endl;

    cout << endl;
    ////////////////////////////////
    
    
    //delete [] this->pi;
    //delete [] this->z;
    solution = NULL;
    solutionPrime = NULL;
    GreedyBest = NULL;
    delete solution;
    delete solutionPrime;
    delete GreedyBest;
    delete perMutation;
    delete evaluate;


    
    return sol->solutions();

}
