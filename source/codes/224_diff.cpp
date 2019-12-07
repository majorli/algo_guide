#include <cstdio>

int main()
{
	int n, data[1000], diff[1000] = { 0 };
	int m, l, r, p;

	scanf("%d", &n);		// n: 输入数据总量
	for (int i = 0; i < n; i++)
		scanf("%d", &data[i]);

	scanf("%d", &m);		// m: 区间修改的次数
	// 循环读入每次修改的左右端点和改变量，记录改变点
	for (int k = 0; k < m; k++) {
		scanf("%d %d %d", &l, &r, &p);
		diff[l] += p;
		if (r < n - 1) diff[r+1] -=p;
	}

	// 原地完成diff差分数组的前缀和处理
	for (int i = 1; i < n; i++)
		diff[i] += diff[i-1];

	// 用差分数组对位完成数据修改
	for (int i = 0; i < n; i++)
		data[i] += diff[i];

	// 输出结果
	for (int i = 0; i < n; i++)
		printf("%4d", data[i]);
	printf("\n");

	return 0;
}
