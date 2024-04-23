#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph{

    private:
        int V;
        vector<vector<int>> adj;

    public:
        Graph(int V){
            this->V=V;
            adj.resize(V);
        }

    void addEdge(int v, int w){
        adj[v].push_back(w);
    }

    void DFS(int v){
        vector<bool> visited(V, false);
        ParallelDFSUtil(v, visited);
    }

    void ParallelDFSUtil(int v, vector<bool> &visited){
        visited[v] = true;
        cout<<v<<" ";
        
        #pragma omp parallel for
        for(int u: adj[v]){
            if(!visited[u]){
                ParallelDFSUtil(u, visited);
            }
        }
    }

};

int main(){

    Graph g(7);

    g.addEdge(0,1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Depth First Search (DFS) starting from vertex 0: ";
    g.DFS(0);
    cout << endl;

    return 0;
}