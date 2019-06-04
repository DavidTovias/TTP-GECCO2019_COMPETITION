#include <random>
#include <iostream>
int main()
{
  /* Initialise. Do this once (not for every
     random number). */
  std::random_device rd;
  std::mt19937_64 gen(rd());

  /* This is where you define the number generator for unsigned long long: */
  //std::uniform_int_distribution<unsigned long long> dis;

  /* A few random numbers: */    
  for (int n=0; n<100; ++n)
    std::cout << (1 + gen() % 3) << ' ';
  std::cout << std::endl;
  std::cout << std::mt19937::max() << std::endl;
  std::cout << std::mt19937_64::max();
  return 0;
}

