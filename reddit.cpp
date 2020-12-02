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

using namespace std;


Reddit::Reddit(string filename) : g_() , gT_()// create empty, weighted, and directed graph and its transpose
{
    std::ifstream f(filename); //input file stream - file pointer
    if(!f.is_open()) std::cout << "File not found!" << std::endl; // error message

    std::string str;
    getline(f, str); //skips first line of csv - coloumn headers

    std::string src; // temp string to parse source subreddit
    std::string des; // temp string to parse target subreddit
    std::string sent; // temp string to parse link sentiment - edge weight
    std::string count; // temp string to parse #links averaged - edge label

    while(!f.eof()) // read lines till end of file is reached
    {
        std::getline(f, src, ','); // reads till first comma, inserts data in 'src'
        std::getline(f, des, ','); // reads till second comma, inserts data in 'des' 
        std::getline(f, sent, ','); // reads till third comma, inserts data in 'sent'
        std::getline(f, count, '\n'); // reads till end of line, inserts data in 'count'

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



// void Reddit::BFS(Graph & g_){
//     //std::unordered_map<Vertex, bool> vlabel;
//     //std::unordered_map<Edge, std::string> elabel;
//     int connectedcomp = 0;
//     for(Vertex v : g_.getVertices()){
//         vlabel[v] = false;
//     }
//     for(Edge e: g_.getEdges()){
//         elabel[e] = "UNEXPLORED";
//     }
//     for(Vertex v : g_.getVertices()){
//         if(vlabel[v] = false){
//             BFSHelper(g_, v);
//             connectedcomp++;
//         }
//     }

// }
// void Reddit::BFSHelper(Graph & g_, Vertex v){
//     std::queue<Vertex> vertices;
//     vlabel[v] = true;
//     vertices.push(v);
//     bool cycledetection = false;
//     //Vertex popped;

//     while(!vertices.empty()){
//         v = vertices.front();
//         vertices.pop();
//         for(Vertex w : g_.getAdjacent(v)){
//             if(vlabel[w] == false){
//                 elabel[g_.getEdge(v, w)] = "DISCOVERY";
//                 vlabel[w] = true;
//                 vertices.push(w);
//             }
//             else if(vlabel[w] == true){
//                 elabel[g_.getEdge(v, w)] = "CROSS";
//                 cycledetection = true;
//             }
//         }
//     }
// }

/**
 * Breadth First Search 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return BFS path
 */
vector<Vertex> Reddit::BFS(Vertex src, Vertex goal)
{
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
 * Implementation of Kosaraju's algorithm to find strongly connected components
 
 * @return A vector of vectors of vertices - vector of strongly connected components 
 */
vector<vector<Vertex>> Reddit::SCCs()
{
    vector<vector<Vertex>> res; // Vector to store Strongly Connected Components
    vector<Vertex> vertices = g_.getVertices(); // Gets list of all vertices needed to be explored
    unordered_set<Vertex> visited; // Unordered set to track visited vertices
    stack<Vertex> s; // Stack of vertices to store order of exploration of graph(g_)
    for(size_t i = 0; i < vertices.size(); i++) // iterate over all vertices in graph
    {
        if(visited.find(vertices[i]) == visited.end()) // checks if vertex is unvisted in g_
        {
            DFS(vertices[i], g_, visited, s); // fills stack(s) with vertices reachable via DFS from this vertex
        }
    }

    visited.clear(); // clears unordered set in order to track visited vertices of graph transpose
    stack<Vertex> scc; // Stack of vertices to store SCCs of a given vertex

    while(!s.empty()) // loops till SCCs of each vertex have been found 
    {
        Vertex curr = s.top(); // gets top vertex from exploration order stack
        s.pop(); // removes top vertex from exploration order stack
        if(visited.find(curr) == visited.end()) // checks if vertex is unvisted in gT_
        {
            res.push_back({}); // inserts empty vector of vertices - to be populated by this vertex's SCCs
            DFS(curr, gT_, visited, scc); // fills stack(ssc) with SCCs of this vertex
            while(!scc.empty()) // copies stack(scc) into this vertex's SCCs list(res.back())
            {
                res.back().push_back(scc.top()); // copies top vertex from stack(scc) to this vertex's SCCs list
                scc.pop(); //removes top vertex from stack(scc)
            }
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
void Reddit::DFS(Vertex src, Graph & g, unordered_set<Vertex> & visited, stack<Vertex> & s)
{
    visited.insert(src); // marks vertex as visted
    vector<Vertex> vertex_list = g.getAdjacent(src);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if this adjecent vertex is unvisted
        {
            DFS(vertex_list[i], g, visited, s); // calls DFS recursively on adjecent vertex
        }
    }
    s.push(src); //add vertex to the stack - see parameters for more detailed explanation of utility
}

/**
 * Calls dUtil to find max depth
 * @param src - Source vertex
 * @return Max depth of source node using DFS
 */
int Reddit::maxDepth(Vertex src)
{
    unordered_map<Vertex, int> depth; // initializes depth map
    return dUtil(depth, src, src); // starts recursion for src node
}

/**
 * Calls dUtil to find max depth
 * @param depth - Unordered map that tracks max depth of each node
 * @param node - Current recursive call's vertex
 * @param src - Source vertex
 * @return Max depth of current node using DFS
 */
int Reddit::dUtil(unordered_map<Vertex, int> & depth, Vertex node, Vertex src)
{
    int max = 0; // initializes max depth tracker for current vertex to 0
    vector<Vertex> vertex_list = g_.getAdjacent(node);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++) // iterates over adjecent vertices
    {
        int curr; // initializes max depth tracker for this adjecenct vertex
        if(vertex_list[i] == src) // checks if this adjecent vertex is the source vertex 
        {
            continue; // skips source vertex
        }
        else if(depth.find(vertex_list[i]) == depth.end()) // checks if this adjecent vertex is unvisted
        {
            curr = dUtil(depth, vertex_list[i], src) + 1; // calls dUtil to get max depth for this adjecent vertex
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

/**
 * Calls IDSutil iteratively increasing depth after every iteration 
 * @param src - Source vertex
 * @param goal - Target vertex
 * @return DFS path
 */
vector<Vertex> Reddit::IDS(string src, string goal, int depth)
{
    vector<Vertex> path; // intializes vector to store output path
    unordered_set<Vertex> visited; // initializes set to track visited vertices
    for (int d = 1; d < depth; d++) // iteratively increases search depth
    {
        if(IDSutil(visited, path, src, goal, d)) break; // if goal is found breaks from loop
        path.clear(); // clears path for next IDS
        visited.clear(); // clears visited tracker for next IDS
    }
    return path; //returns empty path if goal not found | returns path of vertices if goal is found
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
    if (depth <= 0){
        return false;
    }
    vector<Vertex> vertex_list = g_.getAdjacent(node);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++)
    {
        if(visited.find(vertex_list[i]) == visited.end()) // checks if vertex is unvisted
        {
            visited.insert(vertex_list[i]); // marks vertex as visted
            path.push_back(vertex_list[i]); // adds vertex to path
            if (IDSutil(visited, path, vertex_list[i], goal, depth - 1)) // recursive call to IDSutil with decreased depth
            {
                return true; // goal found
            }
            else
            {
                path.pop_back(); // removes vertex added from path since DFS was unsuccesful from this node
            }
        }
    }
<<<<<<< HEAD
    return false;
}

void Reddit::StronglyCCUtil(Vertex curr, unordered_map<Vertex, int> dfsnum, unordered_map<Vertex, int> low, stack<Vertex> *st, unordered_map<Vertex, bool> visited) {
    static int time = 0; 
  
    dfsnum[curr] = low[curr] = time; 
    time++;
    st->push(curr); 
    visited[curr] = true; 
  
    vector<Vertex> adj = g_.getAdjacent(curr);
    for (int i = 0 ; i < adj.size() ; i++) { 
        Vertex child = adj[i];
  
        if (dfsnum[child] == NULL) 
        { 
            StronglyCCUtil(child, dfsnum, low, st, visited);
            low[curr]  = min(low[curr], low[child]); 
        } 
  
        else if (visited[child] == true) 
            low[curr]  = min(low[curr], dfsnum[child]); 
    } 

    Vertex w = 0;
    if (low[curr] == dfsnum[curr]){
        result.push_back({});
        while (st->top() != curr){ 
            w = st->top(); 
            result.back().push_back(w);
            visited[w] = false; 
            st->pop(); 
        } 
        w = st->top();
        visited[w] = false; 
        st->pop(); 
    } 
} 

void Reddit::StronglyCC() {
    vector<Vertex> vertices(g_.getVertices());
    unordered_map<Vertex, int> dfsnum;
    unordered_map<Vertex, int> low;
    unordered_map<Vertex, bool> visited;
    stack<Vertex> *st = new stack<Vertex>(); 
  
    for (int i = 0; i < vertices.size(); i++) 
    { 
        dfsnum[vertices[i]] = NULL; 
        low[vertices[i]] = NULL; 
        visited[vertices[i]] = false; 
    } 
  
    for (int i = 0; i < vertices.size(); i++) 
        if (dfsnum[vertices[i]] == NULL) 
            StronglyCCUtil(vertices[i], dfsnum, low, st, visited); 
} 
=======
    return false; // goal not found
}
>>>>>>> 64296e845f879031bb79d02007ed5a19aff9d5e0