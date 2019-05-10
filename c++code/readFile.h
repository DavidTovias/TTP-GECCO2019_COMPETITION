#include <boost/random.hpp>
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
    short int **opt_plan;

    unsigned long coor_cities[MAXCITIES][2];
    
    unsigned long items[MAXITEMS][3];

    vector<vector<int> > items_in_city;
    vector<short int> optimal_plan;
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
    vector<short int> getOptimalPlan();
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

    for (size_t i = 0; i < this->ncities; ++i)
    {
        inFile >> this->coor_cities[i][0] >> this->coor_cities[i][1];
        this->items_in_city.push_back(std::vector<int>());
    }
    for (size_t i = 0; i < this->nitems; ++i)
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
    for (size_t i = 0; i < this->ncities; ++i)
    {
        inFile >> this->opt_tour[i];
        this->opt_tour[i]--;
    }
    inFile.close();

    cout<<"succesfully read! file2"<<endl;

    int k = 0;
    cout << "imprimiendo items\n";
    for(size_t i = 0; i < this->nitems; i++)
    {
        for(size_t j = 0; j < 3; j++)
        {
            cout << items[i][j] << " ";
            k++;
        }
        cout << endl;
    }
    cout << endl;
    cout << "K: " << k << endl;

    
    this->distances = (float *) malloc (this->ncities*this->ncities*sizeof(float));
    cout << "Despues de distances\n";


    // Read optimal plan ************************
    short int nBestItems;    

    inFile.open(opt_knp);
    inFile >> nBestItems;
    // Asignando memoria dinamicamente
    this->opt_plan = new short int*[nBestItems];
    for (size_t i = 0; i < nBestItems; i++)
    {
        this->opt_plan[i] = new short int[2];
    }
    
    for (size_t i = 0; i < nBestItems; ++i)
    {
        inFile >> this->opt_plan[i][0];
        optimal_plan.push_back(this->opt_plan[i][0]);
    }
    inFile.close();
    
    cout << "\nnBestItems: " << nBestItems << endl;


}

readFile::~readFile()
{
    cout << "readFile obj deleted!";
}

float * readFile::getDistances(){

    
    for (size_t i = 0; i < this->ncities; ++i)
    {
        this->distances[i*this->ncities+i] = 0.0;
        for (size_t j = i+1; j < this->ncities; ++j){
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
    const int c = 3;
    unsigned long ** ptr = new unsigned long*[tam];
    for(size_t i = 0; i < this->nitems; i++){
        ptr[i] = new unsigned long[3];
        for(size_t j = 0; j < 3; j++){
            ptr[i][j] = this->items[i][j];
        }
    }
    
    return ptr;

}

int * readFile::getOptimalTour(){
    return this->opt_tour;
}

vector<short int> readFile::getOptimalPlan(){
    return this->optimal_plan;
}