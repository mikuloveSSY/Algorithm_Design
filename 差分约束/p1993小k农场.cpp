#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge
{
    int to, w;
};

vector<Edge> g[5005]; // 存边
int dist[5005], cnt[5005];
bool inq[5005]; // 记录结点是否在队列内
int n, m;

bool spfa()
{
    // 初始化，将所有节点加入队列
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        dist[i] = 0; // 因为起始点到所有点的边权为0，所有相当于直接全部入队设为0
        q.push(i);
        inq[i] = true;
        cnt[i] = 0;
    }
    // 队列里面是因为松弛需要修改的点
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;
        // 开始松弛
        for (auto e : g[u])
        {
            int v = e.to, w = e.w;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)
                        return false; // 入队超过n次，说明存在负环，即某个点更新了超过n次
                }
            }
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    // 开始建图
    for (int i = 0; i < m; i++)
    {
        int op, a, b, c;
        cin >> op;
        if (op == 1)
        {
            cin >> a >> b >> c;
            // a-b>=c即b-a<=-c，从a到b连边，权值为-c
            g[a].push_back({b, -c});
        }
        else if (op == 2)
        {
            cin >> a >> b >> c;
            // a-b<=c，从b到a连边，权值为c
            g[b].push_back({a, c});
        }
        else
        {
            cin >> a >> b;
            // a == b 即a - b <= 0 且 b - a <= 0
            g[a].push_back({b, 0});
            g[b].push_back({a, 0});
        }
    }

    if (spfa())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}