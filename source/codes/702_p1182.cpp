#include <cstdio>

int a[100010] = { 0 }, n, m;

inline int sum(int begin, int end) { return a[end] - a[begin-1]; }

bool is_small(int max);

int main()
{
	scanf("%d %d", &n, &m);
	int temp;
	int left = 0, right, mid, ans;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &temp);
		a[i] = a[i-1] + temp;
		if (temp > left) left = temp;
	}
	right = a[n];
	
	while (left <= right) {
		mid = (left + right) / 2;
		// printf("left = %d, right = %d, TESTING %d\n", left, right, mid);
		if (is_small(mid)) {
			// printf("  small, move to the right half\n");
			left = mid + 1;
		} else {
			// printf("  not small, record and test the left half\n");
			ans = mid;
			right = mid - 1;
		}
	}
	printf("%d\n", ans);

	return 0;
}

bool is_small(int max)
{
	int count = 0, begin = 1, end = 1;
	while (count < m && begin <= n) {
		// printf("--> seek start from %d, ", begin);
		while (sum(begin, end) <= max && end <= n)
			end++;
		count++;
		// printf("found interval %d, from %d to %d\n", count, begin, end-1);
		begin = end;
	}
	// printf("--> seek over, count = %d, begin = %d, end = %d\n", count, begin, end);
	// 'max' is small ==> count == m && begin <= n
	// 'max' is not small ==> (count == m && begin > n) || count < m
	return (count == m && begin <= n);
}
