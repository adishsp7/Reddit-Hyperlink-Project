#include "../cs225/catch/catch.hpp"
#include "reddit.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>


//using namespace cs225;
using namespace std;


TEST_CASE("Reddit(file) constructor creates the correct edges", "[weight=1][part=1]") {
  Reddit red("data/empty.csv");
  const Graph & g = red.getGraph();

  // always required edges
  REQUIRE(g.edgeExists("1", "3"));
  REQUIRE(g.edgeExists("2", "4"));

  REQUIRE(g.edgeExists("3", "2"));

  REQUIRE(g.edgeExists("4", "5"));
  REQUIRE(g.edgeExists("5", "2"));


}

TEST_CASE("Reddit(file) constructor checks if empty", "[weight=1][part=1]") {
  Reddit red("data/empty.csv");
  const Graph & g = red.getGraph();
  vector<Vertex> vertices = g.getVertices();
  vector<Vertex> edges = g.getEdges();
  
  REQUIRE(vertices.empty() == true);
  REQUIRE(edges.empty() == true);
}

TEST_CASE("Reddit(file) constructor creates corrects vertices", "[weight=1][part=1]") {
  Reddit red("data/empty.csv");
  const Graph & g = red.getGraph();

  REQUIRE(g.vertexExists("A"));
  REQUIRE(g.vertexExists("B"));
  REQUIRE(g.vertexExists("C"));
  REQUIRE(g.vertexExists("D"));
  REQUIRE(g.vertexExists("E"));

}

TEST_CASE("BFS creates correct shortest path traversal ", "[weight=1][part=1]"){


}

TEST_CASE("IDS creates correct traversal ", "[weight=1][part=1]"){


}

TEST_CASE("DFS creates correct traversal ", "[weight=1][part=1]"){


}

TEST_CASE("Mike Strongly Connected Components", "[weight=1][part=1]"){


}


TEST_CASE("Yash Strongly Connected Components", "[weight=1][part=1]"){


}


