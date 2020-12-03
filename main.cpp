#include "reddit.h"
#include <vector>
#include "edge.h"

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
  // Print textual output of the graph:
  // red.getGraph().print();

  // printVec(red.getGraph().getAdjacent("simplerockets"));
  vector<vector<Vertex>> sccs = red.SCCs();
  for(size_t x = 0; x < sccs.size(); x++)
  {
    printVec(sccs[x]);
  }
  return 0;
}