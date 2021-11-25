// Given two strings str1 and str2 and below operations that can performed on str1. Find
// minimum number of edits (operations) required to convert ‘str1’ into ‘str2’.
// 1.Insert
// 2.Remove
// 3.Replace
// All of the above operations are of equal cost.
#include <bits/stdc++.h>
using namespace std;

int min_of_3(int &a, int &b, int &c)
{
    return min(min(a, b), c);
}

int min_edit_distance(const string &X, const string &Y)
{
    int m = X.size(), n = Y.size();
    if (m < n)
        return min_edit_distance(Y, X);
    int dp[2][n + 1];
    bool cur_row;
    for (int i = 0; i <= m; ++i)
    {
        cur_row = i & 1;
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0)
                dp[0][j] = j; //need to inert j times
            if (j == 0)
                dp[cur_row][0] = i; //need to remove i times
            else if (X[i - 1] == Y[j - 1])
                dp[cur_row][j] = dp[1 - cur_row][j - 1];
            else
                dp[cur_row][j] = 1 + min_of_3(dp[1 - cur_row][j], dp[cur_row][j - 1], dp[1 - cur_row][j - 1]);
        }
    }
    return dp[cur_row][n];
}

// Driver program
int main() {
     
  string str1 = "voldemort";
  string str2 = "dumbledore";
                 
  cout<<"Min Edit distance is "<<min_edit_distance(str1, str2);
  return 0;
     
  //     This code is a contribution of Bhavneet Singh
 
}