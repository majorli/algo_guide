#include <cstdio>

int bi_fast_power(int a, int n, int m)
{
	if (m == 1) return 0;
	if (n == 0 || a == 1) return 1;
	if (a == 0) return 0;
	long long ans = 1, b = a % m;
	while (n > 1) {
		if (n % 2) ans = ans * b % m;
		n /= 2;
		b = b * b % m;
	}
	ans = ans * b % m;
	return ans;
}

int main()
{
	int b, p, k;
	scanf("%d %d %d", &b, &p, &k);
	printf("%d^%d mod %d=%d\n", b, p, k, bi_fast_power(b, p, k));

	return 0;
}

