// C++ program to solve N-Queen problem using backtrack algorithm
#include <bits/stdc++.h>
using namespace std;

bool solve_N_Queen(vector<vector<char>> &board, int N, int col, vector<bool> &queen_in_rows,
                   vector<bool> &queen_in_ld, vector<bool> &queen_in_rd)
{
    if (col == N)
        return true;
    //try every row in cur col
    int rand_row=rand()%N; //start from a random row to find different solutions, otherwise we only find a certain solution.
    for (int i = 0; i < board.size(); ++i)
    {   
        int row=(rand_row+i)%N;
        if (!queen_in_rows[row] && !queen_in_ld[row - col + N - 1] && !queen_in_rd[row + col])
        {
            queen_in_rows[row] = queen_in_ld[row - col + N - 1] = queen_in_rd[row + col] = true;
            board[row][col] = 'Q';
            if (solve_N_Queen(board, N, col + 1, queen_in_rows, queen_in_ld, queen_in_rd))
                return true;
            //can not solve by placing Queen at (row, col), backtrack
            board[row][col] = ' ';
            queen_in_rows[row] = queen_in_ld[row - col + N - 1] = queen_in_rd[row + col] = false;
        }
    }
    //can not solve by placing Queen at any row in col, thus not solving the problem
    return false;
}

int main()
{
    srand((unsigned)time(NULL));
    int N = 8;
    vector<vector<char>> board(8, vector<char>(8, ' '));
    vector<bool> queen_in_rows(N, false), queen_in_ld(2*N-1, false), queen_in_rd(2*N-1, false);
    //only when N==1 or N>=4, we try to solve N Queen problem
    if((N==1||N>=4) && solve_N_Queen(board, N, 0, queen_in_rows, queen_in_ld, queen_in_rd))
    {
        for(auto&a:board)
        {
            for(auto&b:a)
                cout<<setw(4)<<b;
            cout<<endl;
        }
    }
    else
        cout<<"Can not find a solution"<<endl;
    return 0;
}