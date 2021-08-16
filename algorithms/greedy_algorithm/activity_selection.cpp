//You are given n activities with their start and finish times. Select the maximum number of 
//activities that can be performed by a single person, assuming that a person can only work 
//on a single activity at a time. 
#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> Pair;

void activity_selection(const vector<int>&starts, const vector<int>&finishs, vector<Pair>&res){
    priority_queue<Pair, vector<Pair>, greater<Pair>>pq;
    for(int i=0;i<starts.size();++i){
        pq.emplace(finishs[i], starts[i]);
    }
    int start=pq.top().second, end=pq.top().first;
    res.emplace_back(start, end);
    pq.pop();
    while(!pq.empty()){
        Pair p=pq.top();
        pq.pop();
        if(p.second>=end){
            start = p.second;
            end = p.first;
            res.emplace_back(start, end);
        }
    }
}

// Driver program
int main()
{
    vector<int>s = {1, 3, 0, 5, 8, 5};
    vector<int>f = {2, 4, 6, 7, 9, 9};
    vector<Pair>res;
    activity_selection(s, f, res);
    for(auto&a:res){
        cout<<'('<<a.first<<','<<a.second<<')'<<"-->";
    }
 
    return 0;
}