#include <cstdio>

inline int ssum(int *sum, int l, int r)
{
	return sum[r] - sum[l-1];
}

int main()
{
	int n = 0, data[1001] = { 0 }, sum[1001] = { 0 };

	scanf("%d", &n);
	int d;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d);
		data[i] = d;
		sum[i] = sum[i-1] + d;
	}
	printf("data: ");
	for (int i = 1; i <= n; i++)
		printf("%4d", data[i]);
	printf("\n");

	printf("sum : ");
	for (int i = 1; i <= n; i++)
		printf("%4d", sum[i]);
	printf("\n");

	int half = n / 2;
	printf("data[1] + ... + data[%d] = %d\n", half, ssum(sum, 1, half));
	printf("data[%d] + ... + data[%d] = %d\n", half+1, n, ssum(sum, half+1, n));

	return 0;
}
