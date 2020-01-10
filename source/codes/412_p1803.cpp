#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Contest {
        int start, end;

        bool operator<(const Contest &c) const { return end < c.end; }
};

int main()
{
        int n;
        cin >> n;                       // 比赛的数量
        vector<Contest> cons(n);        // 所有的比赛
        for (int i = 0; i < n; ++i)
                cin >> cons[i].start >> cons[i].end;
        sort(cons.begin(), cons.end()); // 排序，使用vector的头尾两个迭代器指定排序范围
        int ans = 0, end = 0, next = 0; // ans：最多能参加的比赛数量；end：上一场比赛的结束时间
        while (next < n) {
                ++ans;
                end = cons[next].end;
                while (next < n && cons[next].start < end) ++next;
        }
        cout << ans << endl;

        return 0;
}
