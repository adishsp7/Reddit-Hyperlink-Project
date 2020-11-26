#include "reddit.h"
#include "graph.h"
#include "edge.h"

#include <iostream>
//#include <list>
//#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

/**
 * perform iterative deepening search from a starting node until
 * goal is found or until the depth goes out of the given bound
 * @param g_ - our reddit graph
 * @param node - source node
 * @param goal - target node
 * @param depth - upper depth limit
 * @return whether target successfully found
 */
bool Reddit::IDS(string node, string goal, int depth) {
    if (node == goal){  // if target subreddit found, return true
        return true;
    }
    if (depth <= 0){
        return false;
    }
    vector<Vertex> vertex_list = g_.getAdjacent(node);  // get a list of adjacent vertices
    for (size_t i = 0; i < vertex_list.size(); i++){
        if (IDS(vertex_list[i], goal, depth - 1) == true){
            return true;
        }
    }
    return false;
}