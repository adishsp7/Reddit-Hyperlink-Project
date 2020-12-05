#include "reddit.h"
#include "graph.h"
#include "edge.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <vector>
#include <unordered_map>

using namespace std;


Reddit::Reddit(string filename) : g_() , gT_()// create empty, weighted, and directed graph and its transpose
{
    ifstream f(filename); //input file stream - file pointer
    if(!f.is_open()) 
    {
        std::cout << "File not found!" << std::endl; // error message
        return;
    }
    string str;
    getline(f, str); //skips first line of csv - coloumn headers

    string src; // temp string to parse source subreddit
    string des; // temp string to parse target subreddit
    string sent; // temp string to parse link sentiment - edge weight
    string count; // temp string to parse #links averaged - edge label


    int num = 0;

    while(1) // loops forever - breaks when end of file is reached
    {
        std::getline(f, src, ','); // reads till first comma, inserts data in 'src'
        std::getline(f, des, ','); // reads till second comma, inserts data in 'des' 
        std::getline(f, sent, ','); // reads till third comma, inserts data in 'sent'
        std::getline(f, count, '\n'); // reads till end of line, inserts data in 'count'
        if(f.eof()) break; // if end of file is reached - breaks

        if(!g_.vertexExists(src)) g_.insertVertex(src); // if source subreddit doesnt exist, insert to graph
        if(!g_.vertexExists(des)) g_.insertVertex(des); // if target subreddit doesnt exist, insert to graph
        if(!g_.edgeExists(src, des)) // if edge connecting src & des doesnt exist:
        {
            bool attempt = g_.insertEdge(src, des); // insert edge
            int w = std::stof(sent) * std::stoi(count); // calculate edge weight
            g_.setEdgeWeight(src, des, w); // set edge weight
            g_.setEdgeLabel(src, des, count); // set edge label
            if(!attempt) std::cout << "Failed to insert edge!" << std::endl; // error message
        }

        // Same process as above for the graphs transpose:

        if(!gT_.vertexExists(src)) gT_.insertVertex(src); // if source subreddit doesnt exist, insert to graph transpose
        if(!gT_.vertexExists(des)) gT_.insertVertex(des); // if target subreddit doesnt exist, insert to graph transpose
        // order of edge is reversed from (src, des) to (des, src) in order to create transpose
        if(!gT_.edgeExists(des, src)) // if edge connecting des & src doesnt exist:
        {
            bool attempt = gT_.insertEdge(des, src); // insert edge
            int w = std::stof(sent) * std::stoi(count); // calculate edge weight
            gT_.setEdgeWeight(des, src, w); // set edge weight
            gT_.setEdgeLabel(des, src, count); // set edge label
            if(!attempt) std::cout << "Failed to insert transpose edge!" << std::endl; // error message
        }
    }

    f.close(); // close .csv file
}

/**
 * Breadth First Search 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return BFS path
 */
