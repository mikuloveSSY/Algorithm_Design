#include <algorithm>
#include <iostream>
using namespace std;

int X, N;
int value[15], n[15];

bool cmp(int a, int b) { return a < b; }

int main()
{
    cin >> X >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> value[i];
    }
    sort(value + 1, value + N + 1, cmp);
    if (value[1] != 1)
    {
        cout << -1;
        return 0;
    }
    int ans = 0, sum = 0;
    // 贪心：假设当前已经可以凑出1~sum面值的纸币，那么接下去如果再取新的一张纸币，取<=sum+1的最大的面值value的那种纸币，才能保证继续凑出sum+1~sum+value的面值，且最优
    // 进一步优化思路：找<sum的那种可以用二分；要+几张value取决于>sum的最小面值的那张
    while (sum < X)
    {
        int i;
        for (i = N; i >= 1; i--)
        {
            if (value[i] <= sum + 1)
                break;
        }
        ans++, sum += value[i];
    }
    cout << ans;
    return 0;
}