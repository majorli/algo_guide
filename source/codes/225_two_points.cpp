#include <cstdio>

int main()
{
	int n, data[101] = { 0 };
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &data[i]);

	int s;
	scanf("%d", &s);

	int l = 0, r = 0, sum = data[0];		// 初始化尺子
	while (l < n && r < n) {			// 循环条件为什么是这样？
		if (sum >= s) {
			if (sum == s) printf("sum[%d, %d]=%d\n", l, r, s);
			sum -= data[l++];		// 移动左端点
			if (l > r) sum += data[++r];	// 推动右端点
		} else {
			sum += data[++r];		// 移动右端点
		}
	}

	return 0;
}
