#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef struct
{
    int height;
    int width;
    vector<vector<bool>> map;
    vector<vector<bool>> discovered;
} Maze;

typedef struct
{
    int row;
    int column;
} Position;

void initMazeMap(Maze *maze)
{
    maze->map = vector<vector<bool>>(maze->height+2, vector<bool>(maze->width+2, false));
    maze->discovered = vector<vector<bool>>(maze->height+2, vector<bool>(maze->width+2, false));
    for (int i = 0; i < maze->width + 2; i++)
    {
        maze->map[0][i] = true;
        maze->map[maze->height + 1][i] = true;
        maze->discovered[0][i] = true;
        maze->discovered[maze->height + 1][i] = true;
    }
    for (int i = 0; i < maze->height + 2; i++)
    {
        maze->map[i][0] = true;
        maze->map[i][maze->width + 1] = true;
        maze->discovered[i][0] = true;
        maze->discovered[i][maze->width + 1] = true;
    }
}

void getPath(Maze *maze)
{
    Position exit = {.row = maze->height,
                     .column = maze->width};
    stack<Position> stack;

    maze->discovered[1][1] = 1;
    Position entrance = {.row = 1, .column = 1};
    stack.push(entrance);
    bool found = false;
    Position currentPos;
    Position nextPos;
    while (!stack.empty() && !found)
    {
        currentPos = stack.top();
        stack.pop();
        int dir = 0;

        while (dir < 4 && !found)
        {
            /*
                      0
                      |
                    3- -1
                      | 
                      2
            */
            switch (dir)
            {
            case 0:
                nextPos.row = currentPos.row - 1;
                nextPos.column = currentPos.column;
                break;
            case 1:
                nextPos.row = currentPos.row;
                nextPos.column = currentPos.column + 1;
                break;
            case 2:
                nextPos.row = currentPos.row + 1;
                nextPos.column = currentPos.column;
                break;
            case 3:
                nextPos.row = currentPos.row;
                nextPos.column = currentPos.column - 1;
                break;
            }
            if (nextPos.row == exit.row && nextPos.column == exit.column)
                found = true;
            else if (!maze->map[nextPos.row][nextPos.column] && !maze->discovered[nextPos.row][nextPos.column])
            {
                maze->discovered[nextPos.row][nextPos.column] = true;
                stack.push(currentPos);
                currentPos.row = nextPos.row;
                currentPos.column = nextPos.column;
                dir = 0;
            }
            else
                dir++;
        }
    }

    if (found)
    {
        bool first = true;
        vector<Position> path;
        while (!stack.empty()) {
            path.push_back(stack.top());
            stack.pop();
        }
        for (auto it = path.end() - 1; it != path.begin() - 1; it--)
        {
            if (!first)
                cout << " ";
            cout << "(" << it->row-1 << "," << it->column-1 << ")";
            first = false;
        }
        cout << " (" << currentPos.row -1 << "," << currentPos.column - 1 << ") (" << exit.row-1 << ","<< exit.column -1 << ")" << endl;
    }
    else
        cout << "Can't reach the exit!";
}

void printMaze(Maze *maze)
{
    for (int i = 0; i < maze->height + 2; i++)
    {
        for (int j = 0; j < maze->width + 2; j++)
        {
            cout << maze->map[i][j];
        }
        cout << endl;
    }
}

void setMazePos(Maze *maze, Position *pos, int value)
{
    maze->map[pos->row + 1][pos->column + 1] = value;
}

int main()
{
    Maze maze;
    cin >> maze.height >> maze.width;

    // init maze
    initMazeMap(&maze);

    // set maze according input
    for (int i = 0; i < maze.height; i++)
    {
        for (int j = 0; j < maze.width; j++)
        {
            int tmp;
            cin >> tmp;
            Position pos = {.row = i, .column = j};
            setMazePos(&maze, &pos, tmp);
        }
    }

    getPath(&maze);

    return 0;
}