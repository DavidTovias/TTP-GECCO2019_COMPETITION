#include <iostream>
#include <random>

class time_TTPSolver
{
private:
    /* data */
public:
    Nodo *solution;
    double lessTime;
    int ncities;
    int nitems;
    time_TTPSolver(double, Nodo*, int, int);
    ~time_TTPSolver();


    void RLS(int*, short int *, int, int, int, float *, double, double, unsigned long, unsigned long**, vector<vector<int> >); // Random Local Search
};

time_TTPSolver::time_TTPSolver(double lessTime, Nodo *solution, int ncities, int nitems)
{
    this->lessTime = lessTime;
    this->ncities = ncities;
    this->nitems = nitems;

    this->solution = new Nodo(ncities, nitems);

    this->solution->time = solution->time;
    this->solution->profit = solution->profit;

    this->solution->setTour(solution->getTour());
    this->solution->setPacking(solution->getPacking());
    
}

time_TTPSolver::~time_TTPSolver()
{
}

void time_TTPSolver::RLS(int *pi, short int *optPlan, int ncities, int nitems, int capacity, float* distances, double time0, double time1, unsigned long profit, unsigned long **items, vector<vector<int> > items_in_city){
    
    

    

    
    // nonDominated object
    nonDominated* sol = new nonDominated(ncities, nitems);
    // permutation object
    permutation *perMutation = new permutation();

    // init solution with optimal tour
    for(int i = 0; i < ncities; i++){
        pi[i] = optimal_tour[i];
        cout << pi[i] << " ";
    }

    
    ////////////////////////////
    // other solution with optimal tour an optimal plan added to nonDominated set
    
    // evaluation of function
    eval *evaluate = new eval(ncities, nitems); // Create an eval instance
    //eval *evalOpt = new eval(ncities, nitems);
    Nodo *optPlan_and_tour = new Nodo(ncities, nitems);
    
    cout << "pi -----------------------\n ";
    for (int i = 0; i < ncities; i++)
    {
        cout << pi[i] << " ";
    }
    cout << " -----------------------lal\n\n ";
    


    optPlan_and_tour = evaluate->evaluateFX(optPlan_and_tour, this->pi, optPlan, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
    cout << "\nprint all\n";
    optPlan_and_tour->printAll();

    
    sol->addSolution(optPlan_and_tour); // add to COP

    Nodo *solution = new Nodo(ncities, nitems); // solution Node (init solution)
    solution = optPlan_and_tour;
    
    
    
    // ***************** At this point we already have the first solution ******************

    cout << "We have the first solution\n";

    int counter = 0;
    
    int prob;
    int takeSol;
    Nodo *solutionPrime = new Nodo(ncities, nitems);
    int mutate;
    Nodo *GreedyBest = new Nodo(ncities, nitems); // greedy solution    
    Nodo * aux = new Nodo(ncities, nitems);
    int nonD = 0, dominates = 0, dominated = 0, t_count = 0;
    int BL_Z = 0;
    int BL_CITIES = 2;
    while(t_current > 5.0){ // Temperature  

        // generate new solution
        mutate = perMutation->rndint(1,10);
        if(mutate <= 9){
            perMutation->block_reverse(ncities,this->pi); // made on this->pi
        }else{
            perMutation->vertex_insert(ncities, this->pi);
        }
        
        // Regresar Z = [0,,,0];
        for (int i = 0; i < nitems; i++)
        {
            z[i] = 0;
        }

        mutate = perMutation->rndint(1,3);
        if(mutate > 5){
            exit(0);
            for (int j = 0; j < nitems; ++j){ // Random packing plan
                prob = perMutation->rndint(0,10); // = 0;
                z[j] = (short int) 0; //rndint(0,1);
                if (prob >= 10){ z[j] = 1;}
            }
        }else{
            if(BL_Z == 0){
                for (int i = 0; i < ncities; i++) // Seleccionar ciudades aleatoriamente
                {   
                    mutate = perMutation->rndint(1,10);
                    if(mutate >= 9){ // 10% de las ciudades
                        for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
                        {
                            prob = perMutation->rndint(1,10); // = 0;
                            z[*it] = (short int) 0; //rndint(0,1);
                            if (prob > 5){ z[*it] = 1;}
                        }
                    }
                }
                /*for (int i = ncities-1; i >= ncities-(ncities/BL_CITIES); i--)
                {   
                    for (std::vector<int>::iterator it = items_in_city[pi[i]].begin() ; it != items_in_city[pi[i]].end(); ++it)
                    {
                        prob = perMutation->rndint(1,10); // = 0;
                        z[*it] = (short int) 0; //rndint(0,1);
                        if (prob >= 8){ z[*it] = 1;}
                    }
                }*/
            }

        }
        
        if(BL_CITIES == 6) { BL_CITIES = 2; }
        else{ BL_CITIES += 2; }

        
        
        
        // evaluation of function
        if(BL_Z == 0){
            solutionPrime = evaluate->evaluateFX(solutionPrime, this->pi, z, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
            //BL_Z = 1;
        }else{
            exit(0);
            solutionPrime = evaluate->evaluateFX(solutionPrime, this->pi, optPlan, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);    
            BL_Z = 0;
        }
                
        if(solution->compareSolution(solutionPrime) == 0 ) // nonDominated solutions
        {
            // add solution
            nonD++;
            nonD++;
            sol->addSolution(solution);
            sol->addSolution(solutionPrime);

            sol->addAll(solution);
            sol->addAll(solutionPrime);
            
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
            sol->addAll(solutionPrime);
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
                //exit(0);
                //prob = (int) perMutation->rndint(0,10); // probability;
                
                
                p = exp(-1/this->t_current);
                //cout << "p: " << p << endl;
                cout << "t_current: " << t_current << endl;
                
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
    ////////////////////////////////8
    
    
    delete [] this->pi;
    delete [] this->z;
    delete solution;
    //delete solutionPrime;
    //delete GreedyBest;
    delete perMutation;
    delete evaluate;

    /*cout << "\n All Solutions \n\n";
    for(int i = 0; i< sol->AllSol.size(); i++){
        cout << "time: " << sol->AllSol[i]->time << "  profit: " << sol->AllSol[i]->profit << endl;
    }

    cout << "TOTAL: " << sol->AllSol.size() << endl;

    exit(0);*/
    
    return sol->solutions();
    /*permutation *mutation = new permutation();
    eval *evaluate = new eval(ncities, nitems);
    int mutate;
    Nodo *SP = new Nodo(ncities, nitems);

    while(this->solution->time >= 7492.00){
        mutate = mutation->rndint(1,10);
        if(mutate <= 1){
            mutation->block_reverse(ncities, pi); // made on this->pi
        }else{
            mutation->vertex_insert(ncities, pi);
        }

        SP = evaluate->evaluateFX(SP, pi, optPlan, ncities, nitems, capacity, distances, time0, time1,profit, items, items_in_city);
        
        //exit(0);
        if(SP->time <= this->solution->time){ // SP dominates 
            this->solution = SP;
        }
        cout << "\n" << this->solution->time << "\n";
        cout << "\n" << this->solution->profit << "\n";
    }*/
}
