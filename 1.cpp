#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

int f(vector<int>&nums){
    int all_sum=0;
    for(auto&num:nums)
        all_sum += num;
    int n=nums.size();
    int res=INT_MAX;
    for(int chosen=0;chosen<(int)(pow(2, n));++chosen){
        int chosen_num=0, chosen_sum=0;
        for(int j=0;j<n;++j){
            if(chosen&(1<<j)){
                chosen_num++;
                chosen_sum += nums[j];
            }
        }
        if(chosen_num==n/2){
            int diff = chosen_sum-(all_sum-chosen_sum)>0?chosen_sum-(all_sum-chosen_sum):
                            -(chosen_sum-(all_sum-chosen_sum));
            if(diff==0)
                return 0;
            if(diff<res)
                res = diff;
        }
    }
    return res;
}

int main(){
    vector<int>nums={ 1,2,3,4,5,6,7,8,9,10};
    cout<<f(nums)<<endl;
    return 0;
}