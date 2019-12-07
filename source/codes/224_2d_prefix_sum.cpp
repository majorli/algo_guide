#include <cstdio>

int m, n;
int data[1001][1001] = { 0 }, sum[1001][1001] = { 0 };

inline int ssum(int left, int top, int right, int bottom)
{
	return sum[bottom][right] - sum[top-1][right] - sum[bottom][left-1]
		+ sum[top-1][left-1];
}

void print();

int main()
{
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &data[i][j]);
			sum[i][j] = data[i][j] + sum[i-1][j] + sum[i][j-1]
				- sum[i-1][j-1];
		}
	}
	print();

	int half_row = m / 2, half_col = n / 2;
	printf("Split the Data Matrix into 4 blocks and Print Their Sums:\n");
	printf("%4d\t%4d\n",
			ssum(1, 1, half_col, half_row),
			ssum(half_col+1, 1, n, half_row));
	printf("%4d\t%4d\n",
			ssum(1, half_row+1, half_col, m),
			ssum(half_col+1, half_row+1, n, m));

	return 0;
}

void print()
{
	printf("Data Matrix:\n");
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			printf("%4d", data[i][j]);
		printf("\n");
	}
	printf("Prefix Sum Matrix:\n");
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			printf("%4d", sum[i][j]);
		printf("\n");
	}

	return;
}