vector<Vertex> Reddit::BFS(Vertex src, Vertex goal)
{
    if(!g_.vertexExists(src)) // Checks if Source subreddit exists
    {
        cout << "Source Vertex doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    if(!g_.vertexExists(goal)) // Checks if Goal subreddit exists
    {
        cout << "Target Vertex doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    queue<Vertex> q; //initialize queue to add adjecent vertices
    unordered_map<Vertex, Vertex> prev; // initialize map to track prev vertex
    q.push(src); // add source vertex to queue
    Vertex curr; // initializes current vertex variable

    while(!q.empty()) // loops till all vertices are explored or goal is found
    {
        curr = q.front(); // assigns q front to current vertex
        q.pop(); // removes current vertex from queue
        vector<Vertex> vertex_list = g_.getAdjacent(curr);  // gets a list of adjacent vertices for current vertex
        for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
        {
            if (prev.find(vertex_list[i]) == prev.end()) // checks if this adjecent vertex is unvisted
            {
                prev[vertex_list[i]] = curr; // sets current vertex as previous vertex for this adjecent vertex
                q.push(vertex_list[i]); // adds this adjecent vertex to queue
                if (vertex_list[i] == goal) break; // breaks from for-loop if this adjecent vertex is the goal 
            }
        }
        if (q.back() == goal) break; // breaks from while-loop if the last vertex in the is the goal
    }
    
    vector<Vertex> path; // intializes vector to store output path
    if(q.empty()) return path; // if goal not found returns empty path

    curr = q.back(); // sets current vertex to goal
    path.push_back(curr); // pushes goal in path vector
    while(curr != src) // loops till all the vertices in the path have been pushed
    {
        curr = prev[curr]; // sets current vertex to its previous vertex
        path.push_back(curr); // pushes previous vertex to the path
    }
    reverse(path.begin(), path.end()); // reverses path so the first vertex is source and the last vertex is the goal
    return path; // returns path
}

/**
 * Depth First Search
 * @param src - Source vertex
 * @param visited - Unordered set to keep track of visited nodes
 * @param s - Stack to store traversed nodes
 */
void Reddit::DFS(Vertex src, unordered_set<Vertex> & visited, stack<Vertex> & s)
{
    visited.insert(src); // marks vertex as visted
    vector<Vertex> vertex_list = g_.getAdjacent(src);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if this adjecent vertex is unvisted
        {
            DFS(vertex_list[i], visited, s); // calls DFS recursively on adjecent vertex
        }
    }
    s.push(src); //add vertex to the stack - see parameters for more detailed explanation of utility
}

vector<vector<Vertex>> Reddit::SCCs()
{
    vector<vector<Vertex>> res; // Vector to store Strongly Connected Components
    vector<Vertex> vertices = g_.getVertices(); // Gets list of all vertices needed to be explored
    unordered_set<Vertex> visited; // Unordered set to track visited vertices
    vector<Vertex> s; // Stack of vertices to store order of exploration of graph(g_)
    for(size_t i = 0; i < vertices.size(); i++) // iterate over all vertices in graph
    {
        if(visited.find(vertices[i]) == visited.end()) // checks if vertex is unvisted in g_
        {
            SCCUtil(vertices[i], g_, visited, s); // fills stack(s) with vertices reachable via DFS from this vertex
        }
    }

    visited.clear(); // clears unordered set in order to track visited vertices of graph transpose
    
    while(!s.empty()) // loops till SCCs of each vertex have been found 
    {
        Vertex curr = s.back(); // gets top vertex from exploration order stack
        s.pop_back(); // removes top vertex from exploration order stack
        if(visited.find(curr) == visited.end()) // checks if vertex is unvisted in gT_
        {
            vector<Vertex> scc; // Stack of vertices to store SCCs of a given vertex
            SCCUtil(curr, gT_, visited, scc); // fills stack(ssc) with SCCs of this vertex
            res.push_back(scc);
        }
    }
    return res; // returns list of all strongly connected components for this graph
}

/**
 * DFS utility for strongly connected components
 * @param src - Source vertex
 * @param g - Aliases graph(g_) or graph transpose(gT_)
 * @param visited - Unordered set to keep track of visited nodes
 * @param s - Stack to build order of exploration during non-transpose call and to store SCCs in transpose call
 */
void Reddit::SCCUtil(Vertex src, Graph & g, unordered_set<Vertex> & visited, vector<Vertex> & s)
{
    visited.insert(src); // marks vertex as visted
    vector<Vertex> vertex_list = g.getAdjacent(src);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if this adjecent vertex is unvisted
        {
            SCCUtil(vertex_list[i], g, visited, s); // calls DFS recursively on adjecent vertex
        }
    }
    s.push_back(src); //add vertex to the stack - see parameters for more detailed explanation of utility
}



/**
 * Calls IDSutil iteratively increasing depth after every iteration 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return DFS path
 */
