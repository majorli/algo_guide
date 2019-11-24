#include <cstdio>

long long fast_power(int a, unsigned int n)
{
	long long ans = 1, base = a;
	while (n) {
		if (n & 1) ans *= base;
		n >>= 1;
		base *= base;
	}
	return ans;
}

int main()
{
	printf("0^0 = %lld\n", fast_power(0, 0));
	printf("3^0 = %lld\n", fast_power(3, 0));
	printf("3^13 = %lld\n", fast_power(3, 13));
	printf("-3^13 = %lld\n", fast_power(-3, 13));
	printf("-3^14 = %lld\n", fast_power(-3, 14));
	printf("2^62 = %lld\n", fast_power(2, 62));
	printf("2^63 = %lld\n", fast_power(2, 63));

	return 0;
}
