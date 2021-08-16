#include "graph.h"
#include "topological_sort.cpp"

void Graph::longest_path_from_src(int src){
    stack<int>Stack;//store topo sort result;
    bool visited[V]={false};
    for(int i=0;i<V;++i){
        if(!visited[i])
            topological_sort_util_DFS(i, visited, Stack);
    }
    int dists[V]={INT_MIN}; //init distances from src to v as neg inf
    dists[src] = 0; // dist from src to itself is 0
    while(!Stack.empty()){//pop according to topo result
        int u=Stack.top();
        Stack.pop();
        //update dists of all vertices adjacent to u
        for(auto v=adj[u].begin();v!=adj[u].end();++v){
            if(dists[v->v]<dists[u]+v->w)
                dists[v->v] = dists[u]+v->w;
        }
    }
    //print distances
    cout<<"Longest paths from "<<src<<" have been found:"<<endl;
    for(int i=0;i<V;++i){
        cout<<"Longest path from "<<src<<" to "<<i<<" is "<<dists[i]<<endl;
    }
}

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram.
    // Here vertex numbers are 0, 1, 2, 3, 4, 5 with
    // following mappings:
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
   
    int s = 1;
    cout << "Following are longest distances from "
            "source vertex "
         << s << " \n";
    g.longest_path_from_src(s);
   
    return 0;
}