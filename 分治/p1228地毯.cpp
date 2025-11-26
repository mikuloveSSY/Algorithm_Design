#include <iostream>
using namespace std;

// 关键在于分析公主的位置与各个2的幂次大小的区域的样式关系
// 不难发现对于2的幂次大小的区域，总能用3格大小的毯子铺满且只留出一块空着的格子,这个格子不妨都假定为“公主位”

int number[2][2] = {1, 2, 3, 4}; // 根据“公主位”填型号
int mi(int k)
{
    int ans = 1;
    while (k > 0)
    {
        ans *= 2;
        k--;
    }
    return ans;
}
int paint(int, int, int, int, int);
int main()
{
    int k, x, y;
    cin >> k >> x >> y;
    int len = mi(k);
    paint(x, y, 1, 1, len);
    return 0;
}

int paint(int x, int y, int X, int Y, int len)
{
    if (len == 2)
    {
        // 对于划分的2*2最小区域，根据“公主位”的奇偶性判断地毯型号
        cout << x % 2 + X << ' ' << y % 2 + Y << ' ' << number[(x - 1) % 2][(y - 1) % 2] << endl;
        return 1;
    }
    int mid_x = X + len / 2, mid_y = Y + len / 2;
    if (x < mid_x && y < mid_y)
    {
        // 对于划分区域时的中间那个链接各区域的地毯，根据奇偶性同样去判断型号
        cout << mid_x << ' ' << mid_y << ' ' << number[(mid_x - 1) % 2][(mid_y - 1) % 2] << endl;
        paint(x, y, X, Y, len / 2);
        paint(mid_x - 1, mid_y, X, mid_y, len / 2);
        paint(mid_x, mid_y - 1, mid_x, Y, len / 2);
        paint(mid_x, mid_y, mid_x, mid_y, len / 2);
    }
    else if (x >= mid_x && y < mid_y)
    {
        cout << mid_x - 1 << ' ' << mid_y << ' ' << number[mid_x % 2][(mid_y - 1) % 2] << endl;
        paint(mid_x - 1, mid_y - 1, X, Y, len / 2);
        paint(mid_x - 1, mid_y, X, mid_y, len / 2);
        paint(x, y, mid_x, Y, len / 2);
        paint(mid_x, mid_y, mid_x, mid_y, len / 2);
    }
    else if (x < mid_x && y >= mid_y)
    {
        cout << mid_x << ' ' << mid_y - 1 << ' ' << number[(mid_x - 1) % 2][mid_y % 2] << endl;
        paint(mid_x - 1, mid_y - 1, X, Y, len / 2);
        paint(x, y, X, mid_y, len / 2);
        paint(mid_x, mid_y - 1, mid_x, Y, len / 2);
        paint(mid_x, mid_y, mid_x, mid_y, len / 2);
    }
    else
    {
        cout << mid_x - 1 << ' ' << mid_y - 1 << ' ' << number[mid_x % 2][mid_y % 2] << endl;
        paint(mid_x - 1, mid_y - 1, X, Y, len / 2);
        paint(mid_x - 1, mid_y, X, mid_y, len / 2);
        paint(mid_x, mid_y - 1, mid_x, Y, len / 2);
        paint(x, y, mid_x, mid_y, len / 2);
    }
    return 1;
}