/**
 * @file reddit.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include "graph.h"
#include "edge.h"

class Reddit{
    
    public:
    std::unordered_map<Vertex, bool> vlabel;
    std::unordered_map<Edge, std::string> elabel;

    Reddit();
    void BFS(Graph & g_);
    void BFSHelper(Graph & g_, Vertex v);

    vector<Vertex> myBFS(Vertex src, Vertex goal);

    vector<Vertex> IDS(string src, string goal);
    bool IDSutil(unordered_set<Vertex> & visited, vector<Vertex> & path, Vertex node, Vertex goal, int depth);
    int maxDepth(Vertex src);
    int dUtil(unordered_map<Vertex, int> & depth, Vertex node, Vertex src);

    private:
    // Graph redditg_;
    // Vertex startvertex_;
    Graph g_;

    

};   
