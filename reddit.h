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
    Reddit(string filename);
    vector<Vertex> BFS(Vertex src, Vertex goal);
    vector<Vertex> IDS(string src, string goal, int depth);
    vector<vector<Vertex>> SCCs();
    vector<vector<Vertex>> StronglyCC();
    // void DFS(Vertex src, const Graph & g, unordered_set<Vertex> & visited, stack<Vertex> & s);
    const Graph & getGraph() const;
    const Graph & getTranspose() const;

    // bool Reddit::IDS(string node, string goal, int depth);

    private:
    void StronglyCCUtil(Vertex u, unordered_map<Vertex, int> & disc, unordered_map<Vertex, int> & low, stack<Vertex> & st, unordered_map<Vertex, bool> & stackMember);
    void DFS(Vertex src, Graph & g, unordered_set<Vertex> & visited, stack<Vertex> & s);
    bool IDSutil(unordered_set<Vertex> visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth);
    
    Graph g_;
    vector<vector<Vertex>> result;
    Graph gT_;

    

};   
