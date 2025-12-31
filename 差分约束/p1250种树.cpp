#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 30005;
const int MAXH = 5005;
const int INF = 1e9;

struct Edge
{
    int to, weight;
};

vector<Edge> graph[MAXN];
int dist[MAXN];
bool inQueue[MAXN];

int main()
{
    int n, h;
    cin >> n >> h;

    // 读取居民要求并构建图
    for (int i = 0; i < h; i++)
    {
        int b, e, t;
        cin >> b >> e >> t;
        // S[e] - S[b-1] >= t
        graph[b - 1].push_back({e, t});
    }

    // 添加相邻约束
    for (int i = 1; i <= n; i++)
    {
        // S[i] - S[i-1] >= 0
        graph[i - 1].push_back({i, 0});
        // S[i-1] - S[i] >= -1  (等价于 S[i] - S[i-1] <= 1)
        graph[i].push_back({i - 1, -1});
    }

    // 初始化距离数组为负无穷（求最长路）
    fill(dist, dist + n + 1, -INF);
    dist[0] = 0;

    // SPFA求最长路
    queue<int> q;
    q.push(0);
    inQueue[0] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (const Edge &edge : graph[u])
        {
            int v = edge.to;
            int w = edge.weight;

            if (dist[v] < dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}