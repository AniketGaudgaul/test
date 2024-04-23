#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V; // Set the number of vertices
        adj.resize(V); // Resize the adjacency list
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v's list
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++) {
                int u = adj[v][i];

                    #pragma omp critical
                    {
                        if (!visited[u]) { // Double-check to prevent race conditions
                            visited[u] = true;
                            q.push(u);
                        }
                    }
                
            }
        }
    }
};

int main() {
    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
    g.parallelBFS(0);
    cout << endl;

    return 0;
}
