#include "reddit.h"
#include <vector>

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        std::cout << "Function requires arguments: [Filepath to data set] [Source Subreddit] [Target Subreddit]" << std::endl; 
    }
    Reddit red(argv[1]);
    vector<Vertex> path1 = red.BFS(argv[2], argv[3]);
    std::cout << "BFS path: "; 
    red.printPath(path1);
    std::cout << "Path sentiment: " << red.getSentiment(path1) << std::endl;
}
