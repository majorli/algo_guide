#include <cstdio>
#include <cstring>

void print(int d[], int n);

// 基数排序主函数
void radix_sort(int d[], int n);

// 获取整数 n 的 radix 位上的数，采用内联函数以提高速度
int digit(int n, int radix) { return (n / radix) % 10; }

int main()
{
	int d[100000], n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &d[i]);

	radix_sort(d, n);
	print(d, n);

	return 0;
}

void print(int d[], int n)
{
	printf("%d", d[0]);
	for (int i = 1; i < n; ++i) printf(" %d", d[i]);
	printf("\n");
}

void radix_sort(int d[], int n)
{
	int cnt[10], radix = 1; // cnt[10]: 计数数组, radix: 位,1为个位,10为十位...
	int *tmp = new int[n];	// 临时空间，用于临时放置排好序的元素

	while (true) {
		memset(cnt, 0, sizeof(cnt));	// 开始时清空计数值
		for (int i = 0; i < n; ++i)	// 对radix位上的数进行计数
			++cnt[digit(d[i], radix)];
		if (cnt[0] == n) break;	// 全部元素计数都在0上,说明已经超过最高位,排序结束
		for (int i = 1; i < 10; ++i)	// 计数值做前缀和
			cnt[i] += cnt[i-1];
		/*
		 * 对计数值做前缀和后，计数值变成指示对应元素在排完序后应处的最后位置
		 * 例如序列 [3, 2, 3, 1, 0]，计数数组长度为5，对值为从0到4的元素计数
		 * 计数后各计数值为 [1, 1, 1, 2, 0]，表示1个0，1个1，1个2，2个3，0个4
		 * 做前缀和得到 [1, 2, 3, 5, 5]，表示以下含义：
		 * 最后一个值为0的元素在排完序的数组中应该在第1个
		 * 最后一个值为1的元素在排完序的数组中应该在第2个
		 * 最后一个值为2的元素在排完序的数组中应该在第3个
		 * 最后一个值为3的元素在排完序的数组中应该在第5个
		 * 最后一个值为4的元素在排完序的数组中应该在第5个
		 * 按照上述规律，为保持排序的稳定性，应该逆序遍历原数组中的元素。
		 * 这样，每遇到一个元素，它对应的计数数组值减1就是它排序后应处的位置。
		 * 按照这个位置复制元素到临时空间里，然后把这个计数值减1，改变为下一个
		 * 相同元素的位置，这种方法同时保证了排序的稳定性
		 */
		for (int i = n - 1; i >= 0; --i)// 按上述规律逆序遍历并复制元素
			tmp[--cnt[digit(d[i], radix)]] = d[i];
		// 将临时空间里按从个位到当前radix位排好序的中间结果复制回原数组
		memcpy(d, tmp, n * sizeof(tmp[0]));
		// 循环进入更高一位
		radix *= 10;
	}
	delete [] tmp;
}

