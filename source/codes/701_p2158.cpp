#include <cstdio>

int main()
{
	// cnt: 答案，C君能看到的学生人数
	// x[]: 动态规划表，从x[2]到x[n-1]项表示看不见的人数（非互质对数量）
	int n, cnt, x[40000] = { 0 };
	scanf("%d", &n);
	if (n == 1) {
		printf("0\n");
		return 0;
	}

	cnt = 2 * n - 1 + (n - 2) * (n - 2);
	for (int m = n - 1; m >= 2; m--) {
		x[m] = ((n - 1) / m) * ((n - 1) / m);
		for (int km = m + m; km < n; km += m)
			x[m] -= x[km];
	}
	for (int m = 2; m < n; m++)
		cnt -= x[m];

	printf("%d\n", cnt);

	return 0;
}
