#include <cstdio>

bool is_prime(int a);
int reverse(int n);
int palindromes(int size, int min, int max);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);

	if (a <= 5 && b >= 5)
		printf("5\n");
	if (a <= 7 && b >= 7)
		printf("7\n");
	if (a <= 11 && b >= 11)
		printf("11\n");
	a = a > 101 ? a : 101;
	b = b > 9989899 ? 9989899 : b;

	for (int size = 1; size <= 100; size *= 10)
		palindromes(size, a, b);

	return 0;
}

bool is_prime(int a)
{
	bool prime = true;
	for (int i = 3; i * i <= a && (prime = a % i); i++);

	return prime;
}

int reverse(int n)
{
	int r = n % 10;
	while (n /= 10) r = r * 10 + n % 10;
	return r;
}

int palindromes(int size, int min, int max)
{
	int p, r;
	for (int f = 1; f <= 9; f += 2) {
		if (f == 5) continue;
		for (int m = 0; m < size; m++) {
			for (int l = 0; l < 10; l++) {
				p = f * size + m;
				r = reverse(p);
				p = (p * 10 + l) * size * 10 + r;
				if (p < min) continue;
				if (p > max) return 0;
				if (is_prime(p))
					printf("%d\n", p);
			}
		}
	}
	return 0;
}
