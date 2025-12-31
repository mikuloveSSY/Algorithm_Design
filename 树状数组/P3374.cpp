#include <iostream>
#define int long long // 将 int 替换为 long long，防止溢出
using namespace std;

const int MAXN = 1000001; // 定义最大数组长度
int n, q, c[MAXN];        // n: 数组长度，q: 查询次数，c: 树状数组

// 树状数组更新操作
void upd(int i, const int x)
{
    // 向上更新所有包含位置 i 的区间
    for (; i <= n; i += i & -i)
    {
        c[i] += x;
    }
}

// 前缀和查询操作
int query(int i)
{
    int ret = 0;
    // 向下累加所有不重叠的区间
    for (; i; i -= i & -i)
    {
        ret += c[i];
    }
    return ret;
}

signed main()
{ // 由于定义了 #define int long long，所以用 signed 代替 int
    // 优化输入输出，提高速度
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr);

    cin >> n >> q;

    // 初始化差分树状数组
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        // 将原始数组 a 转化为差分数组 c
        upd(i, a);      // 在位置 i 增加 a
        upd(i + 1, -a); // 在位置 i+1 减少 a（差分特性）
    }

    // 处理 q 个操作
    for (int op, l, r, x; q--;)
    {
        cin >> op;
        if (op == 1)
        {
            // 操作 1: 区间 [l, r] 增加 x
            cin >> l >> r >> x;
            upd(l, x);      // 在 l 处增加 x
            upd(r + 1, -x); // 在 r+1 处减少 x，保证只在 [l, r] 区间内有效
        }
        else
        {
            // 操作 2: 单点查询，输出位置 x 的值
            cin >> x;
            cout << query(x) << '\n'; // 前缀和查询即为原数组的值
        }
    }

    return 0;
}