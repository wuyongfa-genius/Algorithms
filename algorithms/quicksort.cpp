#include<bits/stdc++.h>
#define RAND(x, y) rand()%(y-x+1)+x 
using namespace std;

int standard_hoare_partition(vector<int>&A, int left, int right){
    int i=left-1, j=right+1;
    int pivot=A[left];
    while(1){
        do{
            --j;
        }while(A[j]<pivot);
        do{
            ++i;
        }while(A[i]>pivot);
        
        if(i<j)
            swap(A[i], A[j]);
        else
            return j;
    }
    return -1;
}

int modified_hoare_partition(vector<int>&A, int left, int right){
    int i=left, j=right;
    int pivot=A[left];
    while(i<j){
        while((i<j)&&A[j]>=pivot)
            --j;
        while((i<j)&&A[i]<=pivot)
            ++i;
        if(i<j)swap(A[i], A[j]);
    }
    swap(A[i], A[left]);
    return i;
}

int randomized_hoare_partition(vector<int>&A, int left, int right){
    int x=RAND(left, right);
    swap(A[left], A[x]);
    return standard_hoare_partition(A, left, right);
}

void myTopK(vector<int>&A, int left, int right, int k){
    if(left<right){
        int p=randomized_hoare_partition(A, left, right);
        if(p<k){
            return myTopK(A, p+1, right, k);
        }
        else return myTopK(A, left, p, k);
    }
}

void quicksort(vector<int>&A, int left, int right){
    if(left<right){
        int p=randomized_hoare_partition(A, left, right);
        quicksort(A, left, p);
        quicksort(A, p+1, right);
    }
}

int main(){
    vector<int>nums={3,2,92,3,-1,390,832,-378,834,-8,-39,837,2,1};
    // quicksort(nums, 0, nums.size()-1);
    myTopK(nums, 0, nums.size()-1, 5);
    cout<<"Top "<<5<<" is "<<nums[4]<<endl;
    for(auto&a:nums)
        cout<<a<<',';
    return 0;
}