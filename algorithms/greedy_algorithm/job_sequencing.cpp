//C++ program to solve job sequencing problem
/*
Given a set of n jobs where each job i has a deadline di >=1 and profit pi>=0. 
Only one job can be scheduled at a time. Each job takes 1 unit of time to complete. 
We earn the profit if and only if the job is completed by its deadline. The task is to 
find the sequence of jobs that maximizes profit.
Algorithm:
1.Sort all jobs in decreasing order of profit.
2.Initialize the result sequence as first job in sorted jobs.
3.Do following for remaining n-1 jobs 
    If the current job can fit in the current result sequence without missing the deadline, 
        add current job to the result. Else ignore the current job.
we can efficiently implement it using disjoint set
*/
#include <bits/stdc++.h>
#include "../../disjoint/disjoint_set.h"

void Disjoint_Set::custom_LINK(int u, int v)
{
    parent[v] = u;
}

struct Job
{
    char job_id;
    int deadline, profit;
};

bool myCompare(Job a, Job b)
{
    return a.profit > b.profit;
}

int get_max_deadline(const vector<Job> &j)
{
    int max_deadline = -1;
    for (auto &a : j)
    {
        if (a.deadline > max_deadline)
            max_deadline = a.deadline;
    }
    return max_deadline;
}

void job_scheduling(vector<Job> &j)
{
    sort(j.begin(), j.end(), myCompare);
    Disjoint_Set djset(get_max_deadline(j) + 1);
    for (int i = 0; i < j.size(); ++i)
    {
        //find current latest free time slot
        int free_slot = djset.FIND_SET(j[i].deadline);
        if (free_slot > 0)
        {
            //unite free_slot and the root of free_slot-1 so that in future queries we find
            //the latest free slot
            djset.custom_LINK(djset.FIND_SET(free_slot - 1), free_slot);
            cout << j[i].job_id << ',';
        }
    }
}

// Driver code
int main()
{
    vector<Job> jobs = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
    cout << "Following jobs need to be "
         << "executed for maximum profit\n";
    job_scheduling(jobs);
    return 0;
}