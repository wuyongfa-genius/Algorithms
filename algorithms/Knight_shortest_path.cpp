#include <bits/stdc++.h>
using namespace std;

bool feasible(char **b, int cur_i, int cur_j, int offset_i, int offset_j, int w, int h)
{
    if (cur_i + offset_i < 0 || (cur_i > 0 && b[cur_i - 1][cur_j] == '#' && offset_i == -2))
        return false;
    if (cur_i + offset_i >= w || (cur_i < w - 1 && b[cur_i + 1][cur_j] == '#' && offset_i == 2))
        return false;
    if (cur_j + offset_j >= h || (cur_j < h - 1 && b[cur_i][cur_j + 1] == '#' && offset_j == 2))
        return false;
    if (cur_j + offset_j < 0 || (cur_j > 0 && b[cur_i][cur_j - 1] == '#' && offset_j == -2))
        return false;
    if (b[cur_i + offset_i][cur_j + offset_j] == '#')
        return false;
    return true;
}

int main()
{
    const vector<vector<int>> dirs = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
    int min_steps = INT_MAX;
    // input chess board;
    int w, h;
    cin >> w >> h;
    char **board = new char *[w];
    for (int i = 0; i < w; ++i)
        board[i] = new char[h];
    int _w = w;
    int start_i = -1, start_j = -1;
    while (_w--)
    {
        int _h = h;
        while (_h--)
        {
            int cur_i = w - _w - 1, cur_j = h - _h - 1;
            cin >> board[cur_i][cur_j];
            if (board[cur_i][cur_j] == 'H')
                start_i = cur_i, start_j = cur_j;
        }
    }
    // use BFS to find shortest path.
    bool visited[w][h];
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    q.emplace(make_pair(start_i, start_j));
    visited[start_i][start_j] = true;
    bool find_shortest = false;
    for (int step = 1; !q.empty(); ++step)
    {
        if (find_shortest)
            break;
        int qsize = q.size();
        while (qsize--)
        {   
            if (find_shortest)
                break;
            pair<int, int> coord = q.front();
            q.pop();
            int i = coord.first, j = coord.second;
            for (int k = 0; k < 8; ++k)
            {
                int offset_i = dirs[k][0], offset_j = dirs[k][1];
                if (feasible(board, i, j, offset_i, offset_j, w, h) && !visited[i + offset_i][j + offset_j])
                {
                    if (board[i + offset_i][j + offset_j] == 'T')
                    {
                        min_steps = step;
                        find_shortest = true;
                        break;
                    }
                    q.emplace(make_pair(i + offset_i, j + offset_j));
                    visited[i + offset_i][j + offset_j] = true;
                }
            }
        }
    }
    cout << min_steps << endl;
    // release dynamic arrays
    for (int i = 0; i < w; ++i)
        delete[] board[i];
    delete[] board;
    board = NULL;
    return 0;
}
//test case
// 5 13
// ........H...#
// ........#....
// .....#.......
// .#...........
// ..........T#.