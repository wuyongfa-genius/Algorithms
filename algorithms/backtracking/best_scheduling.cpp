//Given N tasks with the times required to finish, and K workers, A worker can only
//do one job at a time, find the best scheduling so that the finishing time of all tasks is as earlier as possible.
#include <bits/stdc++.h>
using namespace std;

void backtrack(const vector<int> &T, int depth, vector<int> &M, int &min_time)
{
    if (depth == T.size())
    {
        min_time = min(min_time, *max_element(M.begin(), M.end()));
        return;
    }
    for (int i = 0; i < M.size(); ++i)
    {                        //iterate over all machines for tasks[depth]
        M[i] += T[depth];    //try to assign tasks[depth] to i-th machine
        if (M[i] < min_time) // if this assignment is worse than current best, no need to continue
            backtrack(T, depth + 1, M, min_time);
        M[i] -= T[depth];
    }
}

int main()
{
    int N = 7, K = 3;
    vector<int> times = {2, 14, 4, 16, 6, 5, 3};
    vector<int> machine_times(K);
    int min_time = INT_MAX;
    backtrack(times, 0, machine_times, min_time);
    cout << "Min finish time is: " << min_time << endl;
    return 0;
}