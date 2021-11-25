//Given a value V, if we want to make change for V cents, and we have infinite
//supply of each of C = { C1, C2, .. , Cm} valued coins, what is the minimum number
//of coins to make the change? If it’s not possible to make change, print -1.
#include <bits/stdc++.h>
using namespace std;

int minCoins(const vector<int> &C, int change)
{
    vector<int> dp(change + 1, INT_MAX); //to store minCoin of change value i
    dp[0] = 0;
    for (int v = 1; v <= change; ++v)
    {
        for (int j = 0; j < C.size(); ++j) //every coin can be used as many as you need
        {
            if (C[j] <= v)
            {
                if (dp[v - C[j]] != INT_MAX && dp[v - C[j]] + 1 < dp[v])
                    dp[v] = dp[v - C[j]] + 1;
            }
        }
    }
    return dp[change] == INT_MAX ? -1 : dp[change];
}

// Driver program to test above function
int main()
{
    vector<int> coins = {9, 6, 5, 1};
    int V = 11;
    cout << "Minimum coins required is "
         << minCoins(coins, V);
    return 0;
}