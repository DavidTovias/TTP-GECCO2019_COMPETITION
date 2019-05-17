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
    cout << "En write_in_file - solutoins\n";
    ofstream fs("solutions.txt"); // create file (tour and plan)
    for (int i = 0; i < COP.size(); i++)
    {
        cout << "En for\n";
        for(int j = 0; j < this->ncities; j++){
            fs << COP[i]->tour[j] << " ";
            //fs << "0 ";
        }
        fs << "\n\n";
        /*fs << "\n\n";
        for(int j = 0; j < this->nitems; j++){
            fs << COP[i]->packing[j] << " ";
        }
        fs << "\n";*/
    }
       
    fs.close(); // close file
    
   /* cout << "En write_in_file COP\n";
    ofstream tp("COP.txt");
    for (int i = 0; i < COP.size(); i++)
    {
        tp << COP[i]->time << " " << COP[i]->profit << "\n";
    }
    tp << "\n";
    tp.close();*/
}