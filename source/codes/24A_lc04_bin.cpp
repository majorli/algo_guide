#include <cstdio>

int d[2][1000010];
int a = 0, b = 1;

int main()
{
	int m, n, half;
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; ++i) scanf("%d", &d[a][i]);
	for (int i = 0; i < n; ++i) scanf("%d", &d[b][i]);
	half = (m + n) / 2;
	// 确保数组 d[a] 是比较短的那个数组，其长度为m，因此确保 m <= n
	if (m > n) { a = m; m = n; n = a; a = 1; b = 0; }
	
	// 二分查找数组 d[a] 分在前半部分的数字个数 k，查找范围为从 0 到 m，
	// 当 d[a] 中有 k 个数分在前半部分的时候，那么 d[b] 中必须有 j = half-k
	// 个数分在前半部分，这样前半部分一共 half 个数，后半部分 m+n-half 个。
	// 当 m+n 为偶数时，前后个数相等；奇数时，前半部分少一个。
	// 
	// 设前半部分最大值为 max_h，后半部分最小值为 min_r，那么当 m+n 为偶
	// 数时，中位数为 (max_h+min_r)/2.0；为奇数时，中位数为 min_r。
	//
	// 因为 m <= n，所以 m <= half <= n，当：
	//   k = 0 时：d[a] 的所有 m 个数都在后半部分
	//   k = m 时：d[a] 的所有 m 个数都在前半部分
	//   1 <= k <= m-1 时：d[a] 和 d[b] 各有一部分数在前后两个部分
	//
	// 又，各重要变量的取值范围如下：
	// 0 <= k <= m, m <= half <= n => 0 <= m-k <= j = half-k <= n-k <= n
	//
	// 此问题必有且仅有一个解，解的条件是：max_h <= min_r
	//
	// 查找时应判断 d[a] 提供给前半部分的数字个数 k 是多了还是少了：
	//     如果 d[a] 贡献给前半部分的最后一个数字 d[a][k-1] 比 d[b] 留在
	//         后半部分的第一个数字 d[b][j] 大，那么说明 k 多了
	//     如果 d[b] 贡献给前半部分的最后一个数字 d[b][j-1] 比 d[a]
	//         留在后半部分的第一个数字 d[a][k] 大，那么说明 k 少了
	// 所以，进行下面的分析：
	//     当 1 <= k <= m-1 时：
	//        IF d[a][k-1] > d[b][j] THEN right = k - 1
	//        IF d[b][j-1] > d[a][k] THEN left = k + 1
	//     当 k == 0 时：
	//        这时已经不可能再减少 k 了，也不存在 d[a][k-1]，只需要判断
	//        IF d[b][j-1] > d[a][k] THEN left = k + 1
	//     当 k == m 时：
	//        这是已经不可能再增加 k 了，也不存在 d[a][k]，只需要判断
	//        IF d[a][k-1] > d[b][j] THEN right = k - 1
	//     其他情况都说明查找成功。
	// 以上三种情况可以合并为两种：
	//     IF k < m && d[b][j-1] > d[a][k] THEN left = k + 1
	//     IF k > 0 && d[a][k-1] > d[b][j] THEN right = k - 1
	// 剩余情况说明查找成功，计算 max_h 和 min_r 并得出中位数即可
	//
	int left = 0, right = m, k, j;
	// d[a], d[b] 各自在前半部分的最大值和后半部分的最小值
	int max_h, min_r;
	while (left <= right) {
		k = (left + right) / 2;
		j = half - k;
		if (k < m && d[b][j-1] > d[a][k])
			left = k + 1;	// k 小了
		else if (k > 0 && d[a][k-1] > d[b][j])
			right = k - 1;	// k 大了
		else {			// Bingo! 找到中位数的正确划分
			// 计算左半部分的最大值 max_h
			if (k == 0)
				max_h = d[b][j-1];
			else if (j == 0)
				max_h = d[a][k-1];
			else
				max_h = d[a][k-1] > d[b][j-1] ? d[a][k-1] : d[b][j-1];
			// 计算右半部分的最小值 min_r
			if (k == m)
				min_r = d[b][j];
			else if (j == n)
				min_r = d[a][k];
			else
				min_r = d[a][k] < d[b][j] ? d[a][k] : d[b][j];
			// 退出循环
			break;
		}
	}
	printf("%.2lf\n", (m + n) % 2 ? (double) min_r : (max_h + min_r) / 2.0);

	return 0;
}

