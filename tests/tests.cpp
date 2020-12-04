#include "../cs225/catch/catch.hpp"
#include "../reddit.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <unordered_set>


//using namespace cs225;
using namespace std;

TEST_CASE("Reddit(file) constructor checks if empty", "[weight=1][part=1][constructor]") {
  Reddit red("tests/empty.csv");
  const Graph & g = red.getGraph();
  vector<Vertex> vertices = g.getVertices();
  vector<Edge> edges = g.getEdges();
  
  REQUIRE(vertices.empty() == true);
  REQUIRE(edges.empty() == true);
}

TEST_CASE("Reddit(file) Constructor Test - Small", "[weight=1][part=1][constructor]") {
  int n = 5; //number of edges - extracted from csv file
  Reddit red("tests/small.csv"); //constructs reddit object using constructor
  const Graph & g = red.getGraph(); //get graph from reddit object
  const Graph & gT = red.getTranspose(); //get transpose from reddit object

  REQUIRE(g.getEdges().size() == n); //Ensures number of edges is exactly correct 
  REQUIRE(gT.getEdges().size() == n);  //Ensures number of edges is exactly correct 

  //Vector of vertex pairs representing expected edges
  vector<vector<string>> pairs = {{"1", "3"}, {"2", "4"}, {"3", "2"}, {"4", "5"}, {"5", "2"}};

  for(int i = 0; i < n; i++)
  {
    REQUIRE(g.edgeExists(pairs[i][0], pairs[i][1]));
    REQUIRE(gT.edgeExists(pairs[i][1], pairs[i][0]));
  } 

  // always required edges
  // REQUIRE(g.edgeExists("1", "3"));
  // REQUIRE(gT.edgeExists("3", "1"));

  // REQUIRE(g.edgeExists("2", "4"));
  // REQUIRE(gT.edgeExists("4", "2"));

  // REQUIRE(g.edgeExists("3", "2"));
  // REQUIRE(gT.edgeExists("2", "3"));

  // REQUIRE(g.edgeExists("4", "5"));
  // REQUIRE(gT.edgeExists("5", "4"));

  // REQUIRE(g.edgeExists("5", "2"));
  // REQUIRE(gT.edgeExists("2", "5"));

}

TEST_CASE("Reddit(file) Constructor Test - Medium", "[weight=1][part=1][constructor]") {
  int n = 13; //number of edges - extracted from csv file
  Reddit red("tests/medium.csv"); //constructs reddit object using constructor
  const Graph & g = red.getGraph(); //get graph from reddit object
  const Graph & gT = red.getTranspose(); //get transpose from reddit object

  REQUIRE(g.getEdges().size() == n);  //Ensures number of edges is exactly correct 
  REQUIRE(gT.getEdges().size() == n);  //Ensures number of edges is exactly correct 
  
  //Vector of vertex pairs representing expected edges
  vector<vector<string>> pairs = {{"K", "A"}, 
                            {"K", "B"}, 
                            {"A", "D"}, 
                            {"D", "H"}, 
                            {"D", "F"}, 
                            {"H", "G"}, 
                            {"G", "F"}, 
                            {"G", "J"}, 
                            {"G", "E"}, 
                            {"F", "C"}, 
                            {"C", "B"}, 
                            {"E", "K"}, 
                            {"J", "K"}};
  
  for(int i = 0; i < n; i++)
  {
    REQUIRE(g.edgeExists(pairs[i][0], pairs[i][1])); //Ensures each of the expected edges exists in graph
    REQUIRE(gT.edgeExists(pairs[i][1], pairs[i][0])); //Ensures each of the expected edges exists in transpose
  } 
}

TEST_CASE("Reddit(file) Constructor Test - Large #1", "[weight=1][part=1][constructor]") {
  int n = 18; //number of edges - extracted from csv file
  Reddit red("tests/large1.csv"); //constructs reddit object using constructor
  const Graph & g = red.getGraph(); //get graph from reddit object
  const Graph & gT = red.getTranspose(); //get transpose from reddit object

  REQUIRE(g.getEdges().size() == n);  //Ensures number of edges is exactly correct 
  REQUIRE(gT.getEdges().size() == n);  //Ensures number of edges is exactly correct 

  //Vector of vertex pairs representing expected edges
  vector<vector<string>> pairs = {{"K", "B"}, 
                            {"A", "D"}, 
                            {"D", "H"}, 
                            {"D", "F"}, 
                            {"H", "G"}, 
                            {"G", "F"}, 
                            {"G", "J"}, 
                            {"G", "E"}, 
                            {"F", "C"}, 
                            {"C", "B"}, 
                            {"E", "K"}, 
                            {"J", "K"},
                            {"1", "3"},
                            {"2", "4"},
                            {"3", "2"},
                            {"4", "5"},
                            {"5", "2"},
                            {"A", "1"}};
  
  for(int i = 0; i < n; i++)
  {
    REQUIRE(g.edgeExists(pairs[i][0], pairs[i][1])); //Ensures each of the expected edges exists in graph
    REQUIRE(gT.edgeExists(pairs[i][1], pairs[i][0])); //Ensures each of the expected edges exists in transpose
  } 
}

