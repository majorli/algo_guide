#include <cstdio>

long long bi_fast_power(int a, unsigned int n)
{
	if (n == 0) return 1;
	long long ans = 1, b = a;
	while (n > 1) {
		if (n % 2) ans *= b;
		n /= 2;
		b *= b;
	}
	ans *= b;
	return ans;
}

int main()
{
	printf("0^0 = %lld\n", bi_fast_power(0, 0));
	printf("3^0 = %lld\n", bi_fast_power(3, 0));
	printf("3^13 = %lld\n", bi_fast_power(3, 13));
	printf("-3^13 = %lld\n", bi_fast_power(-3, 13));
	printf("-3^14 = %lld\n", bi_fast_power(-3, 14));
	printf("2^62 = %lld\n", bi_fast_power(2, 62));
	printf("2^63 = %lld\n", bi_fast_power(2, 63));

	return 0;
}

