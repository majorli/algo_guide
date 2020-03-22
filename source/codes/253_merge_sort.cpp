#include <cstdio>
#include <cstring>

// 输出数组元素的辅助函数
void print(int d[], int n);

// 归并排序主函数
void merge_sort(int d[], int l, int r);

// 归并函数
void merge(int d[], int l, int r, int mid);

int main()
{
	int d[100000], n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &d[i]);

	merge_sort(d, 0, n);
	print(d, n);

	return 0;
}

void print(int d[], int n)
{
	printf("%d", d[0]);
	for (int i = 1; i < n; ++i) printf(" %d", d[i]);
	printf("\n");
}

/*
 * 归并排序的主函数，将待排序数组二分为左右两部分，分别递归地进行排序并将结果归并
 * d: 待排序的数组
 * l: 待排序部分的左端点，包含 d[l]
 * r：待排序部分的右端点，不包含 d[r]
 * 根据含头不含尾的规则，待排序部分的长度即为 r - l
 */
void merge_sort(int d[], int l, int r)
{
	// 按含头不含尾的规则，将待排序部分二分为 [l, mid) 和 [mid, r) 两半
	// 两个部分恰好仍然是含头不含尾的规则，长度分为为 mid - l 和 r - mid
	int mid = (l + r) / 2;
	// 若左半部分长度大于1，则递归地对其进行归并排序
	if (mid - l > 1) merge_sort(d, l, mid);
	// 若右半部分长度大于1，则递归地对其进行归并排序
	if (r - mid > 1) merge_sort(d, mid, r);
	// 左右两部分递归地完成排序后，将二者进行归并，完成完整的排序
	merge(d, l, r, mid);
}

/*
 * 对数组 d 的 [l, mid) 和 [mid, r) 左右两个有序部分进行归并
 * d: 待归并的数组
 * l: 要归并的前半部分左端点
 * r: 要归并的右半部分右端点
 * mid: 要归并的左半部分右端点，同时也是右半部分左端点
 * 根据含头不含尾的规则，d[mid] 为右半部分的第一个元素，不含在左半部分中
 */
void merge(int d[], int l, int r, int mid)
{
	// 动态申请归并过程使用的临时数组，长度为要归并的所有元素
	int *temp = new int[r - l];
	// 归并过程，参考3.4.10.1小节归并法的介绍
	// 将 d 数组中 [l, mid) 和 [mid, r) 两部分归并到临时数组 temp 中
	int i = l, j = mid, p = 0;
	while (i < mid && j < r)
		if (d[i] <= d[j]) temp[p++] = d[i++];
		else temp[p++] = d[j++];
	while (i < mid) temp[p++] = d[i++];
	while (j < r) temp[p++] = d[j++];
	// 使用内存块复制快速将归并好的数据复制回原数组中的原位置
	memcpy(d + l, temp, (r - l) * sizeof(d[0]));
	// 用 new 命令申请的动态内存必须用完就销毁，有借有还
	delete [] temp;
}
