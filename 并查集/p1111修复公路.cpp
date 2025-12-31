#include <algorithm>
#include <iostream>
using namespace std;

int Father[1005];
struct Road
{
    int x;
    int y;
    int t;
} road[100005];
int cmp(Road a, Road b)
{
    return a.t < b.t;
}
// 查询祖先结点
int find(int x)
{
    if (Father[x] == x)
    {
        return x;
    }
    // 更新祖先结点
    Father[x] = find(Father[x]);
    return Father[x];
}

int main()
{
    // 初始化每个父亲结点都是自己
    for (int i = 0; i < 1005; i++)
    {
        Father[i] = i;
    }
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        cin >> road[i].x >> road[i].y >> road[i].t;
    }
    sort(&road[1], &road[M] + 1, cmp);
    int c = 0; // 记录连接需要的最小公路数；根据树的特性，当边c=N-1即结点数-1时，全部结点相连在一起
    for (int i = 1; i <= M; i++)
    {
        int fx = find(road[i].x), fy = find(road[i].y);
        if (fx != fy)
        {
            // 说明两个村子不在一个集合里，则这条新公路就作为连接两个集合的一条新边
            Father[fx] = fy;
            c++; // 更新边数
        }
        if (c == N - 1)
        {
            cout << road[i].t;
            return 0;
        }
    }

    cout << -1;
    return 0;
}