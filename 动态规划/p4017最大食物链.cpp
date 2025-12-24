#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// in与out用于拓扑排序
int n_in[5005], n_out[5005], n_cnt[5005];
vector<int> n_e[5005];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        n_e[a].push_back(b);
        n_out[a]++;
        n_in[b]++;
    }
    queue<int> food;
    vector<int> tail;
    for (int i = 1; i <= n; i++)
    {
        if (n_in[i] == 0)
        {
            n_cnt[i] = 1;
            food.push(i);
        }
        if (n_out[i] == 0)
            tail.push_back(i);
    }
    while (!food.empty())
    {
        int temp = food.front();
        food.pop();
        for (auto i : n_e[temp])
        {
            n_cnt[i] = (n_cnt[i] + n_cnt[temp]) % 80112002;
            n_in[i]--;
            // 入度为0才入队
            if (n_in[i] == 0)
                food.push(i);
        }
    }
    int ans = 0;
    for (auto i : tail)
    {
        ans = (ans + n_cnt[i]) % 80112002;
    }
    cout << ans;
    return 0;
}