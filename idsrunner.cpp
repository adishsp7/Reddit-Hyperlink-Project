#include "reddit.h"
#include <vector>
#include <string>

int main(int argc, char** argv) 
{
    if(argc != 5)
    {
        std::cout << "Function requires arguments: [Filepath to data set] [Source Subreddit] [Target Subreddit] [Search Depth]" << std::endl; 
    }
    Reddit red(argv[1]);
    vector<Vertex> path1 = red.IDS(argv[2], argv[3], atoi(argv[4]));
    std::cout << "IDS path: "; 
    red.printPath(path1);
    std::cout << "Path sentiment: " << red.getSentiment(path1) << std::endl;
}
