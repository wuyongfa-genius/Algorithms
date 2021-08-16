//C++program to find a solution path in a maze using backtrack
#include <bits/stdc++.h>
using namespace std;

bool solve_maze(const vector<vector<int>> &maze, vector<vector<int>> &solution, int i, int j)
{
    solution[i][j] = 1; //mark cur pos as in solution
    if (i == maze.size() - 1 && j == maze[0].size() - 1 && maze[i][j] == 1)
        return true;
    //right
    if (j + 1 < maze[0].size() && solution[i][j + 1] == 0 && maze[i][j] == 1)
    {
        if (solve_maze(maze, solution, i, j + 1))
            return true;
    }
    //down
    if (i + 1 < maze.size() && solution[i + 1][j] == 0 && maze[i][j] == 1)
    {
        if (solve_maze(maze, solution, i + 1, j))
            return true;
    }
    //can not find solution going right or down, means can not find solutin from cur pos(i, j), backtrack
    solution[i][j] = false;
    return false;
}

int main()
{
    vector<vector<int>> maze = {{1, 0, 0, 0},
                                {1, 1, 0, 1},
                                {0, 1, 0, 0},
                                {1, 1, 1, 1}};
    vector<vector<int>> res(maze.size(), vector<int>(maze[0].size(), 0));
    if (maze[0][0] == 1 && solve_maze(maze, res, 0, 0))
    {
        for (auto &a : res)
        {
            for (auto &b : a)
                cout << setw(4) << b;
            cout << endl;
        }
    }
    return 0;
}