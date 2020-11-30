/**
 * @file reddit.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <stack>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include "graph.h"
#include "edge.h"

using std::unordered_set;
using std::stack;

class Reddit{
    
    public:
    // std::unordered_map<Vertex, bool> vlabel;
    // std::unordered_map<Edge, std::string> elabel;

    Reddit(string filename);
    // void BFS(Graph & g_);
    // void BFSHelper(Graph & g_, Vertex v);

    vector<Vertex> BFS(Vertex src, Vertex goal);

    vector<vector<Vertex>> SSCs();
    void DFS(Vertex src, Graph & g, unordered_set<Vertex> & visited, stack<Vertex> & s);

    vector<Vertex> IDS(string src, string goal, int depth);
    bool IDSutil(unordered_set<Vertex> & visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth);
    int maxDepth(Vertex src);
    int dUtil(unordered_map<Vertex, int> & depth, Vertex node, Vertex src);

    private:
    // Graph redditg_;
    // Vertex startvertex_;
    Graph g_;
    Graph gT_;

};   
