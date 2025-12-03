#include <cstring>
#include <iostream>
using namespace std;

int a[105][105];
int dp[105][105];
int next_f[105][105];

/*有两种dp[i][j]方法：
1、第i束花放在第j个花瓶时的最大值（缺点是要第三层遍历求i-1摆放的最大值）
2、相比第一种方法，改变之处在于遍历第二层花瓶时，只考虑第i束花放不放在当前第j个花瓶的两种选择中的最大值(更优，数据较大时大多采用这个)，若放了更大，则dp[i][j]=dp[i-1][j-1]+aij,若不放，则dp[i][j]=dp[i][j-1]
本质上，方法二相当于把第三层循环优化掉了，并入了第二层的数据中
        不过方法二需要特别得去处理路径问题
*/

int main()
{
    int F, V;
    cin >> F >> V;
    for (int i = 1; i <= F; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            cin >> a[i][j];
        }
    }
    // 由于有负的，所以要注意初始化负的很大
    memset(dp, -1 * 0x3f, sizeof(dp));
    for (int v = 1; v <= V; v++)
    {
        dp[F][v] = a[F][v];
    }
    for (int i = F - 1; i >= 1; i--)
    {
        for (int j = V + i - F; j >= 1; j--)
        {
            int max_value = -1 * 0x3f;
            int max_k = -1;
            for (int k = V + i + 1 - F; k > j; k--)
            {
                if (max_value <= dp[i + 1][k])
                {
                    max_k = k;
                    max_value = dp[i + 1][k];
                }
            }
            next_f[i][j] = max_k;
            dp[i][j] = max_value + a[i][j];
        }
    }

    int max_value = dp[1][1];
    int max_i = -1;
    for (int i = 1; i <= V; i++)
    {
        if (max_value <= dp[1][i])
        {
            max_i = i;
            max_value = dp[1][i];
        }
    }
    cout << max_value << endl;
    for (int f = 1; f <= F; f++)
    {
        cout << max_i << ' ';
        max_i = next_f[f][max_i];
    }
    return 0;
}