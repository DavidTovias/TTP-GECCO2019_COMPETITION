//#include <boost/random.hpp>
#include <iostream>
#include <ctime>
#include <cstdint>

#include <fstream>
#include <math.h>
#include <vector>
#include <climits>


using namespace std;

class readFile
{
private:

    const char *filename;
    int ncities;
    int nitems;
    int capacity;
    int *opt_tour;

    unsigned long coor_cities[MAXCITIES][2];
    
    unsigned long items[MAXITEMS][3];

    vector<vector<int> > items_in_city;
    vector<int> optimal_plan;
    float *distances;

public:

    readFile(const char *, const char *, const char*);
    ~readFile();

    //Methods
    float *getDistances(); // return distanceMatrix

    int getNcities();
    int getNitems();
    int getCapacity();

    int * getOptimalTour();
    unsigned long ** getItems();
    vector<int> getOptimalPlan();
    vector<vector<int> > getItems_in_city();

};

readFile::readFile(const char *filename, const char *opt_tour, const char *opt_knp)
{
    this->filename = filename;
    ifstream inFile;
    //inFile.open("test-example-n4-clean.txt");
    inFile.open(this->filename);
    inFile >> this->ncities;
    inFile >> this->nitems;
    inFile >> this->capacity;

    for (int i = 0; i < this->ncities; ++i)
    {
        inFile >> this->coor_cities[i][0] >> this->coor_cities[i][1];
        this->items_in_city.push_back(std::vector<int>());
    }
    for (int i = 0; i < this->nitems; ++i)
    {
        inFile >> this->items[i][0]; //Profit
        inFile >> this->items[i][1]; //weight
        inFile >> this->items[i][2]; //assigned city
        this->items[i][2]--;
        this->items_in_city[this->items[i][2]].push_back(i);
    }
    inFile.close();
    cout<<"succesfully read! file1"<<endl;

    // read optimal tour **************************

    this->opt_tour = new int[ncities];
    this->filename = filename;
    //inFile.open("test-example-n4-clean.txt");
    inFile.open(opt_tour);
    for (int i = 0; i < this->ncities; ++i)
    {
        inFile >> this->opt_tour[i];
        this->opt_tour[i]--;
    }
    inFile.close();

    cout<<"succesfully read! file2"<<endl;

    
    this->distances = (float *) malloc (this->ncities*this->ncities*sizeof(float));
    cout << "Despues de distances\n";


    // Read optimal plan ************************
    int nBestItems;    

    inFile.open(opt_knp);
    inFile >> nBestItems;


    
    for (int i = 0; i < nBestItems; ++i)
    {
        optimal_plan.push_back(-1);
        inFile >> optimal_plan[i];
    }
    inFile.close();
    
    cout<<"succesfully read! file3"<<endl;

    cout << "\nnBestItems: " << nBestItems << endl;


}

readFile::~readFile()
{
    cout << "readFile obj deleted!";
}

float * readFile::getDistances(){

    
    for (int i = 0; i < this->ncities; ++i)
    {
        this->distances[i*this->ncities+i] = 0.0;
        for (int j = i+1; j < this->ncities; ++j){
            this->distances[(i*this->ncities)+j] = ceil(sqrt((this->coor_cities[i][0]-this->coor_cities[j][0])*(this->coor_cities[i][0]-this->coor_cities[j][0]) + (this->coor_cities[i][1]-this->coor_cities[j][1])*(this->coor_cities[i][1]-this->coor_cities[j][1])));
            this->distances[(j*this->ncities)+i] = this->distances[(i*this->ncities)+j];
        }
    }
    
    return this->distances;
}

int readFile::getNcities(){
    //cout << "El total de ciudades leidas: " << ncities << endl;
    return this->ncities;
}

int readFile::getNitems(){
    return this->nitems;
}

int readFile::getCapacity(){
    return this->capacity;
}

vector<vector<int> > readFile::getItems_in_city(){
    return this->items_in_city;
}

unsigned long ** readFile::getItems(){
    const int tam = (int) this->nitems;
    //const int c = 3;
    unsigned long ** ptr = new unsigned long*[tam];
    for(int i = 0; i < this->nitems; i++){
        ptr[i] = new unsigned long[3];
        for(int j = 0; j < 3; j++){
            ptr[i][j] = this->items[i][j];
        }
    }
    
    return ptr;

}

int * readFile::getOptimalTour(){
    return this->opt_tour;
}

vector<int> readFile::getOptimalPlan(){
    return this->optimal_plan;
}