/*cpp to detect whether there is a cycle in the graph.
WHITE : Vertex is not processed yet. Initially, all vertices are WHITE.
GRAY: Vertex is being processed (DFS for this vertex has started, but not finished which
    means that all descendants (in DFS tree) of this vertex are not processed yet (or this
    vertex is in the function call stack)
BLACK : Vertex and all its descendants are processed. While doing DFS, if an edge is
    encountered from current vertex to a GRAY vertex, then this edge is back edge and hence there is a cycle. 
*/
#include "graph.h"
#include "../disjoint/disjoint_set.h"

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

bool Graph::isCyclicUtil_directed(int u, int color[])
{
    color[u] = GRAY; //mark cur vertex as processed (start DFS from this vertex)
    for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        if (color[i->v] == GRAY) //there is a back edge.
            return true;
        if (color[i->v] == WHITE && isCyclicUtil_directed(i->v, color)) // there is a cycle in descendents of v;
            return true;
    }
    color[u] = BLACK; //cur vertex and all of its descendents has been processed.
    return false;
}

bool Graph::isCyclic_directed()
{
    int color[V] = {WHITE};
    for (int i = 0; i < V; ++i)
    {
        if (color[i] == WHITE && isCyclicUtil_directed(i, color))
            return true;
    }
    return false;
}

bool Graph::isCyclicUtil_undirected(int u, bool visited[], int prev)
{
    visited[u] = true;
    for(auto i=adj[u].begin();i!=adj[u].end();++i){
        if(!visited[i->v]){
            if(isCyclicUtil_undirected(i->v, visited, u))
                return true;
        }
        else if(i->v!=prev)
            return true;
    }
    // visited[u] = false; //not necessary
    return false;
}

bool Graph::isCyclic_undirected(){
    bool visited[V]={false};
    for(int i=0;i<V;++i){
        if(!visited[i] && isCyclicUtil_undirected(i, visited, -1))
            return true;
    }
    return false;
}

bool Graph::isCyclic(){
    if(directed)
        return isCyclic_directed();
    else  return isCyclic_undirected();
}

bool Graph::isCyclic_by_djset(){
    Disjoint_Set dj(V);
    for(int i=0;i<V;++i){
        for(auto j=adj[i].begin();j!=adj[i].end();++j){
            int x = dj.FIND_SET(i);
            int y = dj.FIND_SET(j->v);
            if(x==y)
                return true;
            dj.UNION(x, y);
        }
    }
    return false;
}

// Driver code to test directed graph
// int main()
// {
//     // Create a graph given in the above diagram
//     Graph g(4);
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 2);
//     g.addEdge(2, 0);
//     g.addEdge(2, 3);
//     g.addEdge(3, 3);

//     if (g.isCyclic_by_djset())
//         cout << "Graph contains cycle";
//     else
//         cout << "Graph doesn't contain cycle";

//     return 0;
// }

// Driver program to test undirected graph
// int main()
// {
//     Graph g1(5, false);
//     g1.addEdge(1, 0);
//     g1.addEdge(0, 2);
//     g1.addEdge(2, 1);
//     g1.addEdge(0, 3);
//     g1.addEdge(3, 4);
//     g1.isCyclic()?
//        cout << "Graph contains cycle\n":
//        cout << "Graph doesn't contain cycle\n";
 
//     Graph g2(3, false);
//     g2.addEdge(0, 1);
//     g2.addEdge(1, 2);
//     g2.isCyclic_by_djset()?
//        cout << "Graph contains cycle\n":
//        cout << "Graph doesn't contain cycle\n";
 
//     return 0;
// }