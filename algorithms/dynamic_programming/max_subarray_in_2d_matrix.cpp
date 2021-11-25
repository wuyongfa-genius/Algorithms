// Given a 2D array, find the maximum sum subarray in it
#include <bits/stdc++.h>
using namespace std;

int kanade(int A[], int N, int&start, int&end)
{
    int max_so_far=INT_MIN, max_ending_here=0, ending_here_start=0;
    for(int i=0;i<N;++i){
        max_ending_here += A[i];
        if(max_ending_here>max_so_far){
            max_so_far = max_ending_here;
            start = ending_here_start;
            end = i;
        }
        if(max_ending_here<0){
            max_ending_here = 0;
            ending_here_start = i+1;
        }
    }
    return max_so_far;
}

int max_sum_subarray(const vector<vector<int>>&M)
{
    int max_left_right=0, max_so_far=INT_MIN;
    int ROW=M.size(), COL=M[0].size();
    int temp[ROW];
    int start=0,end=0, final_left, final_top, final_right, final_down;
    for(int left=0;left<COL;++left){ //iterate over all possible left
        memset(temp, 0, sizeof(temp));
        for(int right=left;right<COL;++right){ //iterate over all possible right
            for(int i=0;i<ROW;++i)
                temp[i] += M[i][right];
            max_left_right = kanade(temp, ROW, start, end);
            if(max_left_right>max_so_far){
                max_so_far = max_left_right;
                final_top = start;
                final_left = left;
                final_down = end;
                final_right = right;
            }
        }
    }
    cout<<"Max subarray (left, top): "<<final_left<<','<<final_top<<endl;
    cout<<"Max subarray (right, down): "<<final_right<<','<<final_down<<endl;
    cout<<"Max sum is: "<<max_so_far<<endl;
    return max_so_far;
}

int main()
{
    vector<vector<int>> matrix = {{1, 2, -1, -4, -20},
                                  {-8, -3, 4, 2, 1},
                                  {3, 8, 10, 1, 3},
                                  {-4, -1, 1, 7, -6}};
    max_sum_subarray(matrix);
    return 0;
}