#include <cstring>
#include <iostream>
using namespace std;
// 思考易知，对于每次关下一盏的灯的抉择，肯定是从左右两边最靠近老张的亮的那两盏里面选一个关掉，因为如果选择越过这两盏的灯去关，那么必然会经过这两盏，从而必然要关这两盏，否则肯定浪费电
// 所以关掉的灯肯定是中间连成一片的一个区间
// dp数组，一维表示这个区间左侧，二维表示该区间右侧，三维表示老王此时在左边还是右边，存储的是此时的耗电量

#define min(x, y) ((x) > (y) ? (y) : (x))

int P[55] = {0}; // 处理成前缀和
int point[55] = {0};
int dp[55][55][2] = {0};

int main()
{
    int n, c;
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
    {
        cin >> point[i] >> P[i];
        P[i] += P[i - 1];
    }
    memset(dp, 0x1f, sizeof(dp)); // 为了防止某些到达不了的情况由于初始是0，min计算时也会被算进去
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int l = 1; l + i - 1 <= n; l++)
        {
            // 扫描整个数组，只有包含c时才更新
            if (c >= l && c <= l + i - 1)
            {
                // 不用dp[l][l+i-2]是因为从该状态转移的话只能去关右边的那盏l+i-1，不可能到左边来，所以不用考虑
                // 注意用前缀时相减的两项别搞错
                dp[l][l + i - 1][0] = min(dp[l + 1][l + i - 1][0] + (point[l + 1] - point[l]) * (P[l] + P[n] - P[l + i - 1]), dp[l + 1][l + i - 1][1] + (point[l + i - 1] - point[l]) * (P[l] + P[n] - P[l + i - 1]));

                dp[l][l + i - 1][1] = min(dp[l][l + i - 2][1] + (point[l + i - 1] - point[l + i - 2]) * (P[l - 1] + P[n] - P[l + i - 2]), dp[l][l + i - 2][0] + (point[l + i - 1] - point[l]) * (P[l - 1] + P[n] - P[l + i - 2]));
            }
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         cout << dp[i][n][0] << ' ' << dp[i][n][1] << endl;
    //     }
    // }

    cout << min(dp[1][n][0], dp[1][n][1]);
    return 0;
}