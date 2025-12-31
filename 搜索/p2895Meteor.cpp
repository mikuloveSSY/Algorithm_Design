#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int T[310][310];
int visited[310][310];
int Next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Node
{
    int x, y, time;
};

int main()
{
    // 初始化
    for (int i = 0; i <= 305; i++)
    {
        for (int j = 0; j <= 305; j++)
        {
            T[i][j] = 10000;
            visited[i][j] = -1;
        }
    }

    int M;
    cin >> M;

    // 读取流星数据，考虑影响范围
    for (int i = 1; i <= M; i++)
    {
        int t, x, y;
        cin >> x >> y >> t;

        // 流星击中的点
        if (x >= 0 && x <= 300 && y >= 0 && y <= 300)
        {
            T[x][y] = min(T[x][y], t);
        }

        // 上下左右四个相邻点也会被摧毁
        if (x - 1 >= 0 && x - 1 <= 305 && y >= 0 && y <= 305)
        {
            T[x - 1][y] = min(T[x - 1][y], t);
        }
        if (x + 1 >= 0 && x + 1 <= 305 && y >= 0 && y <= 305)
        {
            T[x + 1][y] = min(T[x + 1][y], t);
        }
        if (x >= 0 && x <= 305 && y - 1 >= 0 && y - 1 <= 305)
        {
            T[x][y - 1] = min(T[x][y - 1], t);
        }
        if (x >= 0 && x <= 305 && y + 1 >= 0 && y + 1 <= 305)
        {
            T[x][y + 1] = min(T[x][y + 1], t);
        }
    }

    // 检查起点是否安全
    if (T[0][0] == 0)
    {
        cout << -1 << endl;
        return 0;
    }

    queue<Node> q;
    q.push({0, 0, 0});
    visited[0][0] = 0;

    while (!q.empty())
    {
        Node current = q.front();
        q.pop();

        int x = current.x;
        int y = current.y;
        int current_time = current.time;

        // 如果当前位置是安全点（永远不会被流星摧毁）
        // 注意人可以走到300以外的地方
        if (T[x][y] == 10000)
        {
            cout << current_time << endl;
            return 0;
        }

        // 尝试四个方向的移动
        for (int i = 0; i < 4; i++)
        {
            int nx = x + Next[i][0];
            int ny = y + Next[i][1];

            // 检查边界
            if (nx < 0 || nx > 305 || ny < 0 || ny > 305)
                continue;

            // 检查是否已经访问过
            if (visited[nx][ny] != -1)
                continue;

            // 检查到达时间是否早于流星摧毁时间
            if (current_time + 1 < T[nx][ny])
            {
                visited[nx][ny] = current_time + 1;
                q.push({nx, ny, current_time + 1});
            }
        }
    }

    // 如果BFS结束都没有找到安全点
    cout << -1 << endl;
    return 0;
}