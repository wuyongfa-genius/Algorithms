#include "graph.h"
using namespace std;

void Graph::paths_s_t_DFS(int src, int tgt, vector<int> &paths, bool *visited)
{
    visited[src] = true;     // mark cur vertex as visited
    paths.emplace_back(src); // push cur vertex to path
    if (src == tgt)
    {
        cout << "A path from " << src << " to " << tgt << " found: ";
        for (auto &i : paths)
            cout << i << "-->";
        cout << endl;
    }
    else
    { // traverse vertex adjacent to src
        for (auto i = adj[src].begin(); i != adj[src].end(); ++i)
        {
            if (!visited[i->v])
                paths_s_t_DFS(i->v, tgt, paths, visited);
        }
    }
    visited[src] = false;
    paths.pop_back();
}

bool Graph::exist_path_over_k_from_src_util(int src, int rest, bool*visited){
    if(rest<=0)
        return true;
    for(auto i:adj[src]){
        if(!visited[i.v]){
            visited[i.v] = true;
            //if there exists a path from v, directly return true;
            if(exist_path_over_k_from_src_util(i.v, rest-i.w, visited))
                return true;
            visited[i.v] = false; //backtrack
        }
    }
    return false;
}

bool Graph::exist_path_over_k_from_src(int src, int k){
    bool visited[V]={false};
    visited[src] = true;
    return exist_path_over_k_from_src_util(src, k, visited);
}

// Driver program to test paths from src to tgt
// int main()
// {
//     // Create a graph given in the above diagram
//     Graph g(4);
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(0, 3);
//     g.addEdge(2, 0);
//     g.addEdge(2, 1);
//     g.addEdge(1, 3);

//     int s = 2, d = 3;
//     vector<int> paths;
//     bool visited[g.num_vertices()] = {false};
//     cout << "Following are all different paths from " << s << " to " << d << endl;
//     g.paths_s_t_DFS(s, d, paths, visited);

//     return 0;
// }

// Driver program to test path over k from src
int main()
{
    // create the graph given in above fugure
    int V = 9;
    Graph g(V, false);
 
    //  making above shown graph
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
 
    int src = 0;
    int k = 62;
    g.exist_path_over_k_from_src(src, k)? cout << "Yes\n" :
                             cout << "No\n";
 
    k = 60;
    g.exist_path_over_k_from_src(src, k)? cout << "Yes\n" :
                             cout << "No\n";
 
    return 0;
}