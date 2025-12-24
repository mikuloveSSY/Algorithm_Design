#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> a;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int w;
        cin >> w;
        a.push(w);
    }
    int ans = 0;
    while (1)
    {
        int x = a.top();
        a.pop();
        int y = a.top();
        a.pop();
        x += y;
        ans += x;
        if (a.empty())
        {
            break;
        }
        a.push(x);
    }
    cout << ans;
    return 0;
}