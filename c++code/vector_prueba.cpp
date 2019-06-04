#include <iostream>
#include <vector>

using namespace std;

class vector_prueba
    {
    private:
        /* data */
    public:
        vector_prueba(/* args */);
        ~vector_prueba();

        void showTour();

        vector<int> SOL;
    };
    
vector_prueba::vector_prueba(/* args */)
{
    for (size_t i = 0; i < 280; i++)
    {
        this->SOL.push_back(-1);
    }
    
}

vector_prueba::~vector_prueba()
{
}



void vector_prueba::showTour(){
    for (size_t i = 0; i < 280; i++)
    {
        cout << this->SOL[i] << " ";
    }
    cout << endl;
    
}




int main(int argc, const char** argv) {

    vector<vector_prueba*> nodo;
    vector_prueba *p1;
    
    for (size_t i = 0; i < 22; i++)
    {
        p1 = new vector_prueba();
        nodo.push_back(p1);
    }
    
    cout << "nodo.size(): " << nodo.size() << endl;

    for (size_t i = 0; i < nodo.size(); i++)
    {
        nodo[i]->showTour();
        cout << "\n\n";
    }
    
    

    return 0;
}