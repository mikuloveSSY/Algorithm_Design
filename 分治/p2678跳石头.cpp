#include <iostream>
using namespace std;
/*方法（反向思考）：
二分法枚举距离，假设该距离符合时，计算出至少需要移走的石头个数m
若符合m<=M，继续增大距离进行下一轮检测；若不符合，则减小距离进行下一轮检测
*/

int D[50005] = {0};

int main()
{
    int L, N, M;
    cin >> L >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> D[i];
    }
    D[N + 1] = L; // N+1为对岸
    int left = 1, right = L;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int m = 0;
        int now = 0, next = 0;
        while (next < N + 1)
        {
            /*
            实际上这里省略了两种情况，即：一开始在岸上时，若一直移动石头，next就会直接到对岸；若一开始是在中间的一块石头上，那么最终若一直移导致next到达对岸时，最后一下若还是<mid，那么此时m++实际上移动的是now脚下的那块石头，因为此时从now到对岸之间已经没石头可以移走，而移走脚下那块石头后，总距离必然能>mid
             */
            next++;
            if (D[next] - D[now] < mid)
            {
                m++;
            }
            else
            {
                now = next;
            }
        }
        if (m > M)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    cout << right;
    return 0;
}