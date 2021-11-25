// Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function that 
// returns cost of minimum cost path to reach (m, n) from (0, 0). Each cell of the matrix 
// represents a cost to traverse through that cell. The total cost of a path to reach (m, n) 
// is the sum of all the costs on that path (including both source and destination). You 
// can only traverse down, right and diagonally lower cells from a given cell, i.e., from a 
// given cell (i, j), cells (i+1, j), (i, j+1), and (i+1, j+1) can be traversed. You may assume 
// that all costs are positive integers.
#include<bits/stdc++.h>
using namespace std;

int min_of_3(int &a, int &b, int &c)
{
    return min(min(a, b), c);
}

int min_cost_path(vector<vector<int>>&C)
{
    int m=C.size(), n=C[0].size();
    for(int i=1;i<m;++i)
        C[i][0] += C[i-1][0];
    for(int j=1;j<n;++j)
        C[0][j] += C[0][j-1];
    for(int i=1;i<m;++i)
        for(int j=1;j<n;++j){
            C[i][j] += min_of_3(C[i-1][j], C[i][j-1], C[i-1][j-1]);
        }
    return C[m-1][n-1];
}

int main()
{   
    int row=3, col=3;
    vector<vector<int>>cost = {  {1, 2, 3},
                              {4, 8, 2},
                              {1, 5, 3} };
 
    cout << min_cost_path(cost) << endl;
    return 0;
}