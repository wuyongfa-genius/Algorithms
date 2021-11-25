// Given n tasks with arrival time, priority and number of time units they need. 
// We need to schedule these tasks on a single resource. The objective is to arrange 
// tasks such that maximum priority tasks are taken. Objective is to minimize sum 
// of product of priority and left time of tasks that are not scheduled due to limited 
// time. This criteria simply means that the scheduling should cause minimum possible loss.
#include <bits/stdc++.h>
using namespace std;

struct Task
{
    int arrival, units, priority;
    Task(int a, int u, int p) : arrival(a), units(u), priority(p) {}
};

bool operator<(const Task&t1, const Task&t2)
{
    return t1.priority<t2.priority;
}

bool myCompare(const Task&t1, const Task&t2)
{
    return t1.arrival<t2.arrival;
}

int min_loss(vector<Task>&tasks, int t)
{
    sort(tasks.begin(), tasks.end(), myCompare);
    int index=0, loss=0;
    for(auto&a:tasks)
        loss += a.priority*a.units;
    priority_queue<Task>pq;
    for(int i=1;i<=t;++i){
        while(index<tasks.size()&&tasks[index].arrival==i)
        {
            pq.emplace(tasks[index]);
            ++index;
        }
        if(!pq.empty()){
            auto tmp=pq.top();
            pq.pop();
            loss -= tmp.priority;
            --tmp.units;
            if(tmp.units!=0)
                pq.emplace(tmp);
        }
    }
    return loss;
}

int main()
{
    vector<Task> tasks = {
        {1, 2, 100},
        {2, 2, 300}
    };
    int limited_time=3;
    cout<<"Min Loss is: "<<min_loss(tasks, limited_time)<<endl;
    return 0;
}