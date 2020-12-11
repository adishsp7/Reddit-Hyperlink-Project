#include "../cs225/catch/catch.hpp"
#include "../reddit.h"

using namespace std;
int maxDepth(Reddit & red, Vertex src); // declares depth function used for IDS testing
int dUtil(const Graph & g, unordered_map<Vertex, int> & depth, Vertex node); // declares depth function utility

/**
 * Returns Max depth of vertex in reddit graph
 * @param red - Reddit graph object
 * @param src - Vertex for which max depth is required
 * @return Max depth of src vertex
 */
int maxDepth(Reddit & red, Vertex src)
{
    const Graph & g = red.getGraph(); // gets graph object
    if(g.vertexExists(src)) //checks if search vertex exists
    {
      unordered_map<Vertex, int> depth; // initializes depth map
      return dUtil(g, depth, src); // starts recursion for src node
    }
    return -1; //error handling
}

/**
 * Calls dUtil to find max depth
 * @param depth - Unordered map that tracks max depth of each node
 * @param node - Current recursive call's vertex
 * @return Max depth of current node using DFS
 */
int dUtil(const Graph & g, unordered_map<Vertex, int> & depth, Vertex node)
{
  int max = 0; // initializes max depth tracker for current vertex to 0
  depth[node] = -1;
  vector<Vertex> vertex_list = g.getAdjacent(node);  // get a list of adjacent vertices
  for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
  {
    int curr; // initializes max depth tracker for this adjecenct vertex
    if(depth.find(vertex_list[i]) == depth.end()) // checks if this adjecent vertex is unvisted
    {
      curr = dUtil(g, depth, vertex_list[i]) + 1; // calls dUtil to get max depth for this adjecent vertex
    }
    else // this vertex has already been visited
    {
      curr = depth[vertex_list[i]] + 1; // gets max depth of this adjecent vertex
    }
    max = (curr > max) ? curr : max; // sets max to the maximum of current adjecent vertex depth and previously iterated adjecent vertices
  }
  depth[node] = max; // adds current vertex to depth map and assigns max as its depth
  return max; // returns max depth of current vertex
}



TEST_CASE("Reddit(file) constructor checks if empty", "[weight=1][constructor]") {
  Reddit red("tests/empty.csv");
  const Graph & g = red.getGraph();
  vector<Vertex> vertices = g.getVertices();
  vector<Edge> edges = g.getEdges();
  
  REQUIRE(vertices.empty() == true);
  REQUIRE(edges.empty() == true);
}

TEST_CASE("Reddit(file) Constructor Test - Small", "[weight=1][constructor]") {
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
}

