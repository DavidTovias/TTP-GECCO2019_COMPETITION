#include<iostream>
#include<boost/random.hpp>
#include <ctime>

using namespace std;

//Prototypes
double randreal(void);
int rndint(int, int);


std::time_t now = std::time(0);
boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};

int main(int argc, char const *argv[])
{
    int r = rndint(1,2);
    cout << "r " << r << endl;

    
    return 0;
}


double randreal(void)
{
    double result = ( (double) gen() );
    result /= boost::random::mt19937::max();
    
    return (result);
}

int rndint(int lo, int hi){
    return (int)(lo + randreal() * (hi - lo + 1));
}
