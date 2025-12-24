#include <iostream>
#include <queue>
using namespace std;
int n, m, x, y;
int map[405][405];
int reach[405][405];
int Next[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
queue<pair<int, int>> bfs;

int main()
{
    cin >> n >> m >> x >> y;
    reach[x][y] = 1;
    bfs.push({x, y});
    while (!bfs.empty())
    {
        auto temp = bfs.front();
        bfs.pop();
        for (int i = 0; i < 8; i++)
        {
            int next_x = temp.first + Next[i][0], next_y = temp.second + Next[i][1];
            if (next_x > 0 && next_x <= n && next_y > 0 && next_y <= m && !reach[next_x][next_y])
            {
                map[next_x][next_y] = map[temp.first][temp.second] + 1;
                reach[next_x][next_y] = 1;
                bfs.push({next_x, next_y});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (reach[i][j])
            {
                cout << map[i][j];
            }
            else
            {
                cout << -1;
            }
            cout << ' ';
        }
        cout << endl;
    }
    return 0;
}