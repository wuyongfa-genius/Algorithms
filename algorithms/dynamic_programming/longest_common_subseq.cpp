// LCS Problem Statement: Given two sequences, find the length of longest subsequence
// present in both of them. A subsequence is a sequence that appears in the same relative
// order, but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”,
// .. etc are subsequences of “abcdefg”.
#include <bits/stdc++.h>
using namespace std;

void LCS(const string &X, const string &Y)
{
    //find the longest common subsequence.
    int m = X.size(), n = Y.size();
    int lcs[m + 1][n + 1];
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0 || j == 0)
                lcs[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
        }
    // print LCS
    int length=lcs[m][n];
    string _lcs(length, '\0');
    int i=m, j=n;
    while(i>0&&j>0)
    {
        if(X[i-1]==Y[j-1]){
            _lcs[--length] = X[i-1];
            --i;
            --j;
        }
        else if(lcs[i-1][j]>lcs[i][j-1])
            --i;
        else
            --j;
    }
    cout<<"Longest common sub sequence is "<<_lcs<<endl;
    cout<<"Length is "<< lcs[m][n];
}

int space_optimized_LCS(const string &X, const string &Y)
{
    //NOTE this function can only compute the length of LCS .
    int m = X.size(), n = Y.size();
    if(m<n)return space_optimized_LCS(Y, X);// make sure we use the shorter string as column to minimize space
    int lcs[2][n + 1]; //we only need to record prevoius row and current row
    bool cur_row;      //true for current row and false for previous row
    for (int i = 0; i <= m; ++i)
    {
        cur_row = i & 1;
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0 || j == 0)
                lcs[cur_row][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                lcs[cur_row][j] = lcs[1 - cur_row][j - 1] + 1;
            else
                lcs[cur_row][j] = max(lcs[1 - cur_row][j], lcs[cur_row][j - 1]);
        }
    }
    return lcs[cur_row][n];
}

// Driver Code
int main()
{
    string X = "AGGTAB";
    string Y = "GXTXAYB";

    // cout << "Length of LCS is "
    //      << space_optimized_LCS(X, Y);
    LCS(X, Y);

    return 0;
}
