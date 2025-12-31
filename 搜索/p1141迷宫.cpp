#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int n, m;
vector<string> grid;         // 存储迷宫
vector<vector<int>> comp_id; // 每个格子所属的连通分量编号
vector<int> comp_size;       // 每个连通分量的大小
int current_id = 0;          // 当前连通分量编号

// 四个方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// BFS 搜索连通分量
void bfs(int start_x, int start_y)
{
    current_id++;
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    comp_id[start_x][start_y] = current_id;
    int cnt = 0;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        cnt++;

        // 遍历四个相邻格子
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // 检查是否在迷宫内、未访问过、且符合移动规则（当前格子与目标格子数字不同）
            if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                comp_id[nx][ny] == 0 && grid[nx][ny] != grid[x][y])
            {
                comp_id[nx][ny] = current_id;
                q.push({nx, ny});
            }
        }
    }

    comp_size[current_id] = cnt;
}

int main()
{
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入迷宫大小和查询次数
    cin >> n >> m;

    // 初始化
    grid.resize(n);
    comp_id.assign(n, vector<int>(n, 0));
    comp_size.resize(n * n + 1); // 最多可能有 n*n 个连通分量

    // 读入迷宫
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    // 预处理所有连通分量
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (comp_id[i][j] == 0)
            {
                bfs(i, j);
            }
        }
    }

    // 处理每个查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--; // 转换为 0-based 坐标
        cout << comp_size[comp_id[x][y]] << "\n";
    }

    return 0;
}