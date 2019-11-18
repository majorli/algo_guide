#include <cstdio>
#include <cstring>

const int MAXN = 1e8;
bool primes[MAXN+10];

bool is_palindrome(int n);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);

	b = b > 9989899 ? 9989899 : b;

	memset(primes, 1, sizeof(primes));
	primes[0] = primes[1] = false;
	int p = 2;
	while (p * p <= b) {
		for (int i = p * p; i <= b; i += p)
			primes[i] = false;
		if (p >= a && is_palindrome(p))
			printf("%d\n", p);
		while (!primes[++p]);
	}
	while (p <= b) {
		if (p >= a && is_palindrome(p))
			printf("%d\n", p);
		while (!primes[++p]);
	}

	return 0;
}

bool is_palindrome(int n)
{
	int ori = n, rev = n % 10;
	while (n /= 10) rev = rev * 10 + n % 10;
	return ori == rev;
}