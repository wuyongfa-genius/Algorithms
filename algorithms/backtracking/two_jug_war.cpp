//Given a set containing M numbers, split it into two subsets(constains same samount of numbers when M is even
//otherwise,one set contains one more number than the other) such that the difference of the sum of the two subsets
// is minimum.
#include<bits/stdc++.h>
using namespace std;

void backtrack(const vector<int>&A, bool*one_set, int one_set_size, bool*solution, int cur_sum, int pos, int&min_diff, int sum){
    if(pos==A.size())
        return;
    if((A.size()/2-one_set_size)>(A.size()-pos))//include two few elements
        return;
    //consider cur pos is not included in one_set
    backtrack(A, one_set, one_set_size, solution, cur_sum, pos+1, min_diff, sum);
    //consider cur pos included in one_set
    one_set[pos] = true;
    cur_sum += A[pos];
    ++one_set_size;
    if(one_set_size==A.size()/2){
        if(abs(sum-2*cur_sum)<min_diff){
            //find a solution
            min_diff = abs(sum-2*cur_sum);
            for(int i=0;i<A.size();++i)
                solution[i] = one_set[i];
        }
    }
    else
        backtrack(A, one_set, one_set_size, solution, cur_sum, pos+1, min_diff, sum);
    //backtrack, Note that we only need to backtrack the pointers or reference variable
    //other variables do not affect the function calls in the caller stack.
    one_set[pos] = false;
}

void two_jug_war(const vector<int>&A, int&min_diff, vector<vector<int>>&two_sets){
    int n=A.size();
    bool one_set[n]={false};
    bool solution[n]={false};
    int sum=0;
    for(auto& a:A)
        sum += a;
    backtrack(A, one_set, 0, solution, 0, 0, min_diff, sum);
    vector<int>one, the_other;
    for(int i=0;i<n;++i){
        if(solution[i])
            one.emplace_back(A[i]);
        else 
            the_other.emplace_back(A[i]);
    }
    two_sets.emplace_back(one);
    two_sets.emplace_back(the_other);
}

// Driver program to test above functions
int main()
{
    vector<int>arr = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};
    vector<vector<int>>two_sets;
    int min_diff=INT_MAX;
    two_jug_war(arr, min_diff, two_sets);
    cout<<"The first set is: ";
    for(auto& a:two_sets[0])
        cout<<a<<',';
    cout<<"\nThe second set is: ";
    for(auto& a:two_sets[1])
        cout<<a<<',';
    cout<<"\nMin difference is: "<<min_diff<<endl;
    return 0;
}