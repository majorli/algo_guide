#include <cstdio>

int sp_fast_power(int a, int n, int m)
{
	if (m == 1) return 0;
	if (n == 0 || a == 1) return 1;
	if (a == 0) return 0;
	long long ans = 1, base = a % m;
	while (n) {
		if (n & 1) ans = ans * base % m;
		n >>= 1;
		base = base * base % m;
	}
	return ans;
}

int main()
{
	int b, p, k;
	scanf("%d %d %d", &b, &p, &k);
	printf("%d^%d mod %d=%d\n", b, p, k, sp_fast_power(b, p, k));

	return 0;
}
