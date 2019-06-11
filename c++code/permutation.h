#include <random>
#include<iostream>
#include <ctime>
#include <cstdint>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>

using namespace std;
class permutation
{
private:
    
public:

    vector<int> aux;
    permutation();
    ~permutation();


    //Methods
    int * init_permutation(int);

    vector<int> block_reverse(int, vector<int>);
    
    vector<int> vertex_insert(int, vector<int>);

    double randreal(void);
    int rndint(int, int);

    vector<short int> knapsack_dp(vector<unsigned long>, vector<unsigned long>, unsigned long, int);

};


permutation::permutation()
{
    
    
}

permutation::~permutation()
{
}

vector<short int> permutation::knapsack_dp(vector<unsigned long> wt, vector<unsigned long> val, unsigned long W, int n)
{
    unsigned long i, w;
    unsigned long K[n+1][W+1]; 
  
    // Build table K[][] in bottom up manner 
    for (i = 0; i <= (unsigned long)n; i++) 
    { 
       for (w = 0; w <= W; w++) 
        { 
            if (i==0 || w==0) 
               K[i][w] = 0; 
            else if (wt[i-1] <= w) 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
            else
                 K[i][w] = K[i-1][w]; 
        }
   }


    vector<short int> z; //size n, last indez is the maximum z[n+1]
    unsigned long p = n-1; // indice del vector z

    //initialize z
    for(i=0; i<(unsigned long)n; i++){
        z.push_back(0);
    }

    unsigned long ki=W; // para el último elemento
    for(i=n; i>0; i--){
        if(K[i][ki] == K[i-1][ki]){ // Si es igual al de arriba
            p--;
            continue;
        }else{            
            z[p] = 1;
            ki -= wt[i-1];
            p--;
        }
    }

    return z;
}



int * permutation::init_permutation(int n){
    int *perm = new int[n];

    for (int i = 0; i < n; ++i)
        perm[i] = i;

    return perm;
}


// Block reverse ASA-GS
vector<int> permutation::block_reverse(int ncities, vector<int> pi)
{

    int i, j, _min, _max;
    do{
        i = rndint(0,ncities-1);
        j = rndint(0,ncities-1);
    }while(i == j);
    
    _min = min(i,j);
    _max = max(i,j);
    
    i = _min + 1;
    j = _max - 1;
    
    int tam = _max - _min - 1;
    

    // asignar los valores a aux (reverse)
    for(int ind = 0; ind < tam; ind++){
        aux.push_back(pi[j]);
        j--;
    }

    
    // Asignar a pi los valores invertidos de aux
    for(int ind= 0; ind<tam ;ind++)
    {
        pi[i] = aux[ind];
        i++;
    }

    aux.clear();
    
    return pi;

}


vector<int> permutation::vertex_insert(int ncities, vector<int> pi)
{
    int i, j, _min, _max, tmp;
    // Select random cities
    do{
        i = rndint(1,ncities-1);
        j = rndint(1,ncities-1);
    }while(i == j);

    _min = min(i,j);
    _max = max(i,j);

    tmp = pi[_max];

    for(i = _max; i > _min; i--){
        pi[i] = pi[i-1];
    }

    pi[_min] = tmp;


    return pi;

}


double permutation::randreal(void)
{       
    std::random_device rd;
    std::mt19937_64 gen(rd());
    //std::uniform_int_distribution<unsigned long long> dis;
    double result = ((double) gen());
    result /= (double) std::mt19937_64::max();
    //result /= boost::random::mt19937::max();
    
    return (result);
}



int permutation::rndint(int lo, int hi){
    
    return (int)(lo + randreal() * (hi - lo + 1));
    //return (lo + dis(gen) % hi);
}
