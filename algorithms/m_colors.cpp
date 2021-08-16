//C++ program to solve m-color problem, which is using m colors to 
//paint a n-vertices graph such that every adjacent vertex has differents colors
#include <bits/stdc++.h>
#include "../graph/graph.h"

bool canPaint(const Graph&g, vector<int>colors, int vertices, int m){
    bool visited[vertices]={false};
    int maxColors=1;
    queue<int>q;
    q.emplace(0);
    visited[0] = true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto i=g.getEdgeof(u).begin();i!=g.getEdgeof(u).end();++i){
            if(colors[u]==colors[i->v])
                ++colors[i->v];
            maxColors = max(maxColors, colors[i->v]);
            if(maxColors>m)
                return false;
            if(!visited[i->v]){
                visited[i->v] = true;
                q.emplace(i->v);
            }
        }
    }
    return true;
}

// Driver code
int main()
{

    int n = 4;
    bool graph[n][n] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}};
    int m = 3; // Number of colors
    vector<int>colors(n, 1);
    Graph g(n, false);

    // Add edges to each node as per given input
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (graph[i][j])
                g.addEdge(i, j);
        }
    }

    // Display final answer
    cout << canPaint(g, colors, n, m);
    cout << "\n";

    return 0;
}