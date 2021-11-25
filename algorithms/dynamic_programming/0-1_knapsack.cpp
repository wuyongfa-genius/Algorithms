// Given weights and values of n items, put these items in a knapsack of capacity W 
// to get the maximum total value in the knapsack. In other words, given two integer 
// arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with 
// n items respectively. Also given an integer W which represents knapsack capacity, 
// find out the maximum value subset of val[] such that sum of the weights of this subset 
// is smaller than or equal to W. You cannot break an item, either pick the complete item 
// or don’t pick it (0-1 property).
#include<bits/stdc++.h>
using namespace std;

int knapsack(const vector<int>&wt, const vector<int>&v, int W)
{
    vector<int>dp(W+1, 0);
    for(int i=0;i<=v.size();++i){//every item can be placed ONLY ONCE
        for(int w=W;w>0;--w){
            if(wt[i]<=w){
                dp[w] = max(dp[w], dp[w-wt[i]]+v[i]);
            }
        }
    }
    return dp[W];
}

int main()
{
    vector<int>value = { 60, 100, 120 };
    vector<int>weight = { 10, 20, 30 };
    int W = 50;
    cout << knapsack(weight, value, W);
    return 0;
}