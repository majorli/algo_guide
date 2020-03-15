#include <cstdio>

int a[1000010], b[1000010], c[2000010];

int main()
{
	int m, n, half;
	scanf("%d %d", &m, &n);
	// 计算出元素总数 m+n 的一半，由于C++整数除法向下取整，以及数组从0开始计数的特点
	// 当 m+n 为奇数时，half 恰好值向中间元素的位置，例如 (2+3)/2=2，c[2]恰好是第3个元素
	// 当 m+n 为偶数时，half-1 和 half 恰为最中间的两个位置，例如 (2+2)/2=2，c[1]和c[2]是两个正中位置
	half = (m + n) / 2;
	// 读入两个原数组 a 和 b
	for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
	for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
	// pa, pb: a 和 b 两个数组中还没有被归并部分的首位置；p: c 数组的尾部位置
	int pa = 0, pb = 0, p = 0;
	// 每次从 a 和 b 未归并部分的头部挑较小的那个数放到 c 的尾部，直到 a 或 b 中某一个数组被归并完
	while (pa < m && pb < n) a[pa] <= b[pb] ? c[p++] = a[pa++] : c[p++] = b[pb++];
	// 把剩余部分照搬到 c 的尾部完成归并
	while (pa < m) c[p++] = a[pa++];	// 如果 a 已经归并完了，这个循环不会进入
	while (pb < n) c[p++] = b[pb++];	// 同上，故两个循环只有一个会真正运行
	// 输出中位数
	printf("%.2lf\n", p % 2 ? (double) c[half] : (c[half] + c[half-1]) / 2.0);

	return 0;
}

