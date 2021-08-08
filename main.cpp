#include <iostream>
#include <vector>
#include "HeapPQ.h"

using namespace std;

typedef typename HeapPQ<vector<int> >::Position Position;

const int INF = 1923522;
const int N = 6;
vector<vector<int> > G[N];

// Dijkstra settings
int d[N];
int pre[N];

void addEdge(vector<vector<int> > G[], int u, int v, int w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

vector<int> dijkstra(vector<vector<int> > G[], int s) {
    for (int i = 0; i < N; i++) {
        d[i] = INF;
        pre[i] = -1;
    }
    d[s] = 0;
    vector<int> S;
    HeapPQ<vector<int> > Q;
    int idx[N];
    // build heap
    for (int i = 0; i < N; i++) {
        idx[i] = Q.insert({i, d[i]});
    }
    while (!Q.empty()) {
        vector<int> u = Q.min();
        S.push_back(u[0]);
        int deg = G[u[0]].size();
        for (int i = 0; i < deg; i++) {
            vector<int> v = G[u[0]][i];
            // edge relaxation
            int new_dist = d[u[0]] + v[1];
            if (d[v[0]] > new_dist) {
                d[v[0]] = new_dist;
                Position p = Q.pos(idx[v[0]]);
                Q.remove(p);
                idx[v[0]] = Q.insert({v[0], new_dist});
                pre[v[0]] = u[0];
            }
        }
        Q.removeMin();
    }
    return S;
}

int main() {
    addEdge(G, 0, 5, 4);
    addEdge(G, 0, 3, 9);
    addEdge(G, 5, 4, 1);
    addEdge(G, 4, 1, 2);
    addEdge(G, 1, 2, 4);
    addEdge(G, 2, 3, 3);

    vector<int> res = dijkstra(G, 0);
    for (int i = 0; i < N; i++) {
        cout << d[i] << " ";
    }

    return 0;
}