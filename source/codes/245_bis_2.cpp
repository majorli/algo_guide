#include <cstdio>

// 这是用来获取一个传统C语言数组长度的宏
#define LEN(a) sizeof(a)/sizeof(a[0])

// a[]: 查找的数组
// t:   要查找的元素值
// left, right: 查找范围的左右端点
int bisearch(int a[], int t, int left, int right);

int main()
{
	int a[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	int t, pos;
	scanf("%d", &t);
	if ((pos = bisearch(a, t, 0, LEN(a))) != -1)
		printf("a[%d] = %d\n", pos, t);
	else
		printf("%d is not found\n", t);

	return 0;
}

int bisearch(int a[], int t, int left, int right)
{
	int mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == t) return mid;
		if (a[mid] > t)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

