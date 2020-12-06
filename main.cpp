#include "reddit.h"
#include <vector>
#include "edge.h"
#include <chrono>
#include <algorithm>


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
  red.printPath(red.BFS("rarepuppers", "erieco"));
  red.printPath(red.IDS("rarepuppers", "erieco", 4));

  // std::cout << red.getSentiment(red.BFS("1", "3")) << std::endl;
  // std::cout << red.getSentiment(red.BFS("1", "2")) << std::endl;
  // std::cout << red.getSentiment(red.BFS("1", "4")) << std::endl;
  // std::cout << red.getSentiment(red.BFS("1", "5")) << std::endl;
  // std::cout << red.getSentiment(red.BFS("3", "1")) << std::endl;
  // std::cout << red.getSentiment(red.BFS("3", "3")) << std::endl;


  // vector<Vertex> expected = red.getGraph().getVertices();
  // vector<Vertex> actual = red.TraversalDFS();
  
  // sort(expected.begin(), expected.end());
  // sort(actual.begin(), actual.end());
  // if(expected == actual) std::cout << "Gottem" << std::endl; 

  // vector<Vertex> path = red.IDS("rarepuppers", "erieco", 5);
  // red.printPath(path);


  // vector<vector<Vertex>> sccs = red.SCCs();  

  // for(size_t x = 0; x < sccs.size(); x++)
  // {
  //   size_t sz = sccs[x].size();
  //   if(sz > 2) std::cout << sz << std::endl;
  // }

  // int bfs = 0;
  // int ids = 0;
  // for(int i = 0; i < 100; i++)
  // {
  //   if((i+1)%10 == 0) std::cout << i+1 << std::endl;
  //   auto t1 = std::chrono::high_resolution_clock::now();
  //   red.BFS("rarepuppers", "erieco");
  //   auto t2 = std::chrono::high_resolution_clock::now();
  //   red.IDS("rarepuppers", "erieco", 5);
  //   auto t3 = std::chrono::high_resolution_clock::now();
  //   bfs += std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  //   ids += std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();
  // }
  // std::cout << "Average time for BFS: " << bfs/100 << std::endl;
  // std::cout << "Average time for IDS: " << ids/100 << std::endl;
 

  // printVec(red.getGraph().getAdjacent("simplerockets"));
  
  
  return 0;
}

//reference:
// Average time: 113868
//copy:
//Average time: 397093

// *****************************Search Time & Memory Test*******************************
// Tests for search between "rarepuppers" and "erieco"
// Baseline: total heap usage: 685,787 allocs, 685,787 frees, 77,193,512 bytes allocated
// BFS: total heap usage: 707,555 allocs, 707,555 frees, 83,385,040 bytes allocated 
// IDS: total heap usage: 703,676 allocs, 703,676 frees, 91,823,200 bytes allocated
// Average time for BFS:  51.418 ms
// Average time for IDS: 118.075 ms
// Memeory Allocated BFS:  6.191528 MB 
// Memeory Allocated IDS: 14.629688 MB


// Time comparison for reversing traversal path vs not reversing traversal path:

// Reversing before returning:
// Average time for BFS:  51.418 ms
// Average time for IDS: 118.075 ms

// Not reversing before returning:
// Average time for BFS: 51.378 ms
// Average time for IDS: 99.102 ms