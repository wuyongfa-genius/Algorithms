//Dijkstra’s Shortest Path Algorithm using priority_queue of STL
/*algorithm
1) Create a Min Heap of size V where V is the number of vertices in the given graph. Every node
    of min heap contains vertex number and distance value of the vertex. 
2) Initialize Min Heap with source vertex as root (the distance value assigned to source vertex is 0). 
    The distance value assigned to all other vertices is INF (infinite). 
3) While Min Heap is not empty, do following 
…..a) Extract the vertex with minimum distance value node from Min Heap. Let the extracted vertex be u. 
…..b) For every adjacent vertex v of u, check if v is in Min Heap. If v is in Min Heap and distance value 
        is more than weight of u-v plus distance value of u, then update the distance value of v.
*/
#include<bits/stdc++.h>
#include"graph.h"

typedef pair<int, int> Pair;

void Graph::shortest_path_from_src(int src){
    priority_queue<Pair, vector<Pair>, greater<Pair>>pq;//a node is (weight, dst)
    vector<int> dists(V, INT_MAX); //to record sortest paths from src to every other vertices
    vector<int> visited(V, false); //to record if v has been visited
    dists[src] = 0; // initialize src to src distance as 0
    pq.emplace(dists[src], src);
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        visited[u] = true;
        for(auto i=adj[u].begin();i!=adj[u].end();++i){
            int w=i->w, v=i->v;
            if(!visited[v] && dists[u]+w<dists[v]){
                dists[v] = dists[u]+w;
                pq.emplace(dists[v], v);
            }
        }
    }
    //print shortest paths from src to any other vertex
    for(int i=0;i<V;++i){
        cout<<"shortest path from "<<src<<" to "<<i<<" is "<<dists[i]<<endl;
    }
}

// Driver program to test methods of graph class
int main()
{
    int V = 9;
     Graph g(9, false);
  
    // making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
  
    g.shortest_path_from_src(0);
  
    return 0;
}