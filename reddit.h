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

    Reddit();

    private:
    Graph redditg_;
    Vertex startvertex_;

};   
