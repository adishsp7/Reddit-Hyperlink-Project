#include <iostream>
#include <list>
#include <unordered_map>
#include <cstring>
using namespace std;

class Graph {
    // adjacency list
    // using hash table, we're mapping a string (key) to a list of pair (value)
    // the key is our source subreddit, and the value is a list of a pair (target subreddit, edge weight)
    unordered_map<string, list<pair<string, int>>> l;
    public:
        void addEdge(string x, string y, int weight){
            l[x].push_back(make_pair(y, weight));
        }
        // just for printing/iterative purpose
        /*void printAdjList(){
            // iterate over all keys
            for (auto p:l){
                string city = p.first;
                list<pair<string, int>> nbrs = p.second;
                cout<<city<<"->";

                for (auto nbr:nbrs){
                    string dest = nbr.first;
                    int wt = nbr.second;
                    cout<<dest<<" "<<wt<<","<<endl;
                }
            }
        }*/

};

int main() {
    Graph g;
    //g.addEdge("source", "target", weight)
    // maybe reading through the csv we could have for each row, g.addEdge(index[0], index[1], index[2])
    g.addEdge("A", "B", 1); // example
}







/*
class Graph {
    int V;
    // array of list
    list<int> *l;
    public:
        // V = number of vertices
        Graph(int V){
            this->V = V;
            // l = new list of size V
            l = new list<int>[V];
        }

        void addEdge(int x, int y){
            l[x].push_back(y);
            l[y].push_back(x);
        }
        void printAdjList(){
            for (int i=0; i < V; i++){
                cout<<"vertex "<<i<<"->";
                for (int nbr:l[i]){
                    cout<<nbr<<",";
                }
                cout<<endl;
            }
        }
};

int main() {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(2,3);
    g.addEdge(1,2);

    return 0;
}
*/

