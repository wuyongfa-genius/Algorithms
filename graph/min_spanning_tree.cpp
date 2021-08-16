#include "undirected_graph.h"
#include "graph.h"
#include "../disjoint/disjoint_set.h"
#include <algorithm>

typedef pair<int, int> iPair;

bool myCompare(const undirected_Edge &e1, const undirected_Edge &e2)
{
    return e1.weight < e2.weight;
}

void undirected_Graph::kruskalMST()
{ /*algorithm. greedy search, time complexity O(ElogE) or O(ElogV)
    1. Sort all the edges in non-decreasing order of their weight. 
    2. Pick the smallest edge. Check if it forms a cycle with the spanning tree 
        formed so far. If cycle is not formed, include this edge. Else, discard it. 
    3. Repeat step#2 until there are (V-1) edges in the spanning tree.*/
    //make a disjoint set
    Disjoint_Set djset(V);
    //sort edge by weight
    sort(edge.begin(), edge.end(), myCompare);
    vector<undirected_Edge> mst(V - 1); //to store mst
    int i = 0, e = 0;        //record how many edges tried and used
    while (e < V - 1 && i < E)
    {
        //get smallest edge
        undirected_Edge smallestE = edge[i++];
        int x = djset.FIND_SET(smallestE.src);
        int y = djset.FIND_SET(smallestE.dest);
        if (x != y)
        {
            mst[e++] = smallestE;
            djset.UNION(x, y);
        }
    }
    // print the contents of mst to display the built MST
    cout << "Following are the edges in the constructed MST" << endl;
    int minimumCost = 0;
    for (i = 0; i < e; ++i)
    {
        cout << mst[i].src << " -- " << mst[i].dest
             << " == " << mst[i].weight << endl;
        minimumCost += mst[i].weight;
    }
    cout << "Minimum Cost of MST: " << minimumCost << endl;
}

void Graph::primMST(){
    bool inMST[V]={false};//to record if v is in MST
    vector<int> key(V, INT_MAX);//min weight of the edges connecting to v
    vector<int> parent(V, -1);//to store the final MST
    priority_queue<iPair, vector<iPair>, greater<iPair>>pq;
    //initialize vertex 0
    key[0] = 0;
    pq.emplace(key[0], 0);
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        if(inMST[u])
            continue;
        inMST[u] = true;//mark u as in MST
        for(auto i=adj[u].begin();i!=adj[u].end();++i){
            int v=i->v;
            int w=i->w;
            if(!inMST[v]&&key[v]>w){
                key[v] = w;//update key[v] as smaller edge weight
                pq.emplace(key[v], v);//enqueue v in pq.
                parent[v]=  u;//record it in the final MST
            }
        }
    }
    // Print edges of MST using parent array
    cout<<"MST found: "<<endl;
    for (int i = 1; i < V; ++i)
        cout<<parent[i]<<"-->"<<i<<" , ";
}

// Driver code to test kruskal
// int main()
// {
//     /* Let us create following weighted graph
//             10
//         0--------1
//         | \          |
//       6|    \ 5    |15
//         |       \    |
//         2--------3
//             4 
//     */
//     int V = 4; // Number of vertices in graph
//     int E = 5; // Number of edges in graph
//     undirected_Graph graph(V, E);

//     // add edge 0-1
//     graph.addEdge(0, 1, 10);
//     // add edge 0-2
//     graph.addEdge(0, 2, 6);
//     // add edge 0-
//     graph.addEdge(0, 3, 5);
//     // add edge 1-3
//     graph.addEdge(1, 3, 15);
//     // add edge 2-3
//     graph.addEdge(2, 3, 4);

//     graph.kruskalMST();

//     return 0;
// }

// Driver program to test prim
int main()
{
    int V = 9;
    Graph g(V, false);
 
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
 
    g.primMST();
 
    return 0;
}