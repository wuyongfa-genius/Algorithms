//given an empty chess board and an initial position for Knight, find a solution such that 
// the Knight tour every position in the board exactly once and back to its initial position.
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> POS;

const vector<POS> dirs = {{2, 1}, {1, 2}, {-1, 2}, {-2,1}, {-2, -1}, {-1,-2}, {1,-2}, {2,-1}};

bool is_valid(const vector<vector<int>>&board, int board_h, int board_w, POS p){
    return p.first>=0&&p.first<board_h&&p.second>=0&&p.second<board_w&&board[p.first][p.second]==0;
}

bool is_neighboor(const POS& p1, const POS& p2){
    for(auto&d:dirs){
        if((p2.first==p1.first+d.first)&&(p2.second==p1.second+d.second))
            return true;
    }
    return false;
}
 
int get_degree(const vector<vector<int>>&board, int h, int w, POS p){
    int degree=0;
    for(auto&d:dirs){
        int next_i=p.first+d.first, next_j=p.second+d.second;
        if(is_valid(board, h, w, make_pair(next_i, next_j)))
            ++degree;
    }
    return degree;
}

bool move_to_next_pos(vector<vector<int>>&board, int h, int w, POS& p, int&moves){
    int min_deg=9, c, start_dir=rand()%8;
    int min_deg_idx=-1;
    for(int i=0;i<8;++i){
        int d=(start_dir+i)%8;
        POS next_pos(p.first+dirs[d].first, p.second+dirs[d].second);
        if(is_valid(board, h, w, next_pos)&&(c=get_degree(board, h, w, next_pos))<min_deg){
            min_deg = c;
            min_deg_idx = d;
        }
    }
    if(min_deg_idx==-1)
        return false;
    //move to min accessibility pos
    p = make_pair(p.first+dirs[min_deg_idx].first, p.second+dirs[min_deg_idx].second);
    board[p.first][p.second] = ++moves;//record the move
    return true;
}

bool sovleKT(vector<vector<int>>board, POS start_pos){
    int moves=1, h=board.size(), w=board[0].size();
    POS _start_pos=start_pos;
    board[start_pos.first][start_pos.second] = 1;
    while(moves!=h*w){
        if(!move_to_next_pos(board, h, w, start_pos, moves))
            return false;
    }
    if(!is_neighboor(_start_pos, start_pos))
        return false;
    cout << "Find a Knight's tour: \n";
    for (auto &i : board)
    {
        for (auto &j : i)
            cout << setw(4) << j;
        cout << endl;
    }
    return true;
}

//diver code to test solverKT
int main(){
    int h=8, w=8;
    POS start_pos(0, 0);
    vector<vector<int>> board(h, vector<int>(w, 0));
    srand((unsigned)time(NULL));
    while(1){
        if(sovleKT(board, start_pos))
            break;
    }
    return 0;
}