TEST_CASE("Reddit(file) Constructor Test - Large #2", "[weight=1][part=1][constructor]") {
  int n = 20; //number of edges - extracted from csv file
  Reddit red("tests/large2.csv"); //constructs reddit object using constructor
  const Graph & g = red.getGraph(); //get graph from reddit object
  const Graph & gT = red.getTranspose(); //get transpose from reddit object

  REQUIRE(g.getEdges().size() == n);  //Ensures number of edges is exactly correct 
  REQUIRE(gT.getEdges().size() == n);  //Ensures number of edges is exactly correct 

  //Vector of vertex pairs representing expected edges
  vector<vector<string>> pairs = {{"K", "B"}, 
                            {"A", "D"}, 
                            {"D", "H"}, 
                            {"D", "F"}, 
                            {"H", "G"}, 
                            {"G", "F"}, 
                            {"G", "J"}, 
                            {"G", "E"}, 
                            {"F", "C"}, 
                            {"C", "B"}, 
                            {"E", "K"}, 
                            {"J", "K"},
                            {"1", "3"},
                            {"2", "4"},
                            {"3", "2"},
                            {"4", "5"},
                            {"5", "2"},
                            {"C", "5"},
                            {"4", "A"},
                            {"A", "1"}};
  
  for(int i = 0; i < n; i++)
  {
    REQUIRE(g.edgeExists(pairs[i][0], pairs[i][1])); //Ensures each of the expected edges exists in graph
    REQUIRE(gT.edgeExists(pairs[i][1], pairs[i][0])); //Ensures each of the expected edges exists in transpose
  } 
}

// TEST_CASE("Reddit(file) constructor creates corrects vertices", "[weight=1][part=1]") {
//   Reddit red("data/empty.csv");
//   const Graph & g = red.getGraph();

//   REQUIRE(g.vertexExists("A"));
//   REQUIRE(g.vertexExists("B"));
//   REQUIRE(g.vertexExists("C"));
//   REQUIRE(g.vertexExists("D"));
//   REQUIRE(g.vertexExists("E"));
// }
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// NOTE: Not needed since edgeExists throws an error if either of the vertices is not found 


TEST_CASE("BFS creates correct shortest path traversal ", "[weight=1][part=1]"){


}

TEST_CASE("IDS creates correct traversal ", "[weight=1][part=1]"){
  Reddit red("data/empty.csv");   // test case for 5 vertices

  const Graph & g = red.getGraph();
  vector<Vertex> path = red.IDS("1", "5", 2);   // since d=2, should return empty path

  REQUIRE(path.size() == 0);  // empty path

  // checking for valid path in progress - will update soon

}

TEST_CASE("DFS creates correct traversal ", "[weight=1][part=1]"){
<<<<<<< HEAD
  /*Reddit red("data/empty.csv");   // test case for 5 vertices
=======
  Reddit red("tests/small.csv");   // test case for 5 vertices
>>>>>>> 8a70c5f955dccddfa8e553549da0a1f1b3336d83

  const Graph & g = red.getGraph();  
  unordered_set<Vertex> visited;
  stack<Vertex> s;
  // assumed getAdjacent rotate ccw(?)
<<<<<<< HEAD
  red.DFS("1", g, visited, s);    // s from bottom to top = 4, 5, 2, 3, 1, visited = [1, 3, 2, 5, 4]
=======
  red.DFS("1", g, visited, s);    // s from bottom to top = 5, 4, 2, 3, 1, visited = [1, 3, 2, 4, 5]
>>>>>>> 8a70c5f955dccddfa8e553549da0a1f1b3336d83
  
  REQUIRE(s.size() == 5);     // check if stack traversed all 5 vertices
  stack<Vertex> expected;
  expected.push("5");
  expected.push("4");
  expected.push("2");
  expected.push("3");
  expected.push("1");
  
<<<<<<< HEAD
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
  REQUIRE(v3 == "4");*/
=======
  REQUIRE(expected == s);
>>>>>>> 8a70c5f955dccddfa8e553549da0a1f1b3336d83

}

TEST_CASE("Tarjan's Strongly Connected Components - Small", "[weight=1][part=1][Tarjan]"){
  Reddit red("tests/small.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}};
  vector<vector<Vertex>> res = red.StronglyCC(); 

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Tarjan's Strongly Connected Components - Medium", "[weight=1][part=1][Tarjan]"){
  Reddit red("tests/medium.csv");
  
  vector<vector<Vertex>> expected = {{"A", "D", "E", "G", "H", "J", "K"}, {"B"}, {"C"}, {"F"}};
  vector<vector<Vertex>> res = red.StronglyCC(); 

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Tarjan's Strongly Connected Components - Large #1", "[weight=1][part=1][Tarjan]"){
  Reddit red("tests/large1.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}, {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"}, {"H"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.StronglyCC(); 

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Tarjan's Strongly Connected Components - Large #2", "[weight=1][part=1][Tarjan]"){
  Reddit red("tests/large2.csv");
  
  vector<vector<Vertex>> expected = {{"1", "2", "3", "4", "5", "A", "C", "D", "F", "G", "H"}, {"B"}, {"E"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.StronglyCC(); 
  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Small", "[weight=1][part=1][Kosaraju]"){
  Reddit red("tests/small.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Medium", "[weight=1][part=1][Kosaraju]"){
  Reddit red("tests/medium.csv");
  
  vector<vector<Vertex>> expected = {{"A", "D", "E", "G", "H", "J", "K"}, {"B"}, {"C"}, {"F"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Large #1", "[weight=1][part=1][Kosaraju]"){
  Reddit red("tests/large1.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}, {"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"}, {"H"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}

TEST_CASE("Kosaraju's Strongly Connected Components - Large #2", "[weight=1][part=1][Kosaraju]"){
  Reddit red("tests/large2.csv");
  
  vector<vector<Vertex>> expected = {{"1", "2", "3", "4", "5", "A", "C", "D", "F", "G", "H"}, {"B"}, {"E"}, {"J"}, {"K"}};
  vector<vector<Vertex>> res = red.SCCs();

  for(size_t i = 0; i < res.size(); i++)
  {
    sort(res[i].begin(), res[i].end());   
  }

  sort(res.begin(), res.end());
  REQUIRE(res == expected);
}
