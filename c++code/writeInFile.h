#include<iostream>
#include <vector>
#include <fstream>
//#include <ofstream>

using namespace std;

class writeInFile
{
private:
    /* data */
public:

    int ncities;
    int nitems;
    void write_in_file(vector<Nodo*>);

    writeInFile(int, int);
    ~writeInFile();
};

writeInFile::writeInFile(int ncities, int nitems)
{
    this->ncities = ncities;
    this->nitems = nitems;
}

writeInFile::~writeInFile()
{
}

void writeInFile::write_in_file(vector<Nodo*> COP)
{
    size_t cop_size = COP.size();
    cout << "En write_in_file - solutions\n";
    ofstream fs("solutions.txt",ios::app); // create file (tour and plan)
    for (int i = 0; i < cop_size; i++)
    {
        cout << "En for\n";
        for(int j = 0; j < this->ncities; j++){
            if(j!=ncities-1){
                fs << COP[i]->tour[j] << " ";
            }else{
                fs << COP[i]->tour[j];
            }
        }
        fs << "\n";
        for(int j = 0; j < this->nitems; j++){
            if (j != nitems-1)
            {
                fs << COP[i]->packing[j] << " ";
            }else{
                fs << COP[i]->packing[j];
            }
        }
        if(i != COP.size()-1){
            fs << "\n\n";
        }
    }
    fs << "\n\n";
    fs.close(); // close file
    
    cout << "En write_in_file COP\n";
    //TOVIAS_a280_n279.f
    
    
    ofstream tp("COP.txt",ios::app);
    for (int i = 0; i < cop_size; i++)
    {   
        if(i != cop_size-1){
            tp << setprecision(15) << fixed << COP[i]->time << " " << COP[i]->profit << "\n";
        }else{
            tp << setprecision(15) << fixed << COP[i]->time << " " << COP[i]->profit;
        }
        
    }
    tp << "\n";
    tp.close();
}
