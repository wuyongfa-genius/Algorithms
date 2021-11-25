// Given N jobs where every job is represented by following three elements of it.
// Start Time
// Finish Time
// Profit or Value Associated
// Find the maximum profit subset of jobs such that no two jobs in the subset overlap.
#include<bits/stdc++.h>
using namespace std;

struct Job
{
    int start, end, profit;
};

bool myCompare(Job&j1, Job&j2)
{
    return j1.end<j2.end;
}

int latest_nonoverlapping_job(const vector<Job>&j, int index)
{
    //find the latest job which do not overlap with current job
    int low=0, high=index-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(j[mid].end<=j[index].start){
            if(j[mid+1].end>j[index].start)
                return mid;
            else
                low = mid+1;
        }
        else
            high = mid-1;
    }
    return -1;
}

int findMaxProfit(vector<Job>&jobs)
{
    int n=jobs.size();
    vector<int>dp(n);
    sort(jobs.begin(), jobs.end(), myCompare); // sort jobs according to their finish time.
    for(int i=0;i<n;++i)
        dp[i] = jobs[i].profit; //initially we can at least get jobs[i].profit by finishing i-th job
    for(int i=0;i<n;++i){
        int latest_job_index=latest_nonoverlapping_job(jobs, i);
        if(latest_job_index!=-1&&dp[latest_job_index]+jobs[i].profit>dp[i])
            dp[i] = dp[latest_job_index]+jobs[i].profit;
    }
    return dp[n-1];
}

// Driver program
int main()
{
    vector<Job>jobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
    cout << "Optimal profit is " << findMaxProfit(jobs);
    return 0;
}