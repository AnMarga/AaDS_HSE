#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, int& k) {
    visited[node] = true;
    k += 1;
    for (int i = 0; i < graph.size(); ++i)
        if ((visited[i] == false) and (graph[node][i] == 1))
            dfs(i, graph, visited, k);
}

int main() {
    int v, e, x, y, k = 0;  //вершины/рёбра/вводящиеся вершины ребра/количество вершин в компоненте связности
    cin >> e >> v;
    vector<vector<int>> graph(e, vector<int>(e, 0));
    vector<bool> visited(e, false);
    
    for (int i = 0; i < v; ++i) {
        cin >> x >> y;
        graph[x-1][y-1] = 1;
        graph[y-1][x-1] = 1;
    }

    /*
    for (size_t i = 0; i < e; ++i) {
        for (size_t j = 0; j < e; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    */

    dfs(0, graph, visited, k); 

    cout << k << "\n";
    for (int i = 0; i < e; ++i) {
        if (visited[i]) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}