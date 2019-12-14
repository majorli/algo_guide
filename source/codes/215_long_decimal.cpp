#include <cstdio>

int main()
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	if (!a) {
		printf("0\n");
		return 0;
	}
	
	bool neg = (a < 0 && b > 0) || (a > 0 && b < 0);
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;

	int digits[101], d = 0, r;
	digits[0] = a / b;
	r = a % b * 10;

	while (c-- && r) {
		digits[++d] = r / b;
		r = r % b * 10;
	}
	
	digits[d] += (r / b > 4);
	while (d > 0 && digits[d] == 10) {
		digits[d--] = 0;
		++digits[d];
	}

	if (neg) printf("-");
	printf("%d", digits[0]);
	if (d) printf(".");
	for (int i = 1; i <= d; ++i)
		printf("%d", digits[i]);
	printf("\n");

	return 0;
}
