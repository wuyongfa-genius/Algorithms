//Given n eggs and K floors, find the min times needed to find out at which floor we can safely drop the eggs.
#include<bits/stdc++.h>
using namespace std;

int egg_drop(int N, int K)
{
    int dp[N+1][K+1], res, broken, intact;
    for(int i=0;i<=N;++i){
        dp[i][1] = 1; // we need at least one try at the first floor
        dp[i][0] = 0;
    }
    for(int j=0;j<=K;++j){
        dp[1][j] = j; //we need at least j trials at j-th floor
    }
    for(int i=2;i<=N;++i){ // try every possible egg numbers
        for(int j=2;j<=K;++j){ // try every possible floor
            dp[i][j] = INT_MAX;
            for(int x=1;x<=j;++x){ // we try to drop egg from x-th floor
                broken=dp[i-1][x-1]; //the egg breaks, we have i-1 eggs left and we need try every floor under x
                intact = dp[i][j-x]; //the egg keeps intact, we still have i eggs and we need try every floor above x
                res = 1+max(broken, intact); // current drop + maximal possible trials left
                if(res<dp[i][j])
                    dp[i][j] = res;
            }
        }
    }
    return dp[N][K];
}

/* Driver program to test to pront printDups*/
int main()
{
    int n = 2, k = 36;
    printf("Minimum number of trials "
           "in worst case with %d eggs and "
           "%d floors is %d ",
           n, k, egg_drop(n, k));
    return 0;
}