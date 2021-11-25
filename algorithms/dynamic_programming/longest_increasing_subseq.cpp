//The Longest Increasing Subsequence (LIS) problem is to find the length of the 
//longest subsequence of a given sequence such that all elements of the subsequence
//are sorted in increasing order. For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} 
//is 6 and LIS is {10, 22, 33, 50, 60, 80}. 
#include<bits/stdc++.h>
using namespace std;

int LIS(const vector<int>&A)
{
    vector<int>lis(A.size(), 1);
    vector<int>indices(A.size(), 0);
    for(int i=1;i<A.size();++i){
        for(int j=0;j<i;++j){
            if(A[i]>A[j]&&lis[i]<lis[j]+1){
                lis[i] = lis[j]+1;
                indices[i] = j;
            }
        }
    }
    auto it= max_element(lis.begin(), lis.end());
    int index = distance(lis.begin(), it);
    //print LIS
    stack<int>lis_seq;
    while(lis[index]!=1)
    {
        lis_seq.emplace(A[index]);
        index = indices[index];
    }
    lis_seq.emplace(A[index]);
    cout<<"One of the Longest increasing subsequence is : ";
    while(!lis_seq.empty())
    {
        cout<<lis_seq.top()<<',';
        lis_seq.pop();
    }
    cout<<endl;
    return *it;
}

int LIS_ONLgN(const vector<int>&A)
{
    if(A.size()==0)
        return 0;
    vector<int>tail(A.size(), 0);
    //put the first element in.
    tail[0] = A[0];
    int length=1;
    for(int i=1;i<A.size();++i)
    {
        //binary search the first element which is bigger than A[i].
        auto it=lower_bound(tail.begin(), tail.begin()+length, A[i]);
        // make sure the tail element is as min as possible.
        if(it==tail.begin()+length)
            tail[length++] = A[i];
        else
            *it = A[i];
    }
    return length;
}

/* Driver program to test above function */
int main()
{
    vector<int>arr = { 10, 22, 9, 33, 21, 50, 41, 60 };
    printf("Length of lis is %d\n", LIS(arr));
 
    return 0;
}