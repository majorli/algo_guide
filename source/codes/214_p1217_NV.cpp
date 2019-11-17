#include <cstdio>

bool is_prime(int n);
bool is_palindrome(int n);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);

	for (int i = a; i <= b; i += 2) {
		if (i > 5 && i % 10 == 5) continue;
		if (is_prime(i) && is_palindrome(i))
			printf("%d\n", i);
	}

	return 0;
}

bool is_prime(int n)
{
	bool prime = true;
	for (int f = 3; f * f <= n && (prime = n % f); f++);
	return prime;
}

bool is_palindrome(int n)
{
	int ori = n, rev = n % 10;
	while (n /= 10) rev = rev * 10 + n % 10;
	return ori == rev;
}
