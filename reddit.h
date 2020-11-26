/**
 * @file reddit.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
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

    private:
    // Graph redditg_;
    // Vertex startvertex_;
    Graph g_;

    

};   
