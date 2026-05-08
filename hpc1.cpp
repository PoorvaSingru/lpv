#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
vector<vector<int>> g;
vector<int> vis;
// BFS
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
#pragma omp parallel for
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i];
#pragma omp critical
            if (!vis[v])
                vis[v] = 1, q.push(v);
        }
    }
}
// DFS
void dfs(int u)
{
    cout << u << " ";
    vis[u] = 1;
#pragma omp parallel for
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
#pragma omp critical
        if (!vis[v])
            dfs(v);
    }
}
int main()
{
    int n, e, u, v;
    cout << "Nodes & edges: ";
    cin >> n >> e;
    g.resize(n);
    vis = vector<int>(n, 0);
    cout << "Edges:\n";
    for (int i = 0; i < e; i++)
        cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    cout << "BFS: ";
    bfs(0);
    vis = vector<int>(n, 0);
    cout << "\nDFS: ";
    dfs(0);
}