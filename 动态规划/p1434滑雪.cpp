#include <algorithm>
#include <iostream>
using namespace std;

int R, C;
struct Point
{
    int x;
    int y;
} h[10005];
int height[105][105];
int max_length[105][105]; // 代表到达改点的最长长度

int Next[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool cmp(Point a, Point b) { return height[a.x][a.y] < height[b.x][b.y]; }

int main()
{

    cin >> R >> C;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> height[i][j];
            h[(i - 1) * C + j].x = i;
            h[(i - 1) * C + j].y = j;
        }
    }
    sort(&h[1], &h[R * C] + 1, cmp);
    int ans = 0;
    // 周围一圈初始化为0
    for (int i = 1; i <= R * C; i++)
    {
        int x = h[i].x, y = h[i].y;
        max_length[x][y] = 1;
        for (int t = 0; t < 4; t++)
        {
            int X = h[i].x + Next[t][0], Y = h[i].y + Next[t][1];

            if (height[x][y] > height[X][Y])
            {
                max_length[x][y] = max(max_length[X][Y] + 1, max_length[x][y]);
            }
        }
        ans = max(max_length[x][y], ans);
    }
    // for (int i = 1; i <= R * C; i++)
    // {
    //     cout << height[h[i].x][h[i].y] << ' ' << max_length[h[i].x][h[i].y];
    //     cout << endl;
    // }

    cout << ans;
    return 0;
}