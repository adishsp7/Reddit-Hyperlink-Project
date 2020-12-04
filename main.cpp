#include "reddit.h"
#include <vector>
#include "edge.h"
#include <chrono>


void printVec(vector<Vertex> vertices);
void printVec(vector<Vertex> vertices)
{
  if(vertices.empty()) 
  {
    std::cout << "Empty Path!" << std::endl;
    return;
  }
  for(size_t i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
}

void sccSpeed(Reddit & r);
void sccSpeed(Reddit & r)
{
  auto t1 = std::chrono::high_resolution_clock::now();
  r.SCCs();
  auto t2 = std::chrono::high_resolution_clock::now();
  r.StronglyCC();
  auto t3 = std::chrono::high_resolution_clock::now();

  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

  std::cout << "Kosaraju's Algo: " << duration1 << std::endl; 
  std::cout << "Tarjan's Algo: " << duration2 << std::endl;
}

int main() {
  
  // Reddit red("tests/small.csv");
  // Reddit red("tests/medium.csv");
  // Reddit red("tests/large2.csv");
  Reddit red("data/connected.csv");
  std::cout << "Graph Constructed!" << std::endl; 
  // sccSpeed(red);
  // vector<vector<Vertex>> res = red.StronglyCC();
  // for(size_t i = 0; i < res.size(); i++)
  // {
  //   if(res[i].size() > 2) std::cout << res[i].size() << std::endl;
  // }
  

  // int brrr = 0;
  // for(int i = 0; i < 100; i++)
  // {
  //   if((i+1)%10 == 0) std::cout << i+1 << std::endl;
  //   auto t1 = std::chrono::high_resolution_clock::now();
  //   red.IDS("rarepuppers", "colorado", 5);
  //   // red.BFS("rarepuppers", "erieco");
  //   auto t2 = std::chrono::high_resolution_clock::now();
  //   brrr += std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  // }
  // std::cout << "Average time: " << brrr/100 << std::endl;
 

  // printVec(red.getGraph().getAdjacent("simplerockets"));
  
  // for(size_t x = 0; x < sccs.size(); x++)
  // {
  //   printVec(sccs[x]);
  // }
  return 0;
}

// Average time: 376232