#include "../cs225/catch/catch.hpp"
#include "reddit.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <unordered_set>


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
  Reddit red("data/empty.csv");   // test case for 5 vertices

  const Graph & g = red.getGraph();
  vector<Vertex> path = IDS("1", "5", 2);   // since d=2, should return empty path

  REQUIRE(path.size() == 0);  // empty path

  // checking for valid path in progress - will update soon

}

TEST_CASE("DFS creates correct traversal ", "[weight=1][part=1]"){
  Reddit red("data/empty.csv");   // test case for 5 vertices

  const Graph & g = red.getGraph();  
  unordered_set<Vertex> visited;
  stack<Vertex> s;
  // assumed getAdjacent rotate ccw(?)
  DFS("1", g, visited, s);    // s from bottom to top = 4, 5, 2, 3, 1, visited = [1, 3, 2, 5, 4]
  
  REQUIRE(s.size() == 5);     // check if stack traversed all 5 vertices
  
  Vertex v1 = s.pop();
  Vertex v2 = s.pop();
  Vertex v3 = s.pop();
  Vertex v4 = s.pop();
  Vertex v5 = s.pop();        // stack cleare
  
  REQUIRE(v1 == "1");
  REQUIRE(v2 == "3");
  REQUIRE(v3 == "2");
  REQUIRE(v4 == "5");
  REQUIRE(v5 == "4")
  
  visited.clear();            // clear visite
  
  DFS("2", g, visited, s);    // s from bottom to top = 4, 5, 2, visited = [2, 5, 4]
  REQUIRE(s.size() == 3);
  v1 = s.pop();
  v2 = s.pop();
  v3 = s.pop();
    
  REQUIRE(v1 == "2");
  REQUIRE(v2 == "5");
  REQUIRE(v3 == "4");

}

TEST_CASE("Mike Strongly Connected Components", "[weight=1][part=1]"){


}


TEST_CASE("Kosaraju's Strongly Connected Components - Small", "[weight=1][part=1]"){
  Reddit red("small.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(int i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Medium", "[weight=1][part=1]"){
  Reddit red("medium.csv");
  
  vector<vector<Vertex>> expected = {{"A", "D", "E", "G", "H", "J", "K"}, {"B"}, {"C"}, {"F"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(int i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Large #1", "[weight=1][part=1]"){
  Reddit red("large1.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}, {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"}, {"H"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(int i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Large #2", "[weight=1][part=1]"){
  Reddit red("large2.csv");
  
  vector<vector<Vertex>> expected = {{"1", "2", "3", "4", "5", "A", "C", "D", "F", "G", "H"}, {"B"}, {"E"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(int i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}