#include <bits/stdc++.h>
using namespace std;

const int Maxn = 500005; // 定义最大数组长度
int n, s[Maxn], m;       // n: 数组大小，s: 原始数组，m: 操作次数

// 计算x的最低有效位（Lowest Set Bit）
int lowbit(int x)
{
    return x & (-x); // 通过补码特性获取最低位的1对应的值
    // 例如：x=6(110)，-x在补码中是...111010，6&(-6)=2(010)
}

// 树状数组结构体
struct node
{
    int c[Maxn]; // 树状数组，c[i]存储区间[i-lowbit(i)+1, i]的和

    // 单点修改：在位置x增加d
    void add(int x, int d) // 修改
    {
        s[x] += d; // 同时更新原始数组（可选，看需求）
        // 向上更新所有包含x的区间
        for (int i = x; i <= n; i += lowbit(i))
            c[i] += d; // 更新每个相关区间的和
    }

    // 前缀和查询：查询前x个元素的和
    int sum(int x) // 查询
    {
        int ans = 0;
        // 向下累加不重叠的区间
        for (int i = x; i > 0; i -= lowbit(i))
            ans += c[i]; // 累加每个相关区间的和
        return ans;
    }

    // 初始化树状数组
    void init() // 初始化
    {
        memset(c, 0, sizeof(c)); // 清空树状数组
        // 用原始数组s构建树状数组
        for (int i = 1; i <= n; i++)
            for (int j = i - lowbit(i) + 1; j <= i; j++)
                // c[i]是区间[i-lowbit(i)+1, i]的元素和
                c[i] = c[i] + s[j];
    }

    // 调试用：输出原始数组和树状数组
    void print() // 用来调试的输出
    {
        for (int i = 1; i <= n; i++)
            printf("%d ", s[i]);
        cout << "     ";
        for (int i = 1; i <= n; i++)
            printf("%d ", c[i]);
        cout << endl;
    }
} a; // 声明一个名为a的树状数组实例

int main()
{
    cin >> n >> m;               // 读入数组大小和操作次数
    for (int i = 1; i <= n; i++) // 输入原始数组
        scanf("%d", &s[i]);

    a.init(); // 初始化树状数组

    for (int i = 1; i <= m; i++) // 处理m个操作
    {
        // a.print();//调试（可以查看每次操作前后的状态）
        int b, x, y;
        scanf("%d%d%d", &b, &x, &y); // 读入操作类型和参数

        if (b == 1)      // 操作1：单点修改
            a.add(x, y); // 在位置x增加y
        else             // 操作2：区间查询
            // 输出区间[x, y]的和 = 前缀和(y) - 前缀和(x-1)
            printf("%d\n", a.sum(y) - a.sum(x - 1));
    }
    return 0;
}