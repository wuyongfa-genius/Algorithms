#include <iostream>
#pragma once
using namespace std;

class Disjoint_Set
{
    int n; //total items
    int *parent, *rank;
    void LINK(int, int);

public:
    Disjoint_Set(int);
    int FIND_SET(int);
    void UNION(int, int);
    ~Disjoint_Set();
};

Disjoint_Set::Disjoint_Set(int n)
{
    this->n = n;
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

Disjoint_Set::~Disjoint_Set()
{
    delete[] parent;
    parent = NULL;
    delete[] rank;
    rank = NULL;
}

int Disjoint_Set::FIND_SET(int x)
{
    //optimized path compression
    if (parent[x] != x)
        parent[x] = FIND_SET(parent[x]);
    return parent[x];
}

void Disjoint_Set::LINK(int x, int y)
{
    // union by rank
    if (rank[x] < rank[y])
        parent[x] = y;
    else
    {
        if (rank[x] == rank[y])
            ++rank[x];
        parent[y] = x;
    }
}

void Disjoint_Set::UNION(int x, int y)
{
    LINK(FIND_SET(x), FIND_SET(y));
};
