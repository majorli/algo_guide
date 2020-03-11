#include <cstdio>

int main()
{
	int n, k, len[10010];
	scanf("%d %d", &n, &k);
	double temp;
	int left = 1, right = 0, mid;
	for (int i = 0; i < n; ++i) {
		scanf("%lf", &temp);
		len[i] = (int)(temp * 100);	// 乘100变成整数
		if (len[i] > right) right = len[i]; // 最长的绳子长度作为查找的终点
	}
	int num;
	while (left <= right) {
		mid = (left + right) / 2;	// 尝试切出的绳子长度为mid
		num = 0;	// 计算能切出的绳子数量
		for (int i = 0; i < n; ++i) num += len[i] / mid;
		if (num < k)	// 切成长度mid，切出来的数量少了，说明mid大了
			right = mid - 1;	// 下一次尝试切得更短
		else		// 切出的绳子数量大于等于k，还能尝试更长的长度
			left = mid + 1;		// 下一次尝试更长的长度
	}
	// right指向的是要查找的解，left指向的是它的后一个位置，即右边界
	printf("%.2lf\n", right / 100.0);

	return 0;
}
