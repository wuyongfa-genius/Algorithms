//Given the arrival and departure times of all trains that reach a railway station, the task
//is to find the minimum number of platforms required for the railway station so that no train waits. 
//We are given two arrays that represent the arrival and departure times of trains that stop.
#include<bits/stdc++.h>
using namespace std;

int min_platforms_1(vector<int>&arrivals, vector<int>&departures)
{   /*All events are sorted by time.
    Total platforms at any time can be obtained by
    subtracting total departures from total arrivals
    by that time.
    Time Complexity: O(N * log N). Space Complexity: O(1). 
    */
    sort(arrivals.begin(), arrivals.end());
    sort(departures.begin(), departures.end());
    int i=0, j=0, res=1, platforms=0;
    while(i<arrivals.size()&&j<departures.size()){
        if(arrivals[i]<=departures[j]){
            ++platforms;
            ++i;
        }
        else{
            --platforms;
            ++j;
        }
        if(platforms>res)
            res = platforms;
    }
    return res;
}

int min_platforms_2(vector<int>&arrivals, vector<int>&departures)
{
    vector<int>platforms(2361, 0);
    int res=1;
    for(int i=0;i<arrivals.size();++i){
        ++platforms[arrivals[i]]; //once a train arrives, need one platform
        --platforms[departures[i]+1]; //once a train leave. need one less platform
    }
    for(int i=1;i<2361;++i){
        platforms[i] += platforms[i-1];
        if(platforms[i]>res)
            res = platforms[i];
    }
    return res;
}

// Driver code
int main()
{
    vector<int>arr = { 900, 940, 950, 1100, 1500, 1800 };
    vector<int>dep = { 910, 1200, 1120, 1130, 1900, 2000 };
    cout << "Minimum Number of Platforms Required = "
         << min_platforms_2(arr, dep);
    return 0;
}