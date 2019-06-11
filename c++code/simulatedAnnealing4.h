
//#include <random>
#include<iostream>
//#include <boost/random.hpp>
#include <ctime>
#include <cstdint>

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
    simulatedAnnealing(int);
    ~simulatedAnnealing();

    // sa method
    vector<Nodo*> sa_algorithm(vector<int>, int*,int, int, int, float *, unsigned long **, vector<vector<int> >);
    
};


//Constructor
simulatedAnnealing::simulatedAnnealing(int ncities)
{
    this->t_start = 10000;
    this->t_end = 0.0025;
    this->t_current = this->t_start;
    this->alpha = 1600;
    this->beta = 0.333333;
    
    
    this->t_cool = 0.999; //(this->alpha * pow(ncities,0.5) - 1.0)/(this->alpha * sqrt(ncities));
    this->t_greedy = 100; //this->beta * ncities;
    this->t_v = ncities/10;

    this->G = 0;

    //this->pi = new int[ncities];
    /*for (int i = 0; i < ncities; i++)
    {
        this->pi.push_back(-1); // initialize pi
    }*/
    
    
}

simulatedAnnealing::~simulatedAnnealing()
{
    cout << "simuleatedAnnealing obj deleted!\n";
}


vector<Nodo*> simulatedAnnealing::sa_algorithm(vector<int> optimal_plan, int* optimal_tour,int ncities, int nitems, int capacity, float *distances, unsigned long **items, vector<vector<int> > items_in_city)
{    
    //this->z = new short int[nitems];
    for (int i = 0; i < nitems; i++)
    {
        //z[i] = 0;
        z.push_back(0);
    }

    for (int i = 0; i < ncities; i++)
    {
        this->pi.push_back(-1); // initialize pi
    }

    //short int *optPlan = new short int[nitems];
    vector<short int> optPlan;
    for (int i = 0; i < nitems; ++i)
    {
        //optPlan[i] = 0;
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
    // other solution with optimal tour an optimal plan added to nonDominated set
    
    // evaluation of function
    eval *evaluate = new eval(ncities, nitems); // Create an eval instance
    //eval *evalOpt = new eval(ncities, nitems);
    //Nodo *optPlan_and_tour = new Nodo(ncities, nitems);
    
    cout << "pi -----------------------\n ";
    /*for (int i = 0; i < ncities; i++)
    {
        cout << this->pi[i] << " ";
    }
    cout << " -----------------------lal\n\n ";*/
    
    cout << "seg\n";
    // select the best items
    /*for (int i = 0; i < ncities; i++)
    {
        for (std::vector<int>::iterator it = items_in_city[this->pi[i]].begin() ; it != items_in_city[this->pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan.size(); k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    optPlan[optimal_plan[k]] = 1;
                    //cout << *it << " ";
                }
            }
        }
    }

    optPlan_and_tour = evaluate->evaluateFX(optPlan_and_tour, this->pi, optPlan, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\nprint all\n";
    optPlan_and_tour->printAll();
    */
    
    cout << "\n optPlan_and_tour\n";
    //exit(0);
    

    
    //exit(0);
    //sol->addSolution(optPlan_and_tour); // add to COP
    //sol->addAll(optPlan_and_tour); // add to all solutions
    
    //sol->AllSol[0]->printAll();

    // Tour óptimo con los mejores items de la última mitad
    Nodo *optTour_lastItems = new Nodo(ncities, nitems);
    

    for (int i = ncities-1; i >= ncities/2; i--)
    {
        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan.size(); k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    z[*it] = 1;
                    cout << *it << " ";
                }   
            }
        }
    }

    optTour_lastItems = evaluate->evaluateFX(optTour_lastItems, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\n\n";
    //optTour_lastItems->printAll();
    sol->addSolution(optTour_lastItems);

    cout << "pi: size: " << pi.size() << endl;
    


    // Regresar Z = [0,,,0];
    for (int i = 0; i < nitems; i++)
    {
        z[i] = 0;
    }
    

    // tour óptimo con los mejores items de la primera mitad
   /* Nodo *optTour_firstItems = new Nodo(ncities, nitems);
    for (int i = 0; i <= ncities/2; i++)
    {
        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
        {
            for (int k = 0; k < optimal_plan.size(); k++){ // checar todos los objetos
                if(*it == optimal_plan[k]){
                    z[*it] = 1;
                    cout << *it << " ";
                }   
            }
        }
    }
    evaluate->evaluateFX(optTour_firstItems, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\n\noptTour_firstItems\n";
    optTour_firstItems->printAll();
    sol->addSolution(optTour_firstItems);
    */
    //exit(0);



    ////////////////////////////
   
    // init solution's plan
    /*for (int i = 0; i < nitems; ++i)
    {
        this->z[i] = 0;//perMutation->rndint(0,1); // = 0;
    }
    */


    /*this->pi[0] = 0;
    this->pi[1] = 3;
    this->pi[2] = 2;
    this->pi[3] = 1;

    this->z[0] = 1;
    this->z[1] = 0;
    this->z[2] = 0;*/


    ////////////////////////////////    


    Nodo *solution = new Nodo(ncities, nitems); // solution Node (init solution)
    cout << " despues de Nodo \n";
    solution = evaluate->evaluateFX(solution, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    solution->printAll();
    
    
    
    // ***************** At this point we already have the first solution ******************

    cout << "We have the first solution\n";

    int counter = 0;

    
    
    //int prob;
    int takeSol;
    Nodo *solutionPrime = new Nodo(ncities, nitems);
    int mutate;
    Nodo *GreedyBest = new Nodo(ncities, nitems); // greedy solution    
    //Nodo * aux = new Nodo(ncities, nitems);
    int nonD = 0, dominates = 0, dominated = 0, t_count = 0;
    
    
    //int city1, city2, min_city, max_city; 
    vector<unsigned long> peso;
    vector<unsigned long> ganancia;
    vector<short int> objetos;
    vector<short int> knp;
    //int metodo = 0;
    unsigned long peso_total = 0;
    //int c = 0;
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

        
        for (int i = ncities-1; i >= 0; i--) // Seleccionar ciudades aleatoriamente
        {   
            mutate = perMutation->rndint(1,10);
            if(mutate == 10){ // 90%
                for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
                {
                    ganancia.push_back(items[*it][0]);
                    peso.push_back(items[*it][1]);
                    peso_total += items[*it][1];

                    objetos.push_back((short int)*it);
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
            

                knp = perMutation->knapsack_dp(peso, ganancia, 2000UL, peso.size());

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
            
            solution = solutionPrime;
            
            
            // add solutionPrime

            sol->addSolution(solutionPrime);
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
                //cout << "G is complete! ---------------------------------------------------\n";
                //exit(0);
                //prob = (int) perMutation->rndint(0,10); // probability;
                
                
                p = exp(-1/this->t_current);
                //cout << "p: " << p << endl;
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
        
        
                    t_current *= t_cool;//0.8;// update T
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
    ////////////////////////////////8
    
    
    //delete [] this->pi;
    //delete [] this->z;
    //delete solution;
    //delete solutionPrime;
    //delete GreedyBest;
    delete perMutation;
    delete evaluate;


    
    return sol->solutions();

}

