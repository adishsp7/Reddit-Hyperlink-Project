#include "reddit.h"
#include <vector>
#include "edge.h"
#include <chrono>


void printVec(vector<Vertex> vertices);
void printVec(vector<Vertex> vertices)
{
  for(size_t i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
}

int main() {

  // Reddit red("tests/medium.csv");
  Reddit red("data/connected.csv");
  std::cout << "Graph Constructed!" << std::endl; 
  // Print textual output of the graph:
  // red.getGraph().print();

  // printVec(red.getGraph().getAdjacent("simplerockets"));
  auto t1 = std::chrono::high_resolution_clock::now();
  red.SCCs();
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  auto t3 = std::chrono::high_resolution_clock::now();
  red.StronglyCC();
  auto t4 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t2 ).count();

  std::cout << "Kosaraju's Algo: " << duration1 << std::endl; 
  std::cout << "Tarjan's Algo: " << duration2 << std::endl;
  // for(size_t x = 0; x < sccs.size(); x++)
  // {
  //   printVec(sccs[x]);
  // }
  return 0;
}