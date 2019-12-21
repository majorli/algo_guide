#include <cstdio>

int field[1001][1001] = { 0 };

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	int x1, y1, x2, y2;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		y2++;
		for (int row = x1; row <= x2; row ++) {
			field[row][y1]++;
			if (y2 <= n) field[row][y2]--;
		}
	}
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= n; col++)
			field[row][col] += field[row][col-1];
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= n; col++)
			printf("%d%c", field[row][col], col == n ? '\n' : ' ');

	return 0;
}
