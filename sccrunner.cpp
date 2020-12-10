#include "reddit.h"
#include <vector>
#include <string>
#include <fstream>

int main(int argc, char** argv) 
{
    if(argc != 2)
    {
        std::cout << "Function requires arguments: [Filepath to data set]" << std::endl; 
    }
    Reddit red(argv[1]);
    system("ulimit -s unlimited");
    std::ofstream f1;

    vector<vector<Vertex>> kosaraju = red.SCCs();
    std::cout << "Writing SCCs found using Kosaraju's algorithm to 'kosarajus.txt'" << std::endl;
    f1.open ("kosarajus.txt");
    int counter;
    for(auto & vec : kosaraju)
    {
        counter = 0;
        for(auto scc: vec)
        {
            f1 << scc << " ";
            counter++;
            if(counter % 9 == 0) f1 << "\n";
        }
        f1 << "\n***\n";
    }
    f1.close();

    vector<vector<Vertex>> tarjans = red.StronglyCC();
    std::cout << "Writing SCCs found using Tarjan's algorithm to 'tarjans.txt'" << std::endl;
    f1.open ("tarjans.txt");
    for(auto & vec : tarjans)
    {
        counter = 0;
        for(auto scc: vec)
        {
            f1 << scc << " ";
            counter++;
            if(counter % 9 == 0) f1 << "\n";
        }
        f1 << "\n***\n";
    }
    f1.close();   
}
