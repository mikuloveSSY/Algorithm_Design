#include <iostream>
using namespace std;
// 可用前缀栈解，贪心实际上也是同一个模拟过程
string n;
int k, L;
int rest;

main()
{
    cin >> n >> k;
    L = n.length();
    int start = 0, remove = k;
    int flag = 0; // 处理前导零
    while (rest < L - k)
    {
        int min_i = start, min = n[start] - '0';
        // cout << '\n'
        //      << L << ' ' << remove << endl;
        for (int i = start; i < start + remove + 1 && i < L; i++)
        {
            if (min > n[i] - '0')
            {
                min_i = i;
                min = n[i] - '0';
            }
        }
        if (!flag && min != 0)
            flag = 1;
        if (flag)
            cout << min;
        remove -= min_i - start;
        start = min_i + 1;
        rest++;
    }
    if (flag == 0)
        cout << '0'; // 说明前面一直为0
    return 0;
}