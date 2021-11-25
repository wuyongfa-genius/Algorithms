#include <iostream>
#include <list>
#include <queue>
#include <stack>
#pragma once
using namespace std;

struct Edge
{
    int v; //target vertex
    int w; //weight
    Edge(int _v = 0, int _w = 1) : v(_v), w(_w) {}
};

class Graph
{
    int V; //num of vertices
    list<Edge> *adj;
    bool directed;
    bool isCyclicUtil_directed(int, int[]);
    bool isCyclic_directed();
    bool isCyclicUtil_undirected(int, bool[], int);
    bool isCyclic_undirected();
    void topological_sort_util_DFS(int, bool*, stack<int>&);
    void find_all_topological_sort_util(vector<int>&, bool*, int*);
    bool exist_path_over_k_from_src_util(int, int, bool*);

public:
    Graph(int, bool);
    int num_vertices()const{return V;}
    list<Edge>& getEdgeof(int u)const{return adj[u];}
    void addEdge(int, int, int);
    void BFS(int);
    void iterative_DFS(int);
    void DFS(int, bool*);
    void paths_s_t_DFS(int, int, vector<int>&, bool*visited);
    bool isCyclic();
    bool isCyclic_by_djset();
    void topological_sort_DFS();
    void topological_sort_kahn();
    void find_all_topological_sort();
    void longest_path_from_src(int);
    void shortest_path_from_src(int);
    void primMST();
    bool exist_path_over_k_from_src(int, int);
    ~Graph();
};
Graph::Graph(int V, bool directed=true)
{
    this->V = V;
    this->directed = directed;
    adj = new list<Edge>[V];
}

Graph::~Graph()
{
    for (int i = 0; i < V; ++i)
        adj[i].clear();
    adj = NULL;
}

void Graph::addEdge(int u, int v, int w=1)
{
    adj[u].emplace_back(v, w);
    if(!directed)
        adj[v].emplace_back(u, w);
}

void Graph::BFS(int s){
    bool visited[V]={false};
    queue<int>q;
    q.emplace(s);
    visited[s] = true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout<<u<<',';
        list<Edge>::iterator i;
        for(i=adj[u].begin(); i!=adj[u].end();++i){
            if(!visited[i->v]){
                visited[i->v] = true;
                q.emplace(i->v);
            }
        }
    }
}

void Graph::DFS(int s, bool* visited){
    visited[s] = true;
    cout<<s<<',';
    list<Edge>::iterator i;
    for(i=adj[s].begin(); i!=adj[s].end();++i){
        if(!visited[i->v]){
            DFS(i->v, visited);
        }
    }
}

void Graph::iterative_DFS(int s){
    bool visited[V]={false};
    stack<int>stk;
    stk.emplace(s);
    visited[s] = true;
    while(!stk.empty()){
        int u=stk.top();
        stk.pop();
        cout<<u<<',';
        list<Edge>::iterator i;
        for(i=adj[u].begin(); i!=adj[u].end();++i){
            if(!visited[i->v]){
                visited[i->v] = true;
                stk.emplace(i->v);
            }
        }
    }
}

// // Driver program to test methods of graph class
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

//     // cout << "Following is Breadth First Traversal "
//     //      << "(starting from vertex 2) \n";
//     // g.BFS(2);

//     cout << "Following is Depth First Traversal "
//          << "(starting from vertex 2) \n";
//     // bool visited[g.num_vertices()]={false};
//     // g.DFS(2, visited);
//     g.iterative_DFS(2);
 
//     return 0;
// }