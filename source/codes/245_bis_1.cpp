#include <cstdio>

int main()
{
	int a[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	int t;
	scanf("%d", &t);
	int left = 0, right = 9, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == t) break;
		if (a[mid] > t)
			right = mid - 1;
		else
			left = mid + 1;
	}
	if (left > right)
		printf("%d is not found\n", t);
	else
		printf("a[%d] = %d\n", mid, t);

	return 0;
}