TEST_CASE("Reddit(file) Constructor Test - Medium", "[weight=1][constructor]") {
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

TEST_CASE("Reddit(file) Constructor Test - Large #1", "[weight=1][constructor]") {
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

TEST_CASE("Reddit(file) Constructor Test - Large #2", "[weight=1][constructor]") {
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

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("BFS creates correct shortest path traversal - Small", "[weight=1][BFS]"){
  Reddit red("tests/small.csv"); //constructs reddit object using constructor

  vector<Vertex> test1to5 = {"5", "4", "2", "3", "1"}; //test for BFS shortest path from vertices 1 to 5 in reverse
  vector<Vertex> sol1to5 = red.BFS("1", "5"); //solution from BFS function

  vector<Vertex> test3to1 = {}; //test for BFS shortest path from vertices 3 to 1 (NOT POSSIBLE);
  vector<Vertex> sol3to1 = red.BFS("3", "1"); //solution from BFS function

  REQUIRE(test1to5 == sol1to5);
  REQUIRE(test3to1 == sol3to1);

}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("BFS creates correct shortest path traversal - Medium", "[weight=1][BFS]"){
  Reddit red("tests/medium.csv"); //constructs reddit object using constructor

  vector<Vertex> testDtoA = {"A", "K", "E", "G", "H", "D"}; //test for BFS shortest path from vertices D to A in reverse
  vector<Vertex> solDtoA = red.BFS("D", "A"); //solution from BFS function

  REQUIRE(testDtoA == solDtoA);

}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("BFS creates correct shortest path traversal - Large #1", "[weight=1][BFS]"){
  Reddit red("tests/large1.csv"); //constructs reddit object using constructor

  vector<Vertex> testAtoB = {"B", "C", "F", "D", "A"}; //test for BFS shortest path from vertices A to B in reverse
  vector<Vertex> solAtoB = red.BFS("A", "B"); //solution from BFS function

  REQUIRE(testAtoB == solAtoB);

}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("BFS creates correct shortest path traversal - Large #2", "[weight=1][BFS]"){
  Reddit red("tests/large2.csv"); //constructs reddit object using constructor

  vector<Vertex> testAto2 = {"2", "3", "1", "A"}; //test for BFS shortest path from vertices A to 2 in reverse
  vector<Vertex> solAto2 = red.BFS("A", "2"); //solution from BFS function

  REQUIRE(testAto2 == solAto2);

}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("IDS creates the same path as BFS - Small", "[weight=1][IDS]"){
  Reddit red("tests/small.csv"); //constructs reddit object using constructor
  
  int maxD = maxDepth(red, "1"); //gets maximum explorable depth from test source
  vector<Vertex> expected = red.BFS("1", "5"); //solution from BFS function
  vector<Vertex> actual = red.IDS("1", "5", maxD); //solution from IDS function
  vector<Vertex> path = red.IDS("1", "5", 2);   // Since d=2, should return empty path

  REQUIRE(expected == actual);
  REQUIRE(path.size() == 0);  // empty path
}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("IDS creates the same path as BFS - Medium", "[weight=1][IDS]"){
  Reddit red("tests/medium.csv"); //constructs reddit object using constructor

  int maxD = maxDepth(red, "D"); //gets maximum explorable depth from test source
  vector<Vertex> expected = red.BFS("D", "A"); //solution from BFS function
  vector<Vertex> actual = red.IDS("D", "A", maxD); //solution from IDS function

  REQUIRE(expected == actual);
}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("IDS creates the same path as BFS - Large #1", "[weight=1][IDS]"){
  Reddit red("tests/large1.csv"); //constructs reddit object using constructor

  int maxD = maxDepth(red, "A"); //gets maximum explorable depth from test source
  vector<Vertex> expected = red.BFS("A", "B"); //solution from BFS function
  vector<Vertex> actual = red.IDS("A", "B", maxD); //solution from IDS function

  REQUIRE(expected == actual);
}

// Traversal test cases expect path in reverse order destination <- source due to function optimization
TEST_CASE("IDS creates the same path as BFS - Large #2", "[weight=1][IDS]"){
  Reddit red("tests/large2.csv"); //constructs reddit object using constructor

  int maxD = maxDepth(red, "A"); //gets maximum explorable depth from test source
  vector<Vertex> expected = red.BFS("A", "2"); //solution from BFS function
  vector<Vertex> actual = red.IDS("A", "2", maxD); //solution from IDS function

  REQUIRE(expected == actual);
}

TEST_CASE("Tarjan's Strongly Connected Components - Small", "[weight=1][Tarjan]"){
  Reddit red("tests/small.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}}; // expected sccs in sorted order
  vector<vector<Vertex>> res = red.StronglyCC(); //get scc output

  for(size_t i = 0; i < res.size(); i++) // iterate over all sccs found
  {
    sort(res[i].begin(), res[i].end()); // sort scc lexicographically
  }

  sort(res.begin(), res.end()); // sort all sccs lexicographically
  REQUIRE(res == expected);
}

//Check small test case for comments
TEST_CASE("Tarjan's Strongly Connected Components - Medium", "[weight=1][Tarjan]"){
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

//Check small test case for comments
TEST_CASE("Tarjan's Strongly Connected Components - Large #1", "[weight=1][Tarjan]"){
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

//Check small test case for comments
TEST_CASE("Tarjan's Strongly Connected Components - Large #2", "[weight=1][Tarjan]"){
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

TEST_CASE("Kosaraju's Strongly Connected Components - Small", "[weight=1][Kosaraju]"){
  Reddit red("tests/small.csv");
  
  vector<vector<Vertex>> expected = {{"1"}, {"2", "4", "5"}, {"3"}}; // expected sccs in sorted order
  vector<vector<Vertex>> res = red.SCCs(); //get scc output

  for(size_t i = 0; i < res.size(); i++) // iterate over all sccs found
  {
    sort(res[i].begin(), res[i].end()); // sort scc lexicographically
  }

  sort(res.begin(), res.end()); // sort all sccs lexicographically
  REQUIRE(res == expected);
}

//Check small test case for comments
TEST_CASE("Kosaraju's Strongly Connected Components - Medium", "[weight=1][Kosaraju]"){
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

//Check small test case for comments
TEST_CASE("Kosaraju's Strongly Connected Components - Large #1", "[weight=1][Kosaraju]"){
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

//Check small test case for comments
TEST_CASE("Kosaraju's Strongly Connected Components - Large #2", "[weight=1][Kosaraju]"){
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

TEST_CASE("Entire Graph DFS Traversal - Small", "[weight=1][DFSTraversal]"){
  Reddit red("tests/small.csv");
  
  vector<Vertex> expected = red.getGraph().getVertices(); //get all vertices in graph
  vector<Vertex> actual = red.TraversalDFS(); //get output of full graph traversal

  sort(expected.begin(), expected.end()); // sort graph vertices lexicographically
  sort(actual.begin(), actual.end()); // sort full graph traversal lexicographically
  REQUIRE(actual == expected);
}

//Check small test case for comments
TEST_CASE("Entire Graph DFS Traversal - Medium", "[weight=1][DFSTraversal]"){
  Reddit red("tests/medium.csv");
  
  vector<Vertex> expected = red.getGraph().getVertices();
  vector<Vertex> actual = red.TraversalDFS();

  sort(expected.begin(), expected.end()); 
  sort(actual.begin(), actual.end());
  REQUIRE(actual == expected);
}

//Check small test case for comments
TEST_CASE("Entire Graph DFS Traversal - Large #1", "[weight=1][DFSTraversal]"){
  Reddit red("tests/large1.csv");
  
  vector<Vertex> expected = red.getGraph().getVertices();
  vector<Vertex> actual = red.TraversalDFS();

  sort(expected.begin(), expected.end()); 
  sort(actual.begin(), actual.end());
  REQUIRE(actual == expected);
}

//Check small test case for comments
TEST_CASE("Entire Graph DFS Traversal - Large #2", "[weight=1][DFSTraversal]"){
  Reddit red("tests/large2.csv");
  
  vector<Vertex> expected = red.getGraph().getVertices();
  vector<Vertex> actual = red.TraversalDFS();

  sort(expected.begin(), expected.end()); 
  sort(actual.begin(), actual.end());
  REQUIRE(actual == expected);
}