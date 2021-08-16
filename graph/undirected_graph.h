#include <iostream>
#include <vector>
#pragma once
using namespace std;

struct undirected_Edge
{
    int src, dest, weight;
    undirected_Edge(int s = 0, int d = 0, int w = 0) : src(s), dest(d), weight(w) {}
};

class undirected_Graph
{
    int V;             //num of vertices
    int E;             //num of edges
    vector<undirected_Edge> edge; //array of edges
public:
    undirected_Graph(int, int);
    ~undirected_Graph();
    void addEdge(int, int, int);
    void kruskalMST();
};

undirected_Graph::undirected_Graph(int V, int E)
{
    this->V = V;
    this->E = E;
}

undirected_Graph::~undirected_Graph()
{
    edge.clear();
}

void undirected_Graph::addEdge(int u, int v, int w)
{
    edge.emplace_back(u, v, w);
}
