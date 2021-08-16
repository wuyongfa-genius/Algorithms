#include "graph.h"
#include "is_cyclic.cpp"

void Graph::topological_sort_util_DFS(int src, bool *visited, stack<int> &Stack)
{
    visited[src] = true;
    for (auto i = adj[src].begin(); i != adj[src].end(); ++i)
    {
        if (!visited[i->v])
            topological_sort_util_DFS(i->v, visited, Stack);
    }
    Stack.emplace(src); //all the descendants of src have been traversed
}

void Graph::topological_sort_DFS()
{
    //A DFS based algorithm
    bool visited[V] = {false};
    stack<int> Stack;
    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
            topological_sort_util_DFS(i, visited, Stack);
    }
    //print stack
    cout << "A topological sort starting from " << Stack.top() << " is : ";
    while (!Stack.empty())
    {
        cout << Stack.top() << "-->";
        Stack.pop();
    }
}

void Graph::topological_sort_kahn()
{
    //Kahn's algorithm, an indegree-based algorithm
    vector<int> indegrees(V, 0);
    //initialize ingedrees of all vertices
    for (int i = 0; i < V; ++i)
        for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
            ++indegrees[j->v];
    queue<int> q; //store zero-indegree vertices
    // first enqueue all zero-indegree vertices
    for (int i = 0; i < V; ++i)
        if (indegrees[i] == 0)
            q.emplace(i);
    vector<int> topo; //to store final topo results
    int cnt = 0;      //to count if all vertices have been traversed
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.emplace_back(u);
        ++cnt;
        for (auto v = adj[u].begin(); v != adj[u].end(); ++v)
            if (--indegrees[v->v] == 0)
                q.emplace(v->v);
    }
    // Check if there was a cycle
    if (cnt != V)
    {
        cout << "There exists a cycle in the graph\n";
        return;
    }
    // Print topological order
    cout << "A topological sort starting from " << topo[0] << " is : ";
    for (auto &i : topo)
        cout << i << "-->";
}

void Graph::find_all_topological_sort_util(vector<int> &res, bool *visited, int *indegrees)
{
    bool find_one = true; //flag to record if we have find one topo sort of the whole graph.
    // start from every zero-indegree vertex to find possible solution.
    for (int i = 0; i < V; ++i)
    {
        if (indegrees[i] == 0 && !visited[i])
        {
            visited[i] = true;
            res.emplace_back(i);
            for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
            {
                --indegrees[j->v];
            }
            find_all_topological_sort_util(res, visited, indegrees);
            //backtrack, mirror code of above
            for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
            {
                ++indegrees[j->v];
            }
            res.pop_back();
            visited[i] = false;
            find_one = false; //there are still some vertices not visited.
        }
    }
    if (find_one)
    { // all vertices have been visited
        cout << "One possible topo sort is : ";
        for (auto &i : res)
            cout << i << "-->";
        cout << endl;
    }
}

void Graph::find_all_topological_sort()
{
    int indegrees[V] = {0};
    for (int i = 0; i < V; ++i)
        for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
            ++indegrees[j->v];
    bool visited[V] = {false};
    vector<int> res;
    find_all_topological_sort_util(res, visited, indegrees);
}

// Driver Code
// int main()
// {
//     // Create a graph given in the above diagram
//     Graph g(6);
//     g.addEdge(5, 2);
//     g.addEdge(5, 0);
//     g.addEdge(4, 0);
//     g.addEdge(4, 1);
//     g.addEdge(2, 3);
//     g.addEdge(3, 1);

//     cout << "Following is a Topological Sort of the given "
//             "graph \n";

//     // Function Call
//     // g.topological_sort_DFS();
//     // g.topological_sort_kahn();
//     // g.find_all_topological_sort();
//     g.isCyclic_by_djset()?
//     cout<<"Contains a cycle"<<endl:
//     cout<<"Doesn't contain a cycle"<<endl;
//     return 0;
// }