vector<Vertex> Reddit::IDS(string src, string goal, int depth)
{
    if(!g_.vertexExists(src)) // Checks if Source subreddit exists
    {
        cout << "Source Vertex doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    if(!g_.vertexExists(goal)) // Checks if Goal subreddit exists
    {
        cout << "Target Vertex doesn't exist!" << endl; // Prints error message
        return vector<Vertex>(); // Returns empty vector of vertices
    }

    vector<Vertex> path; // intializes vector to store output path
    unordered_set<Vertex> visited; // initializes set to track visited vertices
    for (int d = 0; d < depth; d++) // iteratively increases search depth
    { 
        path.push_back(src); // adds source to path
        if(IDSutil(visited, path, src, goal, d)) break; // if goal is found breaks from loop
        path.clear(); // clears path for next IDS
        visited.clear(); // clears visited tracker for next IDS
    }
    return path;
}

/**
 * perform iterative deepening search from a starting node until 
 * goal is found or until the depth goes out of the given bound
 * @param visited - Unoreded set to track visted nodes - passed as reference
 * @param path - Vector of vertices that store the path traversed - passed as reference
 * @param node - Source Vertex
 * @param goal - Target Vertex
 * @param depth - Upper depth limit
 * @return whether target successfully found
 */
bool Reddit::IDSutil(unordered_set<Vertex> & visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth) {  
    if (node == goal){  // if target subreddit found, return true
        return true;
    }
    if (depth <= 0){ //if depth limit reached return false
        return false;
    }
    visited.insert(node); // marks current vertex as visted
    vector<Vertex> vertex_list = g_.getAdjacent(node);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++)
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if vertex is unvisted
        {
            path.push_back(vertex_list[i]); // adds vertex to path
            if (IDSutil(visited, path, vertex_list[i], goal, depth - 1)) // recursive call to IDSutil with decreased depth
            {
                return true; // goal found
            }
            path.pop_back(); // removes vertex added from path since DFS was unsuccesful from this node
        }
    }
    visited.erase(node); // marks current vertex as unvisted
    return false; //goal not found
}
/*
 * Calls StronglyCCUtil to find strongly connected components
 * @param curr - Current vertex being observed
 * @param dfsnum - Unordered map that keeps track of which order each node was visited
 * @param low - Unordered map that is used to see which nodes are in the same compnent
 * @return Max depth of current node using DFS
 */
void Reddit::StronglyCCUtil(Vertex curr, unordered_map<Vertex, int> & dfsnum, unordered_map<Vertex, int> & low, stack<Vertex> & st, unordered_map<Vertex, bool> & visited) {
    static int time = 0; 
  
    dfsnum[curr] = low[curr] = ++time; 
    st.push(curr); 
    visited[curr] = true; 
  
    vector<Vertex> adj = g_.getAdjacent(curr);
    for (unsigned i = 0 ; i < adj.size() ; i++) { 
        Vertex child = adj[i];
  
        if (dfsnum[child] == -1) { 
            StronglyCCUtil(child, dfsnum, low, st, visited);
            low[curr]  = min(low[curr], low[child]); 
        } 
  
        else if (visited[child] == true) 
            low[curr]  = min(low[curr], dfsnum[child]); 
    } 
    Vertex w;
    if (low[curr] == dfsnum[curr]){
        result.push_back({});
        while (st.top() != curr){ 
            w = st.top();
            result.back().push_back(w);
            visited[w] = false;
            st.pop(); 
        } 
        w = st.top();
        result.back().push_back(w);
        visited[w] = false; 
        st.pop(); 
    } 
} 

vector<vector<Vertex>> Reddit::StronglyCC() {
    vector<Vertex> vertices = g_.getVertices();
    unordered_map<Vertex, int> dfsnum;
    unordered_map<Vertex, int> low;
    unordered_map<Vertex, bool> visited;
    stack<Vertex> st;
  
    for (unsigned i = 0; i < vertices.size(); i++) { 
        dfsnum[vertices[i]] = -1; 
        low[vertices[i]] = -1; 
        visited[vertices[i]] = false; 
    } 

    for (unsigned i = 0; i < vertices.size(); i++){
        if (dfsnum[vertices[i]] == -1){
            StronglyCCUtil(vertices[i], dfsnum, low, st, visited);
        }
    }
    return result;
} 

void Reddit::printPath(vector<Vertex> vertices)
{
  if(vertices.empty()) 
  {
    std::cout << "Empty Path!" << std::endl;
    return;
  }

  for(auto it = vertices.rbegin(); it != vertices.rend(); ++it)
  {
    cout << (*it) << " ";
  }
  std::cout << std::endl;
}

const Graph & Reddit::getGraph() const{
    return g_;
}

const Graph & Reddit::getTranspose() const{
    return gT_;
}
