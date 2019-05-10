#include<iostream>
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>

class permutation
{
private:
    
public:

    permutation();
    ~permutation();

    // random generator
    std::time_t now = std::time(0);
    boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};

    //Methods
    int * init_permutation(int);
    int * gen_permutation(int*, int);
    void block_reverse(int, int*&);
    void vertex_insert(int, int*&);

    double randreal(void);
    int rndint(int, int);

};

permutation::permutation()
{

}

permutation::~permutation()
{
}



int * permutation::init_permutation(int n){
    int *perm = new int[n];

    for (int i = 0; i < n; ++i)
        perm[i] = i;

    //gen_permutation(perm, n);
    return perm;
}


int * permutation::gen_permutation(int *perm, int n){
    // Fisher-Yates shuffling algorithm    
    for (int i = n-1; i > 0; --i){
        //generate a random number [0, n-1]
        int j = 1 + this->gen() % i;
        //swap the last element with element at random index
        int temp = perm[i];
        perm[i] = perm[j];
        perm[j] = temp;
    }
    return perm;
}

// Block reverse ASA-GS
void permutation::block_reverse(int ncities, int* &pi)
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
    int * aux = new int[tam];

    // asignar los valores a aux (reverse)
    for(int ind = 0/*, rev = j*/; ind < tam; ind++/* , rev--*/){
        aux[ind] = pi[j];//pi[rev];
        j--;
        //cout << "aux[i]: " << aux[ind] << " ";
    }
    //cout << endl;
    
    // Asignar a pi los valores invertidos de aux
    for(int ind= 0/*, t= i*/; ind<tam ;ind++/* , t++*/)
    {
        /*pi[t]*/
        pi[i] = aux[ind];
        i++;
    }

    delete[] aux;

}


void permutation::vertex_insert(int ncities, int* &pi)
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
    //cout << "min: " << _min << "   Max: " << _max << endl;

    for(i = _max; i > _min; i--){
        pi[i] = pi[i-1];
    }

    pi[_min] = tmp;
    

}

double permutation::randreal(void)
{
    double result = ((double) this->gen());
    result /= boost::random::mt19937::max();

    return (result);
}



int permutation::rndint(int lo, int hi){
    return (int)(lo + randreal() * (hi - lo + 1));
}






/*

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
    int * aux = new int[tam];

    // asignar los valores a aux (reverse)
    for(int ind = 0, rev = j; ind < tam; ind++, rev--){
        aux[ind] = pi[rev];
        //cout << "aux[i]: " << aux[ind] << " ";
    }
    //cout << endl;
    
    // Asignar a pi los valores invertidos de aux
    for(int ind= 0, t= i; ind<tam ;ind++,t++)
    {
        pi[t] = aux[ind];
    }

    delete[] aux;

*/