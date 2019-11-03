#include <cstdio>
#include <cstring>

const int MAXN = 1e6;

int primes[MAXN] = { 0 };
bool is_prime[MAXN] = { false };

int euler_seive(int max)
{
	memset(is_prime, 1, (max + 1) * sizeof(bool));
	is_prime[1] = false;
	int n = 0;
	for (int i = 2; i <= max; i++) {
		if (is_prime[i])
			primes[n++] = i;
		for (int j = 0; j < n && i * primes[j] <= max; j++) {
			is_prime[i * primes[j]] = false;
			if (i % primes[j] == 0)
				break;
		}
	}
	return n;
}

int main()
{
	int n, p;
	scanf("%d", &n);

	printf("%d primes found in [2, %d]:\n", p = euler_seive(n), n);
	for (int i = 0; i < p; i++)
		printf("%3d,", primes[i]);
	printf("\n");

	return 0;
}
