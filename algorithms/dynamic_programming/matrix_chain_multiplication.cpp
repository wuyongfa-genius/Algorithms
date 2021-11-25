// Given a sequence of matrices, find the most efficient way to multiply these 
// matrices together. The problem is not actually to perform the multiplications, 
// but merely to decide in which order to perform the multiplications.
#include<bits/stdc++.h>
using namespace std;

void print_matrix_chain(int*bracket, int i, int j, int n, char& name)
{
    if(i==j)
    {
        cout<<name++;
        return;
    }
    cout<<'(';//print a ( before i
    //print i to bracket[i][j]
    print_matrix_chain(bracket, i, *(bracket+i*n+j), n, name);
    //print bracket[i][j]+1 to j
    print_matrix_chain(bracket, *(bracket+i*n+j)+1, j, n, name);
    cout<<')'; //print a ) after j
}

void matrix_chain_order(const vector<int>& p)
{
    int n=p.size(), j, q;
    int dp[n][n]; //dp[i][j] means min ops to perform matrix multiplication from matrix i to j
    int brackets[n][n]; //record the break point which has min operations
    char matrix_name='A';
    for(int t=1;t<n;++t)
        dp[t][t] = 0; //no multiplication
    for(int L=2;L<n;++L){// try every possible matrix_chain length
        for(int i=1;i<=n-L;++i){ //try every possible length-L matrix chain
            j = i+L-1; // index j must be <=n-1
            dp[i][j] = INT_MAX;
            for(int k=i;k<=j-1;++k){ //try every possible break point
                if(dp[i][k]!=INT_MAX && dp[k+1][j]!=INT_MAX)
                    q = dp[i][k]+dp[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<dp[i][j]){
                    dp[i][j] = q;
                    brackets[i][j] = k; //record the break point
                }   
            } 
        }
    }
    cout<<"Optimal matrix chain order: ";
    print_matrix_chain((int*)brackets, 1, n-1, n, matrix_name);
    cout<<endl;
    cout << "Minimum number of multiplications is "<<dp[1][n-1];
}

int main()
{
    vector<int>p = { 1, 2, 3, 4 };
 
    matrix_chain_order(p);

    return 0;
}