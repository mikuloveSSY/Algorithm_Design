#include <iostream>
#include <queue>
using namespace std;

queue<int> lift;
int K[205];
int cnt[205];
int reach[205];

int main()
{
    int N, A, B;
    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++)
    {
        cin >> K[i];
    }
    reach[A] = -1;
    int flag = 1;
    lift.push(A);
    while (!lift.empty() && flag)
    {
        int temp = lift.front();
        lift.pop();
        int next[2] = {temp + K[temp], temp - K[temp]};
        for (int i = 0; i < 2; i++)
        {
            if (next[i] > 0 && next[i] <= N && !reach[next[i]])
            {
                cnt[next[i]] = cnt[temp] + 1;
                reach[next[i]] = 1;
                lift.push(next[i]);
            }
            if (next[i] == B)
            {
                flag = 0;
                break;
            }
        }
    }
    cout << (reach[B] ? cnt[B] : -1);
    return 0;
}