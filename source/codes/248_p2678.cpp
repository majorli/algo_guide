#include <cstdio>

// 搬走中间的石块，使得跳跃的最短距离为d
// pos[]: 石块位置的数组
// n: 可以搬走的中间石块的数量
// d: 要达到的最短跳跃距离
int move(int pos[], int n, int d);

int main()
{
	int l, n, m, pos[50020] = { 0 }; // pos[0]表示起点位置
	scanf("%d %d %d", &l, &n, &m);
	pos[n+1] = l;	// pos[n+1]表示河对岸的石头距离，就是河的宽度
	for (int i = 1; i <= n; ++i)
		scanf("%d", &pos[i]);
	// 开始二分搜索边界，搜索的范围是从0到河的宽度l
	int left = 0, right = l, mid;
	while (left <= right) {
		mid = (left + right) / 2;   // 尝试使最小宽度变成mid
		if (move(pos, n, mid) <= m) // 只需要移走小于等于m块的石块就够了
			left = mid + 1;     // 继续测试更大的最小宽度
		else			    // 需要移走比m更多块的石块
			right = mid - 1;    // 尝试小一点的最小宽度
	}
	// 右边界搜索，边界是left，但是本题要的结果是右边界之前的一个值
	// left指向右边界，right指向要查找的结果的最后一个位置
	printf("%d\n", right);
	return 0;
}

int move(int pos[], int n, int d)
{
	int cnt = 0;		// 要搬走的石块数量
	// 循环控制变量：s: 当前石块编号，prev: 前一块石块的编号
	for (int s = 1, prev = 0; s <= n + 1; ++s)
		if (pos[s] - pos[prev] < d)
			++cnt;	// 搬走当前石块，此时下一轮的前一石块不变
		else
			prev = s;	// 当前石块变成下一轮的前一石块
	return cnt;
